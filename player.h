#ifndef PLAYER_H
#define PLAYER_H
#include "SDL.h"
extern "C" {
#include "libswscale/swscale.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/imgutils.h"
#include <libavutil/opt.h>
#include <libavutil/samplefmt.h>
#include <libswresample/swresample.h>
#include "sonic.h"
}
#include<QWidget>
#include<string>
#include<iostream>
#include<cstdio>
//成员变量声明
using namespace std;
#define REFRESH_EVENT  (SDL_USEREVENT + 1)
#define BREAK_EVENT  (SDL_USEREVENT + 2)
typedef struct PacketQueue {
    AVPacketList *first_pkt;
    AVPacketList *last_pkt;
    // 队列中AVPacket的个数
    int nb_packets;
    // 队列中AVPacket总的大小(字节数)
    //sdl互斥锁
    SDL_mutex *mutex;
    //信号
    SDL_cond *cond;
} packetQueue;
//SDLinfo结构体
typedef struct SDLVideoInfo {
    //用来控制视频的播放和暂停
    volatile  bool status ;
    //用来控制视频的播放速度
    volatile int time ;
    //屏幕的宽高
    int screen_w, screen_h;
    //图片的像素
    //int pixel_w, pixel_h;

    SDL_Window *window;
    //渲染器
    SDL_Renderer *render;
    //纹理
    SDL_Texture *texture;
    //矩形区域
    SDL_Rect *sdlRect;
    //sdl事件
    SDL_Event  event;
    Uint32 pixformat;
    //一帧视频数据,用于更新视频帧
    AVFrame *pAVFrameYUV420P;
    //渲染标记，决定是否渲染
    volatile bool renderFlag;
    SDL_mutex *mutex;

} SDLVideoInfo;
extern int countFlag;
extern bool renderFlag;
extern Uint8 * pcm_buffer;
extern int pcm_buffer_size;
extern int yet ;
extern int yetAudio;
extern volatile bool quitFlag;
extern volatile bool audioStatus;
extern volatile double speed;
//是否播放
extern int volume;
//编码器上下文
extern AVCodecContext * context ;
extern AVCodecContext * contextAudio ;
//解码前的数据（h.264数据）
extern AVPacket *packet ;
//解码后的数据（yuv图像数据）
extern AVFrame * frame ;
extern AVFrame * frameAudio ;
//初始化解码器 0为成功  负数为失败
extern int streamIndexAudio ;
extern int streamIndexVideo ;
extern int successAVCodec ;
extern int successAVCodecAudio ;
//编解码器
//视频时长
extern long long duration;
extern AVCodec * aVCodec ;
extern AVCodec * aVCodecAudio ;
//编解码器参数
extern AVCodecParameters * codecContext ;
extern AVCodecParameters * codecContextAudio ;
extern int pixel_w , pixel_h ;
//视频文件信息上下文
extern AVFormatContext* formatContext ;
extern int success;
//是否获得数据流，>=0,成功获取，否则获取失败
extern int streamId ;
//编解码器的id
extern AVCodecID codecId;
extern AVCodecID codecIdAudio;
extern uint8_t *outBuffer;
extern SwrContext *m_SWRtx;
extern SDL_Thread * threadRender;
extern AVFrame *pAVFrameYUV420P;
extern uint8_t * out[2] ;
extern AVFrame *rgb;
extern int pictureWidth;
extern int pictureHeight;
extern SDL_AudioSpec wanted_spec;
extern PacketQueue*  videoPacketQueue;
extern PacketQueue*  audioPacketQueue;
extern SDLVideoInfo * sdlVideoInfo;
extern struct SwsContext *swsContext;
extern long long playingTime;
int mutexVideo(const char* inputFIleName,QWidget* data);
int decodeAudio(void *opaque);
int decodeVideo(void *opaque);
void initpacketQueue(packetQueue* packetQueue);
void renderAudio();
void fill_audio(void *udata, Uint8 *stream, int len);
void initSDLInfo(SDLVideoInfo* sdlVideoInfo, QWidget * data);
int renderVideo(void*  sdlVideoInfo);
void pushToPacketQueue(AVPacket * aVPacket, PacketQueue* packetQueue);
int popFromPacketQueue(PacketQueue* packetQueue, AVPacket * avPacket);
int  getVideoImage(const char* inputFIleName);
void freeAudioMemory();
void freeVideoMemory();
void quitVideo();
void quitAudio();
void calculate_display_rect(SDL_Rect *rect,
                            int scr_xleft, int scr_ytop, int scr_width, int scr_height,
                            int pic_width, int pic_height, AVRational pic_sar);
string getFileType(string filePath);
void packet_queue_destroy(PacketQueue *q);
void packet_queue_flush(PacketQueue *q);
long long getFileTime(string filePath);
#endif // PLAYER_H
