#ifndef UPDATETIMETHREAD_H
#define UPDATETIMETHREAD_H
#include <QThread>
#include<QLabel>
#include <QSlider>
class UpdateTimeThread : public QThread
{
    Q_OBJECT
public:
    explicit UpdateTimeThread(QThread *parent = nullptr);
    explicit UpdateTimeThread(QSlider * slider=NULL,QLabel * label=NULL,long long duration=0, long long *playingTime=NULL);
    QLabel * timeLabel;
    QSlider * slider;
    long long duration;
    long long *playingTime;
    QString formartPlayingTime(long long duration,long long playingTime);
    QString formartTime(long long time);
    volatile bool quitFlag=true;
    volatile bool finished=false;
signals:
protected: void run() override;
};

#endif // UPDATETIMETHREAD_H
