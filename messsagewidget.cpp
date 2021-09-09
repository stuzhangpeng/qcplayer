#include "messsagewidget.h"
#include<QDebug>

//MesssageWidget::MesssageWidget(QWidget *parent) : QWidget(parent)
//{
   
//}
MesssageWidget::MesssageWidget(){
    //设置子窗口无标题在最顶端
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint);
    setFixedSize(120,40);
    layOut= new QHBoxLayout(this);
    messageLable=new QLabel;
    QFont font;
    font.setPointSize(14);
    messageLable->setStyleSheet("color:rgb(255,255,255);");
    messageLable->setFont(font);
    messageLable->setAlignment(Qt::AlignCenter);
    layOut->addWidget(messageLable);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(200,200,200,0));
    setPalette(pal);

};
MesssageWidget::~MesssageWidget(){
    delete  layOut;
    delete  messageLable;
}
void MesssageWidget::changMessage(QString text){
    messageLable->setText(text);
}
