#ifndef TITLEBAR_H
#define TITLEBAR_H
#include <QWidget>
#include "mainwindow.h"
//自定义标题栏
class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    //标题栏双击事件
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    //窗口移动实现
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    //主窗口
    MainWindow * mainwindow;
    void initTitleBar( MainWindow * mainwindow);
    bool m_leftButtonPressed;
    QPoint  m_start;
signals:

};

#endif // TITLEBAR_H
