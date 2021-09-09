#include"player.h"
static  Uint8  *audio_chunk;
static  Uint32  audio_len;
static  Uint8  *audio_pos;
sonicStream stream;
//记录时基
double pts;
long long playingTime=0;
Uint8 * pcm_buffer;
int pcm_buffer_size;
int pictureWidth;
long long  duration;
int pictureHeight;
int yet = -1;
int yetAudio=-1;
volatile double speed=1;
volatile bool quitflag0=false;
volatile bool quitflag1=false;
volatile bool quitflag2=false;
volatile bool quitflag3=false;
//控制是否退出
volatile bool quitFlag=true;
volatile bool  audioStatus=false;
//声道数
int channels;
//采样率
int sanmple;
//编码器上下文
AVFrame *rgb=NULL;
char *pcm=NULL;
AVFrame *pAVFrameYUV420P=NULL;
AVCodecContext * context = NULL;
AVCodecContext * contextAudio = NULL;
//解码前的数据（h.264数据）
AVPacket *packet = NULL;
//解码后的数据（yuv图像数据）
AVFrame * frame = NULL;
AVFrame * frameAudio = NULL;
//初始化解码器 0为成功  负数为失败
int streamIndexAudio = -1;
int streamIndexVideo = -1;
int successAVCodec = NULL;
int successAVCodecAudio = NULL;
bool renderFlag=false;
int countFlag=0;
//编解码器
AVCodec * aVCodec = NULL;
AVCodec * aVCodecAudio = NULL;
//编解码器参数
AVCodecParameters * codecContext = NULL;
AVCodecParameters * codecContextAudio = NULL;
int pixel_w = 0, pixel_h = 0;
//视频文件信息上下文
AVFormatContext* formatContext = NULL;
int success;
//是否获得数据流，>=0,成功获取，否则获取失败
int streamId = 0;
//音量大小
int volume=40;
//编解码器的id
AVCodecID codecId;
AVCodecID codecIdAudio;
uint8_t *outBuffer;
SwrContext *m_SWRtx;
SDL_Thread * threadRender;
uint8_t * out[2] = { 0 };
//设置视频格式
SDL_AudioSpec wanted_spec;
PacketQueue*  videoPacketQueue=NULL;
PacketQueue*  audioPacketQueue=NULL;
SDLVideoInfo * sdlVideoInfo=NULL;
struct SwsContext *swsContext=NULL;
QWidget* widget;
//计算视频位置
void calculate_display_rect(SDL_Rect *rect,
                            int scr_xleft, int scr_ytop, int scr_width, int scr_height,
                            int pic_width, int pic_height, AVRational pic_sar)
{
    float aspect_ratio;
    int width, height, x, y;

    if (pic_sar.num == 0)
        aspect_ratio = 0;
    else
        aspect_ratio = av_q2d(pic_sar);
    // 长宽比小于等于0时，置为1.0
    if (aspect_ratio <= 0.0)
        aspect_ratio = 1.0;
    // 乘以图片的宽高比，可以做缩放处理
    aspect_ratio *= (float)pic_width / (float)pic_height;

    /* XXX: we suppose the screen has a 1.0 pixel ratio */
    // 以高度为基准，计算宽度
    height = scr_height;
    width = lrint(height * aspect_ratio) & ~1;
    // 判断是否大于原图的宽度，如果是则以宽度为基准计算高度
    if (width > scr_width) {
        width = scr_width;
        height = lrint(width / aspect_ratio) & ~1;
    }
    // 计算起始位置和宽高
    x = (scr_width - width) / 2;
    y = (scr_height - height) / 2;
    rect->x = scr_xleft + x;
    rect->y = scr_ytop  + y;
    rect->w = FFMAX(width,  1);
    rect->h = FFMAX(height, 1);
}
//视频解复用
int  mutexVideo(const char* inputFIleName,QWidget* data) {
    widget=data;
    formatContext = avformat_alloc_context();
    success = avformat_open_input(&formatContext, inputFIleName, NULL, NULL);
    if (success == 0){
        //获取流信息，如果返回<0表示没有获得流
        streamId = avformat_find_stream_info(formatContext, NULL);
        if (streamId < 0) {
            return 0;
        }
        //申请packet存放一帧压缩数据
        packet = av_packet_alloc();
        if (!packet) {
            return 0;
        }
        //查找视频的流
        for (unsigned int i = 0; i < formatContext->nb_streams; i++)
        {
            //判断每个流中的编解码器类型是否为视频类型
            if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                //创建一个视频包队列
                videoPacketQueue = new packetQueue;
                //初始化队列
                initpacketQueue(videoPacketQueue);
                streamIndexVideo = i;
                codecContext = formatContext->streams[streamIndexVideo]->codecpar;
                //获取视频的宽高
                pixel_w = codecContext->width;
                pixel_h = codecContext->height;
                //根据解码器上下文查找已经注册的解码器的id
                codecId = codecContext->codec_id;
                //获取解码器
                aVCodec = avcodec_find_decoder(codecId);
                //申请avcodeccontext
                context = avcodec_alloc_context3(NULL);
                //绑定编码器
                avcodec_parameters_to_context(context, codecContext);
                if (!context) {
                    cout << "申请context失败" << endl;
                    return 1;
                }
                //打开编码器
                successAVCodec = avcodec_open2(context, aVCodec, NULL);
                if (successAVCodec < 0) {
                    //打开编解码器失败
                    cout << "初始化解码器失败" << endl;
                    return 0;
                }
                frame = av_frame_alloc();
                if (!frame) {
                    cout << "申请frame失败" << endl;
                    exit(1);
                }
                sdlVideoInfo = new SDLVideoInfo;
                initSDLInfo(sdlVideoInfo, data);
                swsContext = sws_getContext(pixel_w, pixel_h,
                                            context->pix_fmt, pixel_w, pixel_h, AV_PIX_FMT_YUV420P, SWS_POINT, NULL, NULL, NULL);
                //创建一个YUV420视频像素数据格式缓冲区（一帧数据）
                pAVFrameYUV420P = av_frame_alloc();
                int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_YUV420P,
                                                          pixel_w,
                                                          pixel_h,
                                                          1);
                //开辟一块内存空间
                outBuffer = (uint8_t *)av_malloc(bufferSize);
                av_image_fill_arrays(pAVFrameYUV420P->data,
                                     pAVFrameYUV420P->linesize,
                                     outBuffer,
                                     AV_PIX_FMT_YUV420P,
                                     pixel_w,
                                     pixel_h,
                                     1);
                //视频解码（循环获取数据（压缩前的数据）到packet）
                //创建一个线程用于渲染视频
                threadRender = SDL_CreateThread(decodeVideo, NULL, NULL);
                threadRender = SDL_CreateThread(renderVideo, NULL,  (void *)sdlVideoInfo);

            }
            else if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {

                //音频时长
                duration=formatContext->streams[i]->duration;
                //音频流的时基
                pts=av_q2d(formatContext->streams[i]->time_base);
                //创建一个音频包队列
                audioPacketQueue = new packetQueue;
                //初始化队列
                initpacketQueue(audioPacketQueue);
                streamIndexAudio = i;
                //音频流解码——————————————————————————————————————————————
                codecContextAudio = formatContext->streams[streamIndexAudio]->codecpar;
                //根据解码器上下文查找已经注册的解码器的id
                codecIdAudio = codecContextAudio->codec_id;
                //获取视频采样率及相关信息
                channels = codecContextAudio->channels;
                //视频采样率
                sanmple = codecContextAudio->sample_rate;
                //控制音频播放速度
                stream=sonicCreateStream(sanmple, channels);
                //声道布局
                int64_t channellayout = av_get_default_channel_layout(channels);
                //获取解码器
                aVCodecAudio = avcodec_find_decoder(codecIdAudio);
                //申请avcodeccontext
                contextAudio = avcodec_alloc_context3(NULL);
                //绑定编码器
                avcodec_parameters_to_context(contextAudio, codecContextAudio);
                if (!contextAudio) {
                    cout << "申请context失败" << endl;
                    exit(1);
                }
                //打开编码器
                successAVCodecAudio = avcodec_open2(contextAudio, aVCodecAudio, NULL);
                if (successAVCodecAudio < 0) {
                    //打开编解码器失败
                    cout << "初始化解码器失败" << endl;
                    return 0;
                }
                //创建结构体
                m_SWRtx = swr_alloc();
                if (m_SWRtx == NULL) {
                    cout << "error" << endl;
                    return 1;
                }
                //对结构体设置参数
                m_SWRtx = swr_alloc_set_opts(m_SWRtx, av_get_default_channel_layout(2), AV_SAMPLE_FMT_S16,
                                             sanmple, channellayout, contextAudio->sample_fmt, sanmple, 0, 0);
                if (m_SWRtx == NULL) {
                    return 1;
                }
                //初始化结构体
                int re = swr_init(m_SWRtx);
                if (re != 0)
                {
                    return 0;
                }
                //申请AVFrame，存储解码后的像素数据
                frameAudio = av_frame_alloc();
                if (!frameAudio) {
                    cout << "申请frame失败" << endl;
                    exit(1);
                }
                //创建缓冲区
                pcm  = new char[48000 * 4 * 2];
                out[0] = (uint8_t*)pcm;
                //音频解码
                //一定要将解码器的时基设置为流的时基
                contextAudio->pkt_timebase = formatContext->streams[streamIndexAudio]->time_base;
                //SDLaudioinit_______________________________________________________
                if (SDL_Init(SDL_INIT_AUDIO )) {
                    printf("Could not initialize SDL - %s\n", SDL_GetError());
                    return 1;
                }
                //创建音频解码线程
                SDL_CreateThread(decodeAudio, NULL, NULL);

                //采样率
                wanted_spec.freq=contextAudio->sample_rate;
                //采样格式（每次采样的大小）
                wanted_spec.format = AUDIO_S16SYS;
                //声道数
                wanted_spec.channels = 2;
                //静音值
                wanted_spec.silence = 0;
                //播放MP3 wma使用1152
                //播放AAC，M4a，缓冲区的大小 1024,每个声道的采样数
                wanted_spec.samples = (contextAudio->frame_size == 0 ? 1024 : contextAudio->frame_size);
                wanted_spec.size = 8*1024;
                //回调函数
                wanted_spec.callback = fill_audio;
                wanted_spec.userdata = contextAudio;
                if (SDL_OpenAudio(&wanted_spec, NULL) < 0) {
                    return 1;
                }
                //开始播放音频
                SDL_PauseAudio(0);
                //SDLINIT结束_______________________________________________________
            }
            else {
                //其它流
            }
        }
        while (av_read_frame(formatContext, packet) == 0&&quitFlag) {
            if (packet->stream_index == streamIndexVideo) {
                //发送到视频队列
                pushToPacketQueue(packet, videoPacketQueue);
            }
            //判断是否是音频
            if (packet->stream_index == streamIndexAudio) {
                //把packet发送到音频队列
                pushToPacketQueue(packet, audioPacketQueue);
            }
        }
        quitflag0=true;
        av_packet_free(&packet);
    }
    else {
        cout << "解码失败" << endl;
    }
    avformat_free_context(formatContext);
    formatContext=NULL;
    return 0;
}
//初始化sdl
void initSDLInfo(SDLVideoInfo* sdlVideoInfo,QWidget * data) {
    //sdl+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ sdl initkai
    sdlVideoInfo->renderFlag = false;
    sdlVideoInfo->mutex= SDL_CreateMutex();
    sdlVideoInfo->status = false;
    sdlVideoInfo->time = 40;
    if (SDL_Init(SDL_INIT_VIDEO)){
        printf("Could not initialize SDL - %s\n", SDL_GetError());
        return;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    //通过qt窗口创建窗口
    sdlVideoInfo->window = SDL_CreateWindowFrom((void *)data->winId());
    data->setUpdatesEnabled(false);
    SDL_ShowWindow(sdlVideoInfo->window);
    //创建渲染器，指定模式
    sdlVideoInfo->screen_w= data->width();
    sdlVideoInfo->screen_h=data->height();
    sdlVideoInfo->sdlRect=new SDL_Rect;
    sdlVideoInfo->render = SDL_CreateRenderer(sdlVideoInfo->window, -1, SDL_RENDERER_TARGETTEXTURE);
    //创建纹理
    //IYUV: Y + U + V  (3 planes)
    //YV12: Y + V + U  (3 planes)
    sdlVideoInfo->pixformat = SDL_PIXELFORMAT_IYUV;
    sdlVideoInfo->texture = SDL_CreateTexture(sdlVideoInfo->render, sdlVideoInfo->pixformat, SDL_TEXTUREACCESS_STREAMING, pixel_w,pixel_h );
}
//视频渲染方法
int renderVideo(void* sdlVideoInfos) {
    //页面渲染线程，进行视频渲染,循环渲染
    //sdl显示+++++++++++++++++++++++++++++++++++++++
    SDLVideoInfo* sdlVideoInfo = (SDLVideoInfo*)sdlVideoInfos;
    SDL_Event event;
    event.type = REFRESH_EVENT;
    while (quitFlag) {
        SDL_PushEvent(&event);
        //等待40秒，可以用来控制播放速度
        SDL_Delay(sdlVideoInfo->time/speed);
        SDL_LockMutex(sdlVideoInfo->mutex);
        //根据标记决定是否渲染
        if (sdlVideoInfo->renderFlag) {
            SDL_UpdateTexture(sdlVideoInfo->texture, NULL, sdlVideoInfo->pAVFrameYUV420P->data[0], sdlVideoInfo->pAVFrameYUV420P->linesize[0]);
            //设置绘制区域的大小和位置
            calculate_display_rect(sdlVideoInfo->sdlRect,0,0,sdlVideoInfo->screen_w,sdlVideoInfo->screen_h,pixel_w,pixel_h,sdlVideoInfo->pAVFrameYUV420P->sample_aspect_ratio);
            //清空渲染器
            SDL_RenderClear(sdlVideoInfo->render);
            //把数据渲染到显示器
            SDL_RenderCopy(sdlVideoInfo->render, sdlVideoInfo->texture, NULL, sdlVideoInfo->sdlRect);
            //渲染显示
            SDL_RenderPresent(sdlVideoInfo->render);
            //修改标记,避免重复渲染
            sdlVideoInfo->renderFlag = false;
        }
        SDL_UnlockMutex(sdlVideoInfo->mutex);
        while (sdlVideoInfo->status){
        }
    }
    quitflag1=true;
    return 0;
}
//音频播放回调方法
void  fill_audio(void *udata, Uint8 *stream, int len) {
    //SDL 2.0
    SDL_memset(stream, 0, len);
    if (audio_len == 0)
        return;
    len = (len > audio_len ? audio_len : len);
    //从解码缓冲区复制len长度到sdl缓冲区（可以理解为声卡缓冲区）
    SDL_MixAudio(stream, audio_pos, len,volume);
    //移动播放位置
    audio_pos += len;
    //减少播放的长度
    audio_len -= len;
}
//音频渲染方法
void renderAudio(){
    audio_chunk = pcm_buffer;
    //Audio buffer length
    //解码一帧视频的长度
    audio_len = pcm_buffer_size;
    //解码后视频的缓冲区
    audio_pos = audio_chunk;
    while (audio_len > 0)//等待直到一帧视频播放完再解码
    {
        if(!quitFlag){
            return ;
        }
    }

    return ;
}
//视频解码方法
int decodeVideo(void *opaque) {
    //从视频队列中取出packet进行解码

    AVPacket * videoPack = av_packet_alloc();
    while (quitFlag) {
        SDL_WaitEvent(&sdlVideoInfo->event);
        if (sdlVideoInfo->event.type == REFRESH_EVENT) {
            //从队列中获取packet
            int res=popFromPacketQueue(videoPacketQueue, videoPack);
            if (res==1) {
                int result= avcodec_send_packet(context, videoPack);
                if(result!=0){
                    return 1;
                }
                //解码一帧数据
                yet = avcodec_receive_frame(context, frame);
                if (yet == 0)  //解码成功
                {
                    //将图像转成yuv
                    sws_scale(swsContext, (const uint8_t * const *)frame->data,
                              frame->linesize,
                              0,
                              pixel_h,
                              pAVFrameYUV420P->data,
                              pAVFrameYUV420P->linesize);
                    //解码完一帧后更新渲染的一帧数据
                    SDL_LockMutex(sdlVideoInfo->mutex);
                    sdlVideoInfo->pAVFrameYUV420P = pAVFrameYUV420P;
                    //更新标记让渲染线程进行渲染
                    sdlVideoInfo->renderFlag = true;
                    SDL_UnlockMutex(sdlVideoInfo->mutex);
                }

            }

        }
        else if (sdlVideoInfo->event.type == SDL_WINDOWEVENT) {
            switch (sdlVideoInfo->event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                //让画面按比例缩放
                SDL_GetWindowSize(sdlVideoInfo->window,&sdlVideoInfo->screen_w,&sdlVideoInfo->screen_h);
                SDL_SetWindowSize(sdlVideoInfo->window,sdlVideoInfo->screen_w,sdlVideoInfo->screen_h);
                SDL_LockMutex(sdlVideoInfo->mutex);
                SDL_RenderClear(sdlVideoInfo->render);
                SDL_DestroyRenderer(sdlVideoInfo->render);
                SDL_DestroyTexture(sdlVideoInfo->texture);
                sdlVideoInfo->render = SDL_CreateRenderer(sdlVideoInfo->window, -1, SDL_RENDERER_TARGETTEXTURE);
                sdlVideoInfo->texture = SDL_CreateTexture(sdlVideoInfo->render, sdlVideoInfo->pixformat, SDL_TEXTUREACCESS_STREAMING, pixel_w,pixel_h );
                if(audioStatus){
                    SDL_RenderClear(sdlVideoInfo->render);
                    //暂停了，需要手动进行一次渲染
                    SDL_UpdateTexture(sdlVideoInfo->texture, NULL, sdlVideoInfo->pAVFrameYUV420P->data[0], sdlVideoInfo->pAVFrameYUV420P->linesize[0]);
                    //设置绘制区域的大小和位置
                    calculate_display_rect(sdlVideoInfo->sdlRect,0,0,sdlVideoInfo->screen_w,sdlVideoInfo->screen_h,pixel_w,pixel_h,sdlVideoInfo->pAVFrameYUV420P->sample_aspect_ratio);
                    //把数据渲染到显示器
                    SDL_RenderCopy(sdlVideoInfo->render, sdlVideoInfo->texture, NULL, sdlVideoInfo->sdlRect);
                    //渲染显示
                    SDL_RenderPresent(sdlVideoInfo->render);
                    renderFlag=true;
                }
                SDL_UnlockMutex(sdlVideoInfo->mutex);
                break;
            default:break;
            }

        }
    }
    av_packet_free(&videoPack);
    quitflag2=true;
    return 0;
}
//音频解码方法
int decodeAudio(void *opaque){
    sonicSetSpeed(stream, speed);
    sonicSetPitch(stream, 1.0);
    sonicSetRate(stream, 1.0);
    sonicSetChordPitch(stream, 1.0);
    sonicSetQuality(stream, 0);
    AVPacket* audioPack = av_packet_alloc();
    //从音频队列中取出音频进行解码
    while (quitFlag) {
        sonicSetSpeed(stream, speed);
        while (audioStatus) {
        }
        int res= popFromPacketQueue(audioPacketQueue, audioPack);
        if (res==1){
            int a = avcodec_send_packet(contextAudio, audioPack);
            if(a!=0){
                return 0;
            }
            //解码一帧数据
            yetAudio = avcodec_receive_frame(contextAudio, frameAudio);
            if (yetAudio == 0) //解码成功
            {
                //对视频进行重采样
                //将数据写入缓冲区
                swr_convert(m_SWRtx, out, frameAudio->nb_samples, (const uint8_t **)frameAudio->extended_data,
                            frameAudio->nb_samples);
                //缓冲区的大小
                int out_buffer_size = av_samples_get_buffer_size(NULL, 2, frameAudio->nb_samples,
                                                                 AV_SAMPLE_FMT_S16, 1);
                pcm_buffer= out[0];
                //如果这里还有pcm的数据需要送入：
                int ret= sonicWriteShortToStream(stream,(short *)pcm_buffer,out_buffer_size/(sizeof (short)*sonicGetNumChannels(stream)));
                int couldReadSamples = sonicSamplesAvailable(stream)* sizeof(short) * sonicGetNumChannels(stream);
                if (out_buffer_size>couldReadSamples) {
                    out_buffer_size=couldReadSamples;
                }
                int samplesRead = sonicReadShortFromStream(stream,(short *)pcm_buffer, out_buffer_size/(sizeof(short)*sonicGetNumChannels(stream))  );
                int bytesRead = samplesRead * sizeof(short) * sonicGetNumChannels(stream);
                pcm_buffer_size = bytesRead;
                //当前音频播放时长
                playingTime=pts*frameAudio->pts;
                //音频渲染_____________________________________________________________________________
                renderAudio();
                //音频渲染___________________________
            }

        }
    }
    av_packet_free(&audioPack);
    quitflag3=true;
    return 0;
}
//从队首弹出AvPacket
int popFromPacketQueue(PacketQueue* packetQueue, AVPacket * avPacket) {
    if(packetQueue==NULL){
        return 0;
    }
    AVPacketList *node;
    node = packetQueue->first_pkt;
    //加锁
    SDL_LockMutex(packetQueue->mutex);
    if (node){
        packetQueue->first_pkt = node->next;
        if (!packetQueue->first_pkt) {
            packetQueue->last_pkt = NULL;
        }
        *avPacket = node->pkt;
        //从队头弹出一个
        packetQueue->nb_packets--;
        SDL_UnlockMutex(packetQueue->mutex);
        return  1;
    }
    else {
        SDL_UnlockMutex(packetQueue->mutex);
        return 0;
    }


}
//从队尾压入avPacket
void pushToPacketQueue(AVPacket * aVPacket, PacketQueue* packetQueue) {
    if(packetQueue==NULL){
        return ;
    }
    if (aVPacket != NULL && aVPacket->data != NULL) {
        //从队尾压入AVPacket
        AVPacketList* aVPacketList = new AVPacketList;
        //加锁
        SDL_LockMutex(packetQueue->mutex);
        aVPacketList->pkt = *aVPacket;
        aVPacketList->next = NULL;
        if (packetQueue->last_pkt == NULL) {
            //队列为空，放入队头
            packetQueue->first_pkt = aVPacketList;
        }
        else {
            //队列非空放入队尾
            packetQueue->last_pkt->next = aVPacketList;
        }
        packetQueue->last_pkt = aVPacketList;
        packetQueue->nb_packets++;
        SDL_UnlockMutex(packetQueue->mutex);
    }
}
//初始化AvPacket队列
void initpacketQueue(packetQueue* packetQueue) {
    memset(packetQueue, 0, sizeof(PacketQueue));
    packetQueue->first_pkt = NULL;
    packetQueue->last_pkt = NULL;
    packetQueue->mutex = SDL_CreateMutex();
    packetQueue->nb_packets = 0;
}
int  getVideoImage(const char* inputFIleName) {
    int yet=0;
    //编码器上下文
    AVCodecContext * context;
    //解码前的数据（h.264数据）
    AVPacket *packet;
    //解码后的数据（yuv图像数据）
    AVFrame * frame;
    //初始化解码器 0为成功  负数为失败
    int successAVCodec;
    //编解码器
    AVCodec * aVCodec;
    //编解码器参数
    AVCodecParameters * codecContext;
    //视频文件信息上下文
    AVFormatContext* formatContext;
    formatContext = avformat_alloc_context();
    //文件是否打开成功，0为成功，否则失败
    int success;
    //是否获得数据流，>=0,成功获取，否则获取失败
    int streamId;
    //视频流的索引
    int videoindex;
    //编解码器的id
    AVCodecID codecId;
    success = avformat_open_input(&formatContext, inputFIleName, NULL, NULL);
    //打开文件成功
    if (success == 0) {
        //获取流信息，如果返回<0表示没有获得流
        streamId = avformat_find_stream_info(formatContext, NULL);
        if (streamId < 0) {
            return 0;
        }
        videoindex = -1;
        //根据formatContext中的流数量（视频流或音频流），循环查找
        for ( unsigned int i = 0; i < formatContext->nb_streams; i++)
        {
            //判断每个流中的编解码器类型是否为视频类型
            if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                //获取到视频解码器，对应流的索引
                videoindex = i;
                break;
            }
        }
        //没有获取到视频流
        if (videoindex == -1)
        {
            return 0;
        }
        //获取到了视频流
        //根据视频流索引，获取对应的编解码上下文
        codecContext = formatContext->streams[videoindex]->codecpar;
        //根据解码器上下文查找已经注册的解码器的id
        codecId = codecContext->codec_id;
        //获取解码器
        aVCodec = avcodec_find_decoder(codecId);
        //申请avcodeccontext
        context = avcodec_alloc_context3(NULL);
        //绑定编码器
        avcodec_parameters_to_context(context, codecContext);
        if (!context) {
            exit(1);
        }
        //打开编码器
        successAVCodec = avcodec_open2(context, aVCodec, NULL);
        if (successAVCodec < 0) {
            //打开编解码器失败
            return 0;
        }
        //申请packet存放一帧压缩数据
        packet = av_packet_alloc();
        if (!packet) {
            exit(1);
        }
        //申请AVFrame，存储解码后的像素数据
        frame = av_frame_alloc();
        if (!frame) {
            exit(1);
        }
        struct SwsContext *swsContext = sws_getContext(codecContext->width, codecContext->height,
                                                       context->pix_fmt, codecContext->width, codecContext->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
        rgb = av_frame_alloc();
        int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_BGR24,
                                                  context->width,
                                                  context->height,
                                                  1);
        //开辟一块内存空间

        uint8_t *outBuffer = (uint8_t *)av_malloc(bufferSize);
        av_image_fill_arrays(rgb->data,
                             rgb->linesize,
                             outBuffer,
                             AV_PIX_FMT_BGR24,
                             context->width,
                             context->height,
                             1);
        pictureWidth=context->width;
        pictureHeight=context->height;
        //视频解码（循环获取数据（压缩前的数据）到packet）
        //跳到指定帧，防止空白画面
        double sec = 5;
        int64_t pts = sec /av_q2d(formatContext->streams[videoindex]->time_base);
        av_seek_frame(formatContext,videoindex,pts,AVSEEK_FLAG_BACKWARD);
        while (av_read_frame(formatContext, packet) >= 0)
        {
            //判断是不是视频
            if (packet->stream_index == videoindex)
            {
                avcodec_send_packet(context, packet);
                //解码一帧数据
                yet = avcodec_receive_frame(context, frame);
                if (yet == 0)  //解码成功
                {
                    sws_scale(swsContext, (const uint8_t * const *)frame->data,
                              frame->linesize,
                              0,
                              context->height,
                              rgb->data,
                              rgb->linesize);
                    //释放内存
                    av_frame_free(&frame);
                    avcodec_free_context(&context);
                    avformat_free_context(formatContext);
                    return 0;
                }
            }

        }
    }
    else {
        cout << "解码失败" << endl;
    }
    return 0;
}
void freeAudioMemory(){
    //释放资源
    if(audioPacketQueue){
        packet_queue_destroy(audioPacketQueue);
    }
    av_frame_free(&frameAudio);
    avcodec_free_context(&contextAudio);
    if(pcm){
        delete pcm;
        pcm=NULL;
    }
    av_freep(&aVCodecAudio);
    for (int i = 0; i < 2; i++)
    {
        out[i]=0;

    }
    //    if(m_SWRtx){
    //      swr_free(&m_SWRtx);
    //      m_SWRtx=NULL;
    //    }

    audio_chunk=NULL;
    audio_len=0;
    audio_pos=NULL;
    pcm_buffer=NULL;
    pcm_buffer_size=0;
}
string getFileType(string filePath){
    AVFormatContext* formatContext;
    formatContext = avformat_alloc_context();
    const char* filename=filePath.c_str();
    int success = avformat_open_input(&formatContext,filename, NULL, NULL);
    //打开文件成功
    int videoIndex=-1;
    int audioIndex=-1;
    if (success == 0) {
        //获取流信息，如果返回<0表示没有获得流
        streamId = avformat_find_stream_info(formatContext, NULL);
        if (streamId < 0) {
            //未知类型
            return "unknow";
        }
        //根据formatContext中的流数量（视频流或音频流），循环查找
        for ( unsigned int i = 0; i < formatContext->nb_streams; i++)
        {
            //判断每个流中的编解码器类型是否为视频类型
            if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                //视频流
                videoIndex=i;
            }
            if(formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO){
                //音频流
                audioIndex=i;
            }
        }
        avformat_free_context(formatContext);
        if(videoIndex!=-1&&audioIndex!=-1){
            //视频+音频
            return "video";
        }
        if(videoIndex==-1&&audioIndex!=-1){
            //音频
            return "audio";
        }
        if(videoIndex!=-1&&audioIndex==-1){
            return "yuv";
        }

    }
    avformat_free_context(formatContext);
    return "unknow";
}
long long getFileTime(string filePath){
    AVFormatContext* formatContext;
    formatContext = avformat_alloc_context();
    const char* filename=filePath.c_str();
    int success=avformat_open_input(&formatContext,filename, NULL, NULL);
    if(success==0){
        streamId = avformat_find_stream_info(formatContext, NULL);
        if (streamId < 0) {
            cout << "获取流失败" << endl;
            return 0;
        }
        long long time= formatContext->duration/AV_TIME_BASE;
        avformat_free_context(formatContext);
        return time;
    }
    avformat_free_context(formatContext);
    return 0;
}
//视频退出
void quitVideo(){
    widget->setUpdatesEnabled(true);
    quitFlag=false;
    SDL_CloseAudio();
    SDL_DestroyWindow(sdlVideoInfo->window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    while(true){
        if(quitflag0==true&&quitflag1==true&&quitflag2==true&&quitflag3==true){
            freeAudioMemory();
            freeVideoMemory();
            break;
        }
    }
    quitflag0=false;
    quitflag1=false;
    quitflag2=false;
    quitflag3=false;
};
//音频退出
void quitAudio(){
    quitFlag=false;
    SDL_CloseAudio();
    while(true){
        if(quitflag0==true&&quitflag3==true){
            freeAudioMemory();
            break;
        }
    }
    quitflag0=false;
    quitflag3=false;
}
void freeVideoMemory(){
    if(outBuffer){
        outBuffer=NULL;
    }
    //可能出错
    //    if(swsContext){
    //         sws_freeContext(swsContext);
    //         swsContext=NULL;
    //     }
    //释放资源
    if(videoPacketQueue){
        packet_queue_destroy(videoPacketQueue);
    }
    if(sdlVideoInfo){
        delete sdlVideoInfo->sdlRect;
        sdlVideoInfo->sdlRect=NULL;
        SDL_DestroyRenderer(sdlVideoInfo->render);
        SDL_DestroyTexture(sdlVideoInfo->texture);
        SDL_DestroyMutex(sdlVideoInfo->mutex);
        sdlVideoInfo=NULL;
    }
    av_frame_free(&frame);
    av_frame_free(&pAVFrameYUV420P);
    avcodec_free_context(&context);

}
//释放packetqueue
void packet_queue_destroy(PacketQueue *q)
{
    packet_queue_flush(q);
    SDL_DestroyMutex(q->mutex);

}
void packet_queue_flush(PacketQueue *q)
{
    int i=0;
    AVPacketList *pkt, *pkt1;
    SDL_LockMutex(q->mutex);
    for (pkt = q->first_pkt; pkt; pkt = pkt1) {
        i++;
        pkt1 = pkt->next;
        av_packet_unref(&pkt->pkt);
        av_freep(pkt);
    }
    q->last_pkt = NULL;
    q->first_pkt = NULL;
    q->nb_packets = 0;
    SDL_UnlockMutex(q->mutex);
}

