#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H
#include <QWidget>
#include<QToolButton>
#include<QLabel>
#include<QPixmap>
#include<QListWidget>
#include<QHBoxLayout>
#include "mainwindow.h"
#include<QEvent>
#include<QDebug>
#include"picturelable.h"
class MyListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QWidget *parent = nullptr);
    explicit MyListWidget(QString fileName=nullptr,QString deleteIcon=nullptr,QPixmap* pixmap=NULL,MainWindow * mainwindow=NULL,
                          QListWidgetItem * item=NULL);
    void toImage();
    void changToList();
    void changToImage();
    QString filePath;
    QString fileType;
    QLabel * deleLable;
    MainWindow * mainwindow;
    QListWidgetItem * item;
    PictureLable * qlabel;
    QLabel * textLable;
    //文件姓名
    QString fileName;
    //格式化时间
    QString timeFormart;
    //缩略图
    QPixmap pic;
    //缩略图
    QPixmap pixmap;
    long long duration;
signals:
private:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MYLISTWIDGET_H
