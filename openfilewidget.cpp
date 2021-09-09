#include "openfilewidget.h"
#include<QToolButton>
#include<QStyleOption>
#include<QPainter>
#include<QPaintEvent>
OpenFileWidget::OpenFileWidget(QWidget *parent) : QWidget(parent)
{
  QHBoxLayout * hBoxLayOut=new QHBoxLayout(this);
  QToolButton *fileToolButton= new QToolButton(this);
   QIcon icon(":/player/picture/player/文件夹.png");
  fileToolButton->setIcon(icon);
 //fileToolButton->setStyleSheet("background-image: url(:/player/picture/player/文件夹.png);");

  //fileToolButton->setAutoRaise(true);
  fileToolButton->setIconSize(QSize(100,100));
  fileToolButton->setText("打开文件");
  fileToolButton->setStyleSheet("background-color: rgb(255, 0, 0);");
  fileToolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
  hBoxLayOut->addWidget(fileToolButton);
  //setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
  //设置最小大小;
 // setMinimumSize(250,250);
  //setAttribute(Qt::WA_StyledBackground);

}
//void OpenFileWidget::paintEvent(QPaintEvent* event)
//{
//  //event->ignore();
////    QStyleOption option;
////    option.init(this);
////    QPainter p(this);
////    style()->drawPrimitive(QStyle::PE_Widget, &option, &p, this);

//}
