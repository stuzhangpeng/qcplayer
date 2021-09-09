#include "playingthread.h"
#include <string>
using namespace std;
PlayingThread::PlayingThread(QThread *parent) : QThread(parent)
{

}
PlayingThread::PlayingThread(QString filePath){
    this->filePath=filePath;
};
void PlayingThread:: run() {
  getFileTime(filePath.toStdString());
  mutexVideo(filePath.toStdString().c_str(),NULL);

};
