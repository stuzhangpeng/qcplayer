#include "mainwindow.h"
#include <QApplication>
#include"player.h"
#include<QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTextCodec* codec = QTextCodec::codecForLocale();

    QTextCodec::setCodecForLocale(codec);

    w.show();
    return a.exec();
}
