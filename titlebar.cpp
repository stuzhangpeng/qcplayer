#include "titlebar.h"
#include<QDebug>
TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
  setAttribute(Qt::WA_StyledBackground);
}
//左键双击标题栏最大化
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if(mainwindow->isMaximized()){
           mainwindow->showNormal();
        }else{
          mainwindow->showMaximized();
        }
    }

}
void TitleBar::initTitleBar( MainWindow * mainwindow){
   this->mainwindow=mainwindow;
}
void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 记录鼠标左键状态
        m_leftButtonPressed = true;
        //记录鼠标在屏幕中的位置
        m_start = event->globalPos();
    }

}
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    // 持续按住才做对应事件
    if(m_leftButtonPressed)
    {
        //将父窗体移动到父窗体原来的位置加上鼠标移动的位置：event->globalPos()-m_start
         mainwindow->move(mainwindow->geometry().topLeft() +
                             event->globalPos() - m_start);
        //将鼠标在屏幕中的位置替换为新的位置
        m_start = event->globalPos();
    }

}
void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    // 鼠标左键释放
    if (event->button() == Qt::LeftButton)
    {
        // 记录鼠标状态
        m_leftButtonPressed = false;
    }
}
