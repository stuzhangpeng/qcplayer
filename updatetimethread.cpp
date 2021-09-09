#include "updatetimethread.h"
#include<string>
using namespace std;
UpdateTimeThread::UpdateTimeThread(QThread *parent) : QThread(parent)
{

}
UpdateTimeThread::UpdateTimeThread(QSlider * slider,QLabel * label,long long duration, long long *playingTime){
    this->slider=slider;
    this->timeLabel=label;
    this->duration=duration;
    this->playingTime=playingTime;
};
void UpdateTimeThread::run(){
    //初始化播放时间
    *playingTime=0;
   //执行线程操作
    while(*playingTime<=duration&&quitFlag){
        QString time=formartPlayingTime(duration,*playingTime);
        //更新时间
        timeLabel->setText(time);
        //更新滑块值
        slider->setValue(*playingTime);
    }
    finished=true;
}
QString UpdateTimeThread:: formartPlayingTime(long long duration,long long playingTime){
  QString durationTime=formartTime(duration);
  QString formatPlayingTime=formartTime(playingTime);
  QString temp("/");
  return formatPlayingTime.append(temp).append( durationTime);
}
QString UpdateTimeThread::formartTime(long long time){
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
