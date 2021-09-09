#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mylistwidget.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    //去除系统标题栏
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    //开启鼠标跟踪
    setAttribute(Qt::WA_Hover,true);
    ui->widget_2->setAttribute(Qt::WA_Hover,true);
    initPlayer();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete qtimer;
    delete clickedTimer;
    delete hiddenVideoListTimer;
    delete playModelMenu;
}
//绘图过滤器
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched ==this){
        if(event->type()==QEvent::Move){
            int x=geometry().x()+ui->widget_2->width()-transWidget->width();
            int y=geometry().y()+ui->widget_12->height()+(ui->widget_2->height()-transWidget->width())/2;
            transWidget->move(x,y);

        }
        if(event->type()==QEvent::WindowDeactivate){
            //处理窗口失去焦点后刷新卡顿，tooltip的弹出
            if(!isActiveWindow()){
                //hide();
                activateWindow();
                raise();
                show();
            }
        }
        if(event->type()==QEvent::HoverEnter||event->type()==QEvent::HoverMove||event->type()==QEvent::HoverLeave){
            QHoverEvent * even=( QHoverEvent *)event;
            if (isMaximized())
            {
               return QWidget::eventFilter(watched,event);
            }

            // 如果当前鼠标未按下，则根据当前鼠标的位置更新鼠标的状态及样式;
            if (!m_isMousePressed)
            {
                QPoint cursorPos = even->pos();
                // 根据当前鼠标的位置显示不同的样式;
                m_stretchRectState = getCurrentStretchState(cursorPos);
                updateMouseStyle(m_stretchRectState);
            }
            // 如果当前鼠标左键已经按下，则记录下第二个点的位置，并更新窗口的大小;
            else
            {
                m_endPoint = this->mapToGlobal(even->pos());
                //拉伸窗口
                updateWindowSize();
            }
            //return __super::mouseMoveEvent(event);

        }
    }
    if(watched ==transWidget->button){
        if(event->type()==QEvent::MouseButtonPress){
            if(ui->widget_3->isHidden()){
                ui->widget_3->show();
                transWidget->button->setIcon(QIcon(":/player/picture/player/fanhui.png"));
            }else{
                transWidget->button->setIcon(QIcon(":/player/picture/player/toumingfanhui.png"));
                ui->widget_3->hide();
            }
            return true;
        }
    }
    if(watched ==ui->widget_2)
    {
        if(event->type()==QEvent::MouseButtonPress){
            clickedTimer->start(300);
        }
        if(event->type()==QEvent::Paint){
            graphChart(ui->widget_2);
            if(messageFlag){
                //绘制消息提示框
                graphMessageBox(ui->widget_2);
            }
        }
        if(event->type()==QEvent::MouseButtonDblClick){
            doubleClicked=true;
            if(playingType=="audio"&&audioStatus){
                //音频正在暂停，会自动渲染一次
                boolFlag=true;
            }
            //线程等待
            if (isMaximized())
            {
                this->showNormal();
                ui->widget_2->resize(_previewInitSize);
                ui->widget_2->move(_previewInitPoit);
            }
            else
            {
                this->showMaximized();
                ui->widget_2->resize(this->size());
                ui->widget_2->move(0, 0);
            }
            return false;
        }
        if(event->type()==QEvent::Resize){
            if(playingType=="audio"&&audioStatus){
                //音频正在暂停，会自动渲染一次
                boolFlag=true;
            };
            int x=geometry().x()+ui->widget_2->width()-transWidget->width();
            int y=geometry().y()+ui->widget_12->height()+(ui->widget_2->height()-transWidget->width())/2;
            transWidget->move(x,y);
        }
        if(event->type()==QEvent::HoverMove){
            //定时显示透明窗体
            if(audioStatus&&playingType=="audio")
            {
                boolFlag=true;
            }
            if(transWidget->isHidden()){
                transWidget->show();
            }
            if(!hiddenVideoListTimer->isActive()){
                hiddenVideoListTimer->start(5000);
            }

        }
    }
    if(watched==ui->label_2){
        if(event->type()==QEvent::Paint){
            ui->label_2->move((ui->widget_2->width()-ui->label_2->width())*0.5,(ui->widget_12->height()-ui->label_2->height())*0.5);
        }
        if(event->type()==QEvent::MouseMove){
            event->ignore();
        }
        if(event->type()==QEvent::MouseButtonRelease){
            event->ignore();
        }
    }
    return QWidget::eventFilter(watched,event);
}
//绘图
void MainWindow::graphChart(QWidget *w)
{
    if(boolFlag){
        painter = new QPainter();
        painter->begin(w);
        if(imageRotate++ == 360)
            imageRotate = 0;
        /* 设定旋转中心点 */
        painter->translate(w->width()/2,w->height()/2);
        /* 旋转的角度 */
        painter->rotate(imageRotate);
        /* 恢复中心点 */
        painter->translate(-w->width()/2,-w->height()/2);
        painter->drawPixmap((w->width()-210)/2,(w->height()-210)/2,QPixmap(":/player/picture/player/zhuanji.png"));
        painter->end();
        ui->widget_2->setMouseTracking(true);
    }
}
void MainWindow::graphMessageBox(QWidget *w){
    painter = new QPainter();
    painter->begin(w);
    painter->setPen(Qt::white);
    //设置字体大小
    QFont font = painter->font();
    font.setPixelSize(14);//改变字体大小
    font.setFamily("Microsoft YaHei");
    painter->setFont(font);
    QStaticText text(QString::fromLocal8Bit("当前没有播放文件"));
    text.setTextWidth(120);
    painter->drawStaticText(50,w->height()-50,text);
    painter->end();
    messageFlag=false;
};
void MainWindow::openFile(){
    QString filePath=QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("打开文件"),"C:\\Users\\zhangpeng\\Desktop"
                                                  ,"videos(*.*)");
    if(filePath==NULL||findVideoList(filePath)){
        //没有选择或者已经存在
        return ;
    }
    //判断打开文件的类型
    string fileType=getFileType(filePath.toStdString());
    QPixmap pixmap;
    if(fileType=="unknow"){
        //弹出不支持格式的提示窗口
        return;
    }else{
        if(fileType=="audio"){
            pixmap= QPixmap(":/player/picture/player/music.png");
        }else if(fileType=="yuv"||fileType=="video"){
            //截取一帧图片和时间
            getVideoImage(filePath.toStdString().c_str());
            QImage qimage(rgb->data[0],pictureWidth,pictureHeight,QImage::Format_BGR888);
            pixmap=QPixmap::fromImage(qimage);
            av_frame_free(&rgb);
            rgb=NULL;
        }
    }
    //格式化时间
    long long duration=getFileTime(filePath.toStdString());
    QString time=formartTime(duration);
    //获取文件信息
    QFileInfo* fileInfo=new QFileInfo(filePath);
    //获得文件名
    QString fileName=fileInfo->fileName();
    //获取文件时长和第一帧图片
    //创建 QListWidgetItem（缩虐图列表）
    QListWidgetItem *imageItem = new QListWidgetItem();
    //设置文件名
    //获取视频缩略图和视频时长
    QSize qSize(200,70);
    MyListWidget * myListWidget=new MyListWidget(fileName,time,&pixmap,this,imageItem);
    //保存filepath
    myListWidget->setMouseTracking(true);
    myListWidget->filePath=filePath;
    //保存filetype
    myListWidget->fileType=QString::fromStdString(fileType);
    //保存时长
    myListWidget->duration=duration;
    imageItem->setSizeHint(qSize);
    ui->listWidget->addItem(imageItem);
    ui->listWidget->setItemWidget(imageItem,myListWidget);
    ui->listWidget->show();
    //通过双向循环列表，保存视频列表
    //从尾部插入到list列表
    videoList.push_back(filePath);
}
//打开文件
void MainWindow::on_toolButton_2_clicked()
{
    openFile();
}
QString MainWindow::formartTime(long long time){
    int hou=time/3600;
    int min= (time-(time/3600*3600))/60;
    int sec=(time-(time/3600*3600)-(time-(time/3600*3600))/60*60);
    string hour;
    string minute;
    string second;
    if(hou<10){
        hour= "0"+to_string(hou);
    }
    else{
        hour=to_string(hou);
    }if(min<10){
        minute="0"+to_string(min);
    }else{
        minute=to_string(min);
    }if(sec<10)
    {
        second=  "0"+to_string(sec);
    }else{
        second=to_string(sec);
    }
    string temp=hour+":"+minute+":"+second;
    return QString::fromStdString(temp);
}
//双击播放
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    MyListWidget*widget=( MyListWidget*)ui->listWidget->itemWidget(item);
    QString filePath= widget->filePath;
    QString fileType= widget->fileType;
    long long duration=widget->duration;
    //重新设置样式
    ui->widget_2->setStyleSheet(QString("background-color: rgb(10,10 , 10)"));
    ui->toolButton_10->setHidden(true);

    if(playingType!="null"){
        //正在播放，需要关闭资源
        if(playingType=="audio"){
            if(audioStatus){
                //正在暂停，退出暂停
                audioStatus=false;
            }
            if(qtimer->isActive()){
                boolFlag=false;
                qtimer->stop();
            }
            quitAudio();
        }
        if(playingType=="video"){
            if(audioStatus&&sdlVideoInfo->status){
                //正在暂停，退出暂停
                audioStatus=false;
                sdlVideoInfo->status=false;
            }
            quitVideo();
        }
        quitFlag=true;
    }
    if(fileType.toStdString()=="audio"){
        //渲染播放图片
        boolFlag=true;
        translatePic();
        ui->centralwidget->setMouseTracking(true);
        ui->widget_11->setMouseTracking(true);
        ui->widget_2->setMouseTracking(true);
    }else{
        //播放视频关闭播放图片渲染
        boolFlag=false;
        if(qtimer->isActive()){
            qtimer->stop();
        }
    }
    //记录当前播放的类型
    playingPath=filePath;
    playingType=fileType.toStdString();
    //修改图标
    ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media play .png"));
    ui->toolButton_7->setToolTip(QString::fromLocal8Bit("暂停"));
    ui->label_2->setText(widget->fileName);
    ui->label_2->repaint();
    mutexVideo(filePath.toStdString().c_str(),ui->widget_2);
    showPlayingTime(duration);
}
//清空播放列表
void MainWindow::on_toolButton_clicked()
{
    //开启qt渲染
    if(playingType!="null"){
        closeShowPlayingTime();
        if(playingType=="audio"){
            if(audioStatus){
                //正在暂停，退出暂停
                audioStatus=false;
            }
            quitAudio();
            //关闭播放图片渲染和定时器
            boolFlag=false;
            if(qtimer->isActive()){
                qtimer->stop();
            }
        }
        if(playingType=="video"||playingType=="yuv"){
            if(audioStatus&&sdlVideoInfo->status){
                //正在暂停，退出暂停
                audioStatus=false;
                sdlVideoInfo->status=false;
            }
            ui->widget_2->setAttribute(Qt::WA_PaintOnScreen,false);
            //打开qt渲染
            quitVideo();
        }
        quitFlag=true;
        playingType="null";
        //修改样式
        ui->widget_2->setStyleSheet(QString("#widget_2{border-image: url(:/pic/picture/bg.jpg)}"));
        ui->label_2->setText("");
    }
    ui->listWidget->clear();
    //清空videolist列表
    if(!videoList.empty()){
        videoList.clear();
    }
    ui->toolButton_10->setHidden(false);
    ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media-pause.png"));
    ui->toolButton_7->setToolTip(QString::fromLocal8Bit("播放"));
    ui->widget_2->setAttribute(Qt::WA_PaintOnScreen,false);
    ui->label->setHidden(true);
    playingPath="null";
}
//停止播放
void MainWindow::on_toolButton_6_clicked()
{
    if(playingType!="null"){
        closeShowPlayingTime();
        if(playingType=="audio"){
            if(audioStatus){
                //正在暂停，退出暂停
                audioStatus=false;
            }
            quitAudio();
            //关闭播放图片渲染和定时器
            boolFlag=false;
            if(qtimer->isActive()){
                qtimer->stop();
            }
        }
        if(playingType=="video"||playingType=="yuv"){
            //打开qt渲染
            if(audioStatus&&sdlVideoInfo->status){
                //正在暂停，退出暂停
                audioStatus=false;
                sdlVideoInfo->status=false;
            }
            quitVideo();
            //取消焦点
            ui->listWidget->setCurrentItem(NULL);
        }
        quitFlag=true;
        //修改样式
        ui->widget_2->setStyleSheet(QString("#widget_2{border-image: url(:/pic/picture/bg.jpg)}"));
        ui->toolButton_10->setHidden(false);
        ui->label->setHidden(true);
        playingType="null";
        //修改图标
        ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media-pause.png"));
        ui->toolButton_7->setToolTip(QString::fromLocal8Bit("播放"));
        ui->label_2->setText("");
    }else{
        //提示信息
        messageFlag=true;
        timer->start(1000);
    }
}
//暂停 播放
void MainWindow::on_toolButton_7_clicked()
{
    if(playingType!="null"){
        if(playingType=="audio"){
            //音频播放暂停
            audioStatus=!audioStatus;
            //关闭渲染
            if(qtimer->isActive()){
                boolFlag=false;
                qtimer->stop();
            }else{
                boolFlag=true;
                qtimer->start(30);
            }
        }
        if(playingType=="video"||playingType=="yuv"){
            //视频播放暂停
            audioStatus=!audioStatus;
            sdlVideoInfo->status=!sdlVideoInfo->status;
        }
        //更换图标
        if(audioStatus){
            //暂停了更换图标
            ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media-pause.png"));
            ui->toolButton_7->setToolTip(QString::fromLocal8Bit("播放"));
        }else{
            //播放了 更换图标
            ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media play .png"));
            ui->toolButton_7->setToolTip(QString::fromLocal8Bit("暂停"));
        }

    }
    else{
        //没有播放，从容器列表中选择一个直接播放
        if(!videoList.empty()){
            //获取列表的开头
            QString filePath;
            //获取文件的类型
            if(playingPath!="null"){
                filePath=playingPath;
            }else{
                filePath=*videoList.begin();
            }
            //更换播放ico
            ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media play .png"));
            ui->toolButton_7->setToolTip(QString::fromLocal8Bit("暂停"));
            ui->toolButton_10->setHidden(true);
            //获得播放列表焦点
            for (int j = 0; j < ui->listWidget->count(); j++)
            {
                QListWidgetItem *item = ui->listWidget->item(j);
                MyListWidget *widget =( MyListWidget *) ui->listWidget->itemWidget(item);
                if(widget->filePath==filePath){
                    //设置为选中状态
                    ui->listWidget->setCurrentItem(item);
                }
            }
            playVideoByType(filePath);
            ui->label->setHidden(false);
        }else{
            //打开文件选择
            openFile();
            //播放文件，避免没有选择文件
            if(!videoList.empty()){
                QString filePath=*videoList.begin();
                ui->toolButton_10->setHidden(true);
                //更换播放icon
                ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media play .png"));
                ui->toolButton_7->setToolTip(QString::fromLocal8Bit("暂停"));
                playVideoByType(filePath);
                //设置焦点
                QListWidgetItem *item = ui->listWidget->item(0);
                ui->listWidget->setCurrentItem(item);
                ui->label->setHidden(false);
            }

        }
    }



}
//前一首播放
void MainWindow::on_toolButton_9_clicked()
{
    if(playingType!="null"){
        if(playingType=="audio"){
            if(audioStatus){
                //正在暂停，退出暂停
                audioStatus=false;
            }
            quitAudio();
            //关闭播放图片渲染和定时器
            boolFlag=false;
            if(qtimer->isActive()){
                qtimer->stop();
            }
        }
        if(playingType=="video"||playingType=="yuv"){
            //打开qt渲染
            if(audioStatus&&sdlVideoInfo->status){
                //正在暂停，退出暂停
                audioStatus=false;
                sdlVideoInfo->status=false;
            }
            quitVideo();
        }
        quitFlag=true;
    }
    QString filePath;
    bool flag=false;
    //播放前一个
    //查找前一个
    if(!videoList.empty()){
        for(list<QString>::const_iterator it=videoList.begin();it!=videoList.end();it++){
            if(*it==playingPath){
                flag=true;
                if(it==videoList.begin()){
                    filePath=*(--videoList.end());
                }else{
                    filePath=*--it;
                }
                break;
            }
        }
        if(!flag){
            //没找到，从列表第一个播放
            list<QString>::const_iterator it=videoList.begin();
            filePath=*it;
        }
        ui->label->setHidden(false);
    }else{
        //提示没有播放文件
        //提示信息
        messageFlag=true;
        timer->start(1000);
        return;
    }
    //记录当前播放的类型
    string fileType=getFileType(filePath.toStdString());
    //修改icon标记
    ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media play .png"));
    ui->toolButton_7->setToolTip(QString::fromLocal8Bit("暂停"));
    if(fileType=="audio"){
        //渲染播放图片
        ui->widget_2->setAttribute(Qt::WA_PaintOnScreen,false);
        boolFlag=true;
        translatePic();
    }
    if(fileType=="video"){
        //关闭qt渲染
    }
    //从widget中查找该filePath，获得焦点
    for (int j = 0; j < ui->listWidget->count(); j++)
    {
        QListWidgetItem *item = ui->listWidget->item(j);
        MyListWidget *widget =( MyListWidget *) ui->listWidget->itemWidget(item);
        if(widget->filePath==filePath){
            //设置为选中状态
            ui->listWidget->setCurrentItem(item);
        }
    }
    playingType=fileType;
    playingPath=filePath;
    ui->toolButton_10->setHidden(true);
    ui->widget_2->setStyleSheet(QString("background-color: rgb(10, 10, 10)"));
    long long duration=getFileTime(filePath.toStdString());
    showPlayingTime(duration);
    QFileInfo fileInfo(filePath);
    ui->label_2->setText(fileInfo.fileName());
    mutexVideo(filePath.toStdString().c_str(),ui->widget_2);
}
//开启定时器旋转图片
void MainWindow::translatePic(){
    //创建定时器
    if(!qtimer->isActive()){
        qtimer->start(30);
    }
}
//静音控制
void MainWindow::on_toolButton_5_clicked()
{
    if(volume){
        //保存上次的音量值
        lastVolume =ui->horizontalSlider_2->value();
        //静音
        ui->horizontalSlider_2->setValue(0);
        //修改成静音
        ui->toolButton_5->setIcon(QIcon(":/player/picture/player/jingying.png"));
        ui->toolButton_5->setToolTip(QString::fromLocal8Bit("声音"));
    }else{
        //修改成声音
        ui->toolButton_5->setIcon(QIcon(":/player/picture/player/sound.png"));
        ui->horizontalSlider_2->setValue(lastVolume);
        //ui->toolButton_5->setToolTip(QString::fromLocal8Bit("静音"));
    }
}
//根据类型播放视频
void MainWindow:: playVideoByType(QString filePath){
    QFileInfo fileInfo(filePath);
    ui->label_2->setText(fileInfo.fileName());
    string fileType=getFileType(filePath.toStdString());
    //进行播放
    if(fileType=="audio"){
        //开启画面渲染
        boolFlag=true;
        translatePic();
    }
    ui->widget_2->setStyleSheet(QString("background-color: rgb(10, 10, 10)"));
    ui->toolButton_10->setHidden(true);
    playingPath=filePath;
    playingType=fileType;
    //展示时间
    long long duration=getFileTime(filePath.toStdString());
    showPlayingTime(duration);
    mutexVideo(filePath.toStdString().c_str(),ui->widget_2);
}
//下一首
void MainWindow::on_toolButton_8_clicked()
{
    if(playingType!="null"){
        if(playingType=="audio"){
            if(audioStatus){
                //正在暂停，退出暂停
                audioStatus=false;
            }
            quitAudio();
            //关闭播放图片渲染和定时器
            boolFlag=false;
            if(qtimer->isActive()){
                qtimer->stop();
            }
        }
        if(playingType=="video"||playingType=="yuv"){
            //打开qt渲染
            if(audioStatus&&sdlVideoInfo->status){
                //正在暂停，退出暂停
                audioStatus=false;
                sdlVideoInfo->status=false;
            }
            quitVideo();
        }
        quitFlag=true;
    }
    QString filePath;
    bool flag=false;
    //播放前一个
    //查找前一个
    if(!videoList.empty()){
        for(list<QString>::const_iterator it=videoList.begin();it!=videoList.end();it++){
            if(*it==playingPath){
                flag=true;
                if(++it!=videoList.end()){
                    //不是最后一个
                    filePath=*it;
                }else{
                    //是最后一个
                    filePath=*videoList.begin();
                }
                break;
            }
        }
        if(!flag){
            //没找到，从列表第一个播放
            list<QString>::const_iterator it=videoList.begin();
            filePath=*it;
        }
        ui->label->setHidden(false);
    }else{
        //提示没有播放文件
        //提示信息
        messageFlag=true;
        timer->start(1000);
        return;
    }
    //记录当前播放的类型
    string fileType=getFileType(filePath.toStdString());
    if(fileType=="audio"){
        //渲染播放图片
        //开启qt渲染
        ui->widget_2->setAttribute(Qt::WA_PaintOnScreen,false);
        boolFlag=true;
        translatePic();
    }
    if(fileType=="video"){
        //关闭qt渲染
        // ui->widget_2->setAttribute(Qt::WA_PaintOnScreen,true);

    }
    //获取选中焦点
    for (int j = 0; j < ui->listWidget->count(); j++)
    {
        QListWidgetItem *item = ui->listWidget->item(j);
        MyListWidget *widget =( MyListWidget *) ui->listWidget->itemWidget(item);
        if(widget->filePath==filePath){
            //设置为选中状态
            ui->listWidget->setCurrentItem(item);
        }
    }
    ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media play .png"));
    ui->toolButton_7->setToolTip(QString::fromLocal8Bit("暂停"));
    playingType=fileType;
    playingPath=filePath;
    QFileInfo fileInfo(filePath);
    ui->label_2->setText(fileInfo.fileName());
    ui->toolButton_10->setHidden(true);
    ui->widget_2->setStyleSheet(QString("background-color: rgb(10, 10, 10)"));
    long long duration=getFileTime(filePath.toStdString());
    showPlayingTime(duration);
    mutexVideo(filePath.toStdString().c_str(),ui->widget_2);
}
//打开文件
void MainWindow::on_toolButton_10_clicked()
{
    openFile();
}
void MainWindow::pauseOrPlayVideo(){
    if(playingType!="null"){
        if(playingType=="audio"){
            //音频播放暂停
            audioStatus=!audioStatus;
            //关闭渲染
            if(qtimer->isActive()){
                boolFlag=false;
                qtimer->stop();
            }else{
                boolFlag=true;
                qtimer->start(30);
            }
        }
        if(playingType=="video"||playingType=="yuv"){
            //视频播放暂停
            audioStatus=!audioStatus;
            sdlVideoInfo->status=!sdlVideoInfo->status;
        }
        if(audioStatus){
            //暂停 修改标记
            ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media-pause.png"));
            ui->toolButton_7->setToolTip(QString::fromLocal8Bit("播放"));
        }else{
            //播放 修改标记
            ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media play .png"));
            ui->toolButton_7->setToolTip(QString::fromLocal8Bit("暂停"));
        }
    }
};
//删除单个item
void MainWindow:: deleteSingleItem(QListWidgetItem* item,QString filePath){
    //判断是否正在播放
    if(playingType!="null"){
        if(playingPath==filePath){
            ui->toolButton_7->setIcon(QIcon(":/player/picture/player/media-pause.png"));
            ui->toolButton_7->setToolTip(QString::fromLocal8Bit("播放"));
            closeShowPlayingTime();
            if(playingType=="audio"){
                if(audioStatus){
                    //正在暂停，退出暂停
                    audioStatus=false;
                }
                quitAudio();
                //关闭播放图片渲染和定时器
                boolFlag=false;
                if(qtimer->isActive()){
                    qtimer->stop();
                }
            }
            if(playingType=="video"||playingType=="yuv"){
                //打开qt渲染
                if(audioStatus&&sdlVideoInfo->status){
                    //正在暂停，退出暂停
                    audioStatus=false;
                    sdlVideoInfo->status=false;
                }
                quitVideo();
                //开启qt渲染
                ui->widget_2->setAttribute(Qt::WA_PaintOnScreen,false);
            }
            quitFlag=true;
            //修改样式
            ui->widget_2->setStyleSheet(QString("#widget_2{border-image: url(:/pic/picture/bg.jpg)}"));
            ui->toolButton_10->setHidden(false);
            playingType="null";
            //取消焦点
            ui->listWidget->setCurrentItem(NULL);
            ui->label->setHidden(true);
            ui->label_2->setText("");
        }
    }
    //删除item
    ui->listWidget->removeItemWidget(item);
    delete(item);
    //删除list中的数据
    for(list<QString>::const_iterator it=videoList.begin();it!=videoList.end();it++){
        if(*it==filePath){
            //找到当前项，删除
            videoList.erase(it);
            break;
        }
    }
}
//查找list是否已经存在该video
bool MainWindow::findVideoList(QString filePath){
    for(list<QString>::const_iterator it=videoList.begin();it!=videoList.end();it++){
        if(*it==filePath){
            return true;
        }
    }
    return false;
}
//应用关闭，保存文件列表
void MainWindow::closeEvent(QCloseEvent *event){
    //将videolist直接序列化到文件，实现文件列表的保存
    if(!videoList.empty()){
        //将列表数据写入到文件
        QFile file;
        file.setFileName(storeFilePath);
        //以截断和追加方式
        if(file.open(QIODevice::Append|QIODevice::Truncate)) {
            for(list<QString>::const_iterator it=videoList.begin();it!=videoList.end();it++){
                QString filePath=*it+";";
                file.write(filePath.toStdString().data());
            }
        };
    }
    else{
        //直接删除文件
        QFile file;
        file.setFileName(storeFilePath);
        if(file.exists()){
            file.remove();
        }
    }

};
void MainWindow::addFile(QString filePath){
    //判断打开文件的类型
    string fileType=getFileType(filePath.toStdString());
    QPixmap pixmap;
    if(fileType=="unknow"){
        //弹出不支持格式的提示窗口
        return;
    }else{
        if(fileType=="audio"){
            pixmap= QPixmap(":/player/picture/player/music.png");
        }else if(fileType=="yuv"||fileType=="video"){
            //截取一帧图片和时间
            getVideoImage(filePath.toStdString().c_str());
            QImage qimage(rgb->data[0],pictureWidth,pictureHeight,QImage::Format_BGR888);
            pixmap=QPixmap::fromImage(qimage);
            // 释放内存
            av_frame_free(&rgb);
            rgb=NULL;
        }
    }
    //格式化时间
    long long duration=getFileTime(filePath.toStdString());
    QString time=formartTime(duration);
    QFileInfo* fileInfo=new QFileInfo(filePath);
    //获得文件名
    QString fileName=fileInfo->fileName();
    //获取文件时长和第一帧图片
    //创建 QListWidgetItem（缩虐图列表）
    QListWidgetItem *imageItem = new QListWidgetItem();
    //设置文件名
    //获取视频缩略图和视频时长
    QSize qSize(200,70);
    MyListWidget * myListWidget=new MyListWidget(fileName,time,&pixmap,this,imageItem);
    //保存filepath
    myListWidget->setMouseTracking(true);
    myListWidget->filePath=filePath;
    //保存filetype
    myListWidget->fileType=QString::fromStdString(fileType);
    //保存时长
    myListWidget->duration=duration;
    imageItem->setSizeHint(qSize);
    ui->listWidget->addItem(imageItem);
    ui->listWidget->setItemWidget(imageItem,myListWidget);
    ui->listWidget->show();
}
//最大化和最小化处理
void MainWindow:: changeEvent(QEvent *event){

    if(this->windowState()==Qt::WindowMaximized)

    {
        //        cout<<11<<endl;

    }

    if(this->windowState()==Qt::WindowMinimized)

    {
        //        cout<<22<<endl;

    }

    if(this->windowState()==Qt::WindowFullScreen)

    {
        //        cout<<33<<endl;

    }

    if(this->windowState()==Qt:: WindowActive)

    {
        //        cout<<44<<endl;

    }

    if(this->windowState()==Qt:: WindowNoState)

    {
        //        cout<<55<<endl;

    }
};
void MainWindow:: resizeEvent(QResizeEvent *event){

};
//格式化时间
QString MainWindow:: formartPlayingTime(long long duration,long long playingTime){
    QString durationTime=formartTime(duration);
    QString formatPlayingTime=formartTime(playingTime);
    return formatPlayingTime+"/"+durationTime;
}
//添加历史文件记录
void MainWindow::addHistoryVideoList(){
    QFile file;
    file.setFileName(storeFilePath);
    //读取文件中的历史文件列表
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray byteArray=file.readAll();
        string fileContent=byteArray.toStdString();
        if(fileContent!=""){
            size_t pos = fileContent.find(";");
            while(pos != fileContent.npos)
            {
                string temp = fileContent.substr(0, pos);
                QString filePath= QString::fromStdString(temp);
                videoList.push_back( filePath);
                addFile(filePath);
                //去掉已分割的字符串,在剩下的字符串中进行分割
                fileContent = fileContent.substr(pos+1, fileContent.size());
                pos = fileContent.find(";");

            }
        }
    }

}
//缩略图和列表切换
void MainWindow::on_toolButton_3_clicked()
{

    if(imageList){
        ui->toolButton_3->setIcon(QIcon(":/player/picture/player/playinglist.png"));
        ui->toolButton_3->setToolTip(QString::fromLocal8Bit("切换到缩略图"));
    }
    else{
        ui->toolButton_3->setIcon(QIcon(":/player/picture/player/suonuetu.png"));
        ui->toolButton_3->setToolTip(QString::fromLocal8Bit("切换到列表"));
    };
    //遍历list列表
    for (int j = 0; j < ui->listWidget->count(); j++)
    {
        QListWidgetItem *item = ui->listWidget->item(j);
        MyListWidget *widget =( MyListWidget *) ui->listWidget->itemWidget(item);
        if(imageList){
            widget->changToList();
        }else{
            widget->toImage();
        }
    }
    imageList=!imageList;

}
//声音调节
void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    volume=value;

}
//显示播放时间
void MainWindow::showPlayingTime(long long duration){
    //线程存在
    if( updateTimeThread!=NULL){
        updateTimeThread->quitFlag=false;
        //退出线程
        updateTimeThread->quit();
        updateTimeThread->wait();
        delete updateTimeThread;
        updateTimeThread=NULL;
    }
    if(ui->label->isHidden()){
        ui->label->setHidden(false);
    }
    if(ui->horizontalSlider->isHidden()){
        ui->horizontalSlider->setHidden(false);
    }
    ui->horizontalSlider->setMaximum(duration);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setSingleStep(3);
    //开启线程更新时间
    updateTimeThread=new UpdateTimeThread(ui->horizontalSlider,ui->label,duration,&playingTime);
    //开启线程
    updateTimeThread->start();


}
void MainWindow::initPlayer(){
    //创建播放模式菜单
    playModelMenu=new QMenu(ui->toolButton_4);
    QAction * actionRandomPlay= new QAction(playModelMenu);
    actionRandomPlay->setIcon(QIcon(":/player/picture/player/randomplay.png"));
    actionRandomPlay->setText(QString::fromLocal8Bit("随机播放"));
    QAction * actionSortPlay= new QAction(playModelMenu);
    actionSortPlay->setIcon(QIcon(":/player/picture/player/listxunhuan.png"));
    actionSortPlay->setText(QString::fromLocal8Bit("顺序播放"));
    QAction * actionSinglePlay= new QAction(playModelMenu);
    actionSinglePlay->setIcon(QIcon(":/player/picture/player/singleplay.png"));
    actionSinglePlay->setText(QString::fromLocal8Bit("单个播放"));
    QAction * actionSingleCycle= new QAction(playModelMenu);
    actionSingleCycle->setIcon(QIcon(":/player/picture/player/singlecycle.png"));
    actionSingleCycle->setText(QString::fromLocal8Bit("单个循环"));
    QAction * actionListCycle= new QAction(playModelMenu);
    actionListCycle->setIcon(QIcon(":/player/picture/player/listcycle.png"));
    actionListCycle->setText(QString::fromLocal8Bit("列表循环"));
    playModelMenu->addAction(actionRandomPlay);
    playModelMenu->addAction(actionSortPlay);
    playModelMenu->addAction(actionSinglePlay);
    playModelMenu->addAction(actionSingleCycle);
    playModelMenu->addAction(actionListCycle);
    playModelMenu->setWindowFlags(playModelMenu->windowFlags() | Qt::FramelessWindowHint);
    //playModelMenu->setAttribute(Qt::WA_TranslucentBackground);
    playModelMenu->setStyleSheet("QMenu {border-radius:5px;"
                                 "font-family:'Arial';font-size:12px;color:rgb(255,255,255);width:90px;}"
                                 "QMenu::item {height:30px; width:90px;padding-left:10px;border: 1px solid none;}"
                                 "QMenu::item:selected {background-color:rgb(70,70,70);\
                                 padding-left:10px; border: 1px solid rgb(65,173,255);}");
connect(playModelMenu,SIGNAL(triggered(QAction *)), this, SLOT(selectPlayMode(QAction * )));
ui->toolButton_4->setMenu(playModelMenu);
createToolMenu();
//隐藏时间qlabel
//ui->label->setHidden(true);
//隐藏播放进度滑块
ui->horizontalSlider->setHidden(true);
_previewInitPoit = ui->widget_2->pos();
_previewInitSize = ui->widget_2->size();
ui->widget_2->installEventFilter(this);
this->installEventFilter(this);
ui->label_2->installEventFilter(this);
transWidget=new TranslucentWidget();
transWidget->button->installEventFilter(this);
transWidget->installEventFilter(this);
ui->widget_2->setMouseTracking(true);
//处理单击双击冲突
connect(clickedTimer,&QTimer::timeout,[=]{
    //延时调用
    if(!doubleClicked){
        //没有双击则触发
        pauseOrPlayVideo();
    }else{
        //双击了则改变标记
        doubleClicked=false;
    }
    //关闭定时器
    if(clickedTimer->isActive()){
        clickedTimer->stop();
    }

});
//隐藏透明按钮
connect(hiddenVideoListTimer,&QTimer::timeout,[=]{
    transWidget->hide();
    hiddenVideoListTimer->stop();
});
//停止播放停止消息
connect(timer,&QTimer::timeout,[=](){
    //渲染播放图标
    update();
    if(!messageFlag){
        if(timer->isActive()){
            //关闭渲染
            timer->stop();
        }
    }

});
//音乐播放渲染
connect(qtimer,&QTimer::timeout,[=](){
    //渲染播放图标
    update();
});
//读取历史文件列表
addHistoryVideoList();
ui->widget_12->initTitleBar(this);
ui->label_2->installEventFilter(this);
ui->label_2->show();
setStyleSheet(QString("QToolButton{border:none;}"));
createQslider();
messageWidget=new MesssageWidget;
}
//关闭显示播放时间
void MainWindow::closeShowPlayingTime(){
    if( updateTimeThread!=NULL){
        updateTimeThread->quitFlag=false;
        //退出线程
        updateTimeThread->quit();
        updateTimeThread->wait();
        delete updateTimeThread;
        updateTimeThread=NULL;
    }
    if(!ui->label->isHidden()){
        ui->label->setHidden(true);
    }
    if(!ui->horizontalSlider->isHidden()){
        ui->horizontalSlider->setHidden(true);
    }
}
//播放模式菜单
void MainWindow::on_toolButton_4_clicked()
{
    //修改按钮菜单的坐标
    QPoint p = ui->toolButton_4->mapToGlobal(QPoint(0, 0));//相对应屏幕左上角的坐标
    playModelMenu->move(QPoint(p.x()- (playModelMenu->size().width()-ui->toolButton_4->width())*0.5 , p.y()+ ui->toolButton_4->height() ));
    playModelMenu->show();
}
//重新设置选择模式
void MainWindow:: selectPlayMode(QAction * action){
    QString text=action->text();
    ui->toolButton_4->setToolTip(text);
    ui->toolButton_4->setIcon(action->icon());

    if(text==QString::fromLocal8Bit("顺序播放")){
        playingMode=0;
        return;
    }
    if(text==QString::fromLocal8Bit("随机播放")){
        playingMode=1;
        return;
    }
    if(text==QString::fromLocal8Bit("单个播放")){
        playingMode=2;
        return;
    }
    if(text==QString::fromLocal8Bit("单个循环")){
        playingMode=3;
        return;
    }
    if(text=="列表循环"){
        playingMode=4;
        return;
    }
};
//最小化
void MainWindow::on_toolButton_14_clicked()
{
    showMinimized();
}
//最大化
void MainWindow::on_toolButton_13_clicked()
{
    if(isMaximized()){
        ui->toolButton_16->setIcon(QIcon(":/player/picture/player/menumaxsize.png"));
        ui->toolButton_13->setIcon(QIcon(":/player/picture/player/maxsize.png"));
        showNormal();
    }else{
        ui->toolButton_16->setIcon(QIcon(":/player/picture/player/menuhuanyuan .png"));
        ui->toolButton_13->setIcon(QIcon(":/player/picture/player/huanyuan.png"));
        showMaximized();

    }
}
//关闭
void MainWindow::on_toolButton_12_clicked()
{

    close();
}
//菜单全屏
void MainWindow::on_toolButton_16_clicked()
{
    if(isMaximized()){
        ui->toolButton_13->setIcon(QIcon(":/player/picture/player/maxsize.png"));
        ui->toolButton_16->setIcon(QIcon(":/player/picture/player/menumaxsize.png"));
        showNormal();
    }else{
        ui->toolButton_13->setIcon(QIcon(":/player/picture/player/huanyuan.png"));
        ui->toolButton_16->setIcon(QIcon(":/player/picture/player/menuhuanyuan .png"));
        showMaximized();
    }
}
//工具箱显示
void MainWindow::on_toolButton_11_clicked()
{
    //修改按钮菜单的坐标
    QPoint p = ui->toolButton_11->mapToGlobal(QPoint(0, 0));//相对应屏幕左上角的坐标
    toolMenu->move(QPoint(p.x()- (toolMenu->size().width()-ui->toolButton_11->width())*0.5 , p.y()-110 ));
    toolMenu->show();
}
//创建工具菜单
void MainWindow::createToolMenu(){
    //创建工具菜单
    toolMenu=new QMenu(ui->toolButton_11);
    //截图
    QAction * grabPicture= new QAction( toolMenu);
    grabPicture->setIcon(QIcon(":/player/picture/player/cutPicture.png"));
    grabPicture->setText(QString::fromLocal8Bit("截图"));
    //生成gif
    QAction * createGIF= new QAction( toolMenu);
    createGIF->setIcon(QIcon(":/player/picture/player/createGif.png"));
    createGIF->setText(QString::fromLocal8Bit("生成gif"));
    //连拍
    QAction * photograph= new QAction( toolMenu);
    photograph->setIcon(QIcon(":/player/picture/player/phtograph.png"));
    photograph->setText(QString::fromLocal8Bit("连拍"));
    toolMenu->addAction(grabPicture);
    toolMenu->addAction(createGIF);
    toolMenu->addAction(photograph);
    toolMenu->setWindowFlags( toolMenu->windowFlags() | Qt::FramelessWindowHint);
    toolMenu->setStyleSheet("QMenu {border-radius:5px;"
                            "font-family:'Arial';font-size:12px;color:rgb(255,255,255);width:90px;}"
                            "QMenu::item {height:30px; width:90px;padding-left:10px;border: 1px solid none;}"
                            "QMenu::item:selected {background-color:rgb(70,70,70);\
                            padding-left:10px; border: 1px solid rgb(65,173,255);}");
ui->toolButton_11->setMenu(toolMenu);

}
//倍速调节
void MainWindow::on_toolButton_17_clicked()
{

        QPoint p = ui->toolButton_17->mapToGlobal(QPoint(0, 0));//相对应屏幕左上角的坐标
        slider->move(QPoint(p.x()+( ui->toolButton_17->width()-slider->width())*0.5 , p.y()-slider->height()-10));
        if(slider->isHidden()){
             slider->show();
        }else{
             slider->hide();
        }
}
//倍速播放控制滑块
void MainWindow::createQslider(){
    slider=new SpeedControlSlider;
    //显示消息
    slider->connect(slider,&SpeedControlSlider::sliderMoved,[=](int value){
        double percentage=(double)value/100;
        speed= floor( percentage * 10.000f + 0.5) / 10.000f;
        QString message=QString::fromLocal8Bit("倍速:")+QString::number(speed);
        messageWidget->changMessage(message);
        QPoint p = ui->widget_2->mapToGlobal(QPoint(0, 0));//相对应屏幕左上角的坐标
        messageWidget->move(QPoint(p.x()+20, p.y()+ui->widget_2->height()-messageWidget->height()-20));
        if(messageWidget->isHidden()){
            messageWidget->show();
        }

    });
    //隐藏提示框
    slider->connect(slider,&SpeedControlSlider::sliderReleased,[=](){
        if(messageWidget->isVisible()){
            messageWidget->hide();
        }
        slider->hide();
    });
}
//隐藏音量框
void MainWindow::on_horizontalSlider_2_sliderReleased()
{
    if(messageWidget->isVisible()){
        messageWidget->hide();
    }
}
//显示音量框
void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    int maxNum=ui->horizontalSlider_2->maximum();
    double percentage=(double)position/(double)maxNum;
    int percent=(int) (percentage*100);
    QString message=QString::fromLocal8Bit("音量:")+QString::number(percent)+QString("%");
    messageWidget->changMessage(message);
    QPoint p = ui->widget_2->mapToGlobal(QPoint(0, 0));//相对应屏幕左上角的坐标
    messageWidget->move(QPoint(p.x()+20, p.y()+ui->widget_2->height()-messageWidget->height()-20));
    if(messageWidget->isHidden()){
        messageWidget->show();
    }
}
//窗口拉伸计算区域
void MainWindow::calculateStrenchRect(){
    // 四个角Rect;
    m_leftTopRect = QRect(0, 0, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_leftBottomRect = QRect(0, this->height() - STRETCH_RECT_HEIGHT, STRETCH_RECT_WIDTH, STRETCH_RECT_WIDTH);
    m_rightTopRect = QRect(this->width() - STRETCH_RECT_WIDTH, 0, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_rightBottomRect = QRect(this->width() - STRETCH_RECT_WIDTH, this->height() - STRETCH_RECT_HEIGHT, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    // 四条边Rect;
    // 四条边Rect;
    m_topBorderRect = QRect(STRETCH_RECT_WIDTH, 0, this->width() - STRETCH_RECT_WIDTH * 2, STRETCH_RECT_HEIGHT);
    m_rightBorderRect = QRect(this->width() - STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT, STRETCH_RECT_WIDTH, this->height() - STRETCH_RECT_HEIGHT * 2);
    m_bottomBorderRect = QRect(STRETCH_RECT_WIDTH, this->height() - STRETCH_RECT_HEIGHT, this->width() - STRETCH_RECT_WIDTH * 2, STRETCH_RECT_HEIGHT);
    m_leftBorderRect = QRect(0, STRETCH_RECT_HEIGHT, STRETCH_RECT_WIDTH, this->height() - STRETCH_RECT_HEIGHT * 2);
}
void MainWindow::showEvent(QShowEvent *event){
   //计算窗口拉伸 区域
    calculateStrenchRect();
}
//根据鼠标位置，确定鼠标所在区域
WindowStretchRectState MainWindow::getCurrentStretchState(QPoint cursorPos)
{
    WindowStretchRectState stretchState;
    if (m_leftTopRect.contains(cursorPos))
    {
        stretchState = LEFT_TOP_RECT;
    }
    else if (m_rightTopRect.contains(cursorPos))
    {
        stretchState = RIGHT_TOP_RECT;
    }
    else if (m_rightBottomRect.contains(cursorPos))
    {
        stretchState = RIGHT_BOTTOM_RECT;
    }
    else if (m_leftBottomRect.contains(cursorPos))
    {
        stretchState = LEFT_BOTTOM_RECT;
    }
    else if (m_topBorderRect.contains(cursorPos))
    {
        stretchState = TOP_BORDER;
    }
    else if (m_rightBorderRect.contains(cursorPos))
    {
        stretchState = RIGHT_BORDER;
    }
    else if (m_bottomBorderRect.contains(cursorPos))
    {
        stretchState = BOTTOM_BORDER;
    }
    else if (m_leftBorderRect.contains(cursorPos))
    {
        stretchState = LEFT_BORDER;
    }
    else
    {
        stretchState = NO_SELECT;
    }
    return stretchState;
}
//根据鼠标所在区域更新鼠标样式
void MainWindow::updateMouseStyle(WindowStretchRectState stretchState)
{
    switch (stretchState)
    {
    case NO_SELECT:
        setCursor(Qt::ArrowCursor);
        break;
    case LEFT_TOP_RECT:
    case RIGHT_BOTTOM_RECT:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TOP_BORDER:
    case BOTTOM_BORDER:
        setCursor(Qt::SizeVerCursor);
        break;
    case RIGHT_TOP_RECT:
    case LEFT_BOTTOM_RECT:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case LEFT_BORDER:
    case RIGHT_BORDER:
        setCursor(Qt::SizeHorCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }

}
//鼠标移动
void MainWindow::mouseMoveEvent(QMouseEvent *event){


};
//鼠标按下
void MainWindow::mousePressEvent(QMouseEvent *event){
       // 当前鼠标进入了以上指定的8个区域，并且是左键按下时才开始进行窗口拉伸;
        if (m_stretchRectState != NO_SELECT && event->button() == Qt::LeftButton)
        {
            m_isMousePressed = true;
            // 记录下当前鼠标位置，为后面计算拉伸位置;
            m_startPoint = this->mapToGlobal(event->pos());
            // 保存下拉伸前的窗口位置及大小;
            m_windowRectBeforeStretch = this->geometry();
        }
}
//鼠标释放
void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    // 鼠标松开后意味之窗口拉伸结束，置标志位，并且重新计算用于拉伸的8个区域Rect;
        //ui->widget_2->setUpdatesEnabled(false);
        m_isMousePressed = false;
        //重新计算区域
        calculateStrenchRect();
};
//窗口拉伸
void MainWindow::updateWindowSize(){
        // 拉伸时要注意设置窗口最小值;
        QRect windowRect = m_windowRectBeforeStretch;
        int delValue_X = m_startPoint.x() - m_endPoint.x();
        int delValue_Y = m_startPoint.y() - m_endPoint.y();
        if (m_stretchRectState == LEFT_BORDER)
        {
            QPoint topLeftPoint = windowRect.topLeft();
            topLeftPoint.setX(topLeftPoint.x() - delValue_X);
            windowRect.setTopLeft(topLeftPoint);
        }
        else if (m_stretchRectState == RIGHT_BORDER)
        {
            QPoint bottomRightPoint = windowRect.bottomRight();
            bottomRightPoint.setX(bottomRightPoint.x() - delValue_X);
            windowRect.setBottomRight(bottomRightPoint);
        }
        else if (m_stretchRectState == TOP_BORDER)
        {
            QPoint topLeftPoint = windowRect.topLeft();
            topLeftPoint.setY(topLeftPoint.y() - delValue_Y);
            windowRect.setTopLeft(topLeftPoint);
        }
        else if (m_stretchRectState == BOTTOM_BORDER)
        {
            QPoint bottomRightPoint = windowRect.bottomRight();
            bottomRightPoint.setY(bottomRightPoint.y() - delValue_Y);
            windowRect.setBottomRight(bottomRightPoint);
        }
        else if (m_stretchRectState == LEFT_TOP_RECT)
        {
            QPoint topLeftPoint = windowRect.topLeft();
            topLeftPoint.setX(topLeftPoint.x() - delValue_X);
            topLeftPoint.setY(topLeftPoint.y() - delValue_Y);
            windowRect.setTopLeft(topLeftPoint);
        }
        else if (m_stretchRectState == RIGHT_TOP_RECT)
        {
            QPoint topRightPoint = windowRect.topRight();
            topRightPoint.setX(topRightPoint.x() - delValue_X);
            topRightPoint.setY(topRightPoint.y() - delValue_Y);
            windowRect.setTopRight(topRightPoint);
        }
        else if (m_stretchRectState == RIGHT_BOTTOM_RECT)
        {
            QPoint bottomRightPoint = windowRect.bottomRight();
            bottomRightPoint.setX(bottomRightPoint.x() - delValue_X);
            bottomRightPoint.setY(bottomRightPoint.y() - delValue_Y);
            windowRect.setBottomRight(bottomRightPoint);
        }
        else if (m_stretchRectState == LEFT_BOTTOM_RECT)
        {
            QPoint bottomLeftPoint = windowRect.bottomLeft();
            bottomLeftPoint.setX(bottomLeftPoint.x() - delValue_X);
            bottomLeftPoint.setY(bottomLeftPoint.y() - delValue_Y);
            windowRect.setBottomLeft(bottomLeftPoint);
        }

        // 避免宽或高为零窗口显示有误，这里给窗口设置最小拉伸高度、宽度;
        if (windowRect.width() < minimumWidth())
        {
            windowRect.setLeft(this->geometry().left());
            windowRect.setWidth(minimumWidth());
        }
        if (windowRect.height() < minimumHeight())
        {
            windowRect.setTop(this->geometry().top());
            windowRect.setHeight(minimumHeight());
        }
        this->setGeometry(windowRect);


}
