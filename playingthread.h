#ifndef PLAYINGTHREAD_H
#define PLAYINGTHREAD_H

#include <QMainWindow>
#include<QThread>
#include"player.h"
class PlayingThread : public QThread
{
    Q_OBJECT
public:
    explicit PlayingThread(QThread *parent = nullptr);
    PlayingThread(QString filePath);
    void run() override;
    QString filePath;
signals:

};

#endif // PLAYINGTHREAD_H
