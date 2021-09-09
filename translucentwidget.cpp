#include "translucentwidget.h"

//透明窗体
TranslucentWidget::TranslucentWidget(QWidget *parent) : QWidget(parent)
{
    //设置无边框，子窗体
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    //设置窗体透明
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_StyledBackground);
    QHBoxLayout *listVideoEdit= new QHBoxLayout(this);
    QToolButton * btn=new QToolButton;
    btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btn->setFixedSize(QSize(20,20));
    btn->setIcon(QIcon(":/player/picture/player/fanhui.png"));
    button=btn;
    btn->setAutoRaise(true);
    listVideoEdit->addWidget(btn);
    this->setFixedSize(30,30);
    //设置无边框
    setStyleSheet("border:none;");
}
//重写绘图事件
void TranslucentWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //透明颜色
    QColor clor=QColor(255,255,255,1);
    painter.fillRect(this->rect(),clor);
};
