#include "mylistwidget.h"
#include "picturelable.h"
//自定义缩略图列表控件
MyListWidget::MyListWidget(QString fileName,QString time, QPixmap* pixmap,
                           MainWindow * mainwindow,QListWidgetItem * item)
{
    this->pixmap=*pixmap;
    this->setFixedSize(260,70);
    this->fileName=fileName;
    this->timeFormart=time;
    this->mainwindow=mainwindow;
    this->item=item;
    qlabel=new PictureLable();
    textLable=new QLabel(this);
    deleLable=new QLabel(this);
    deleLable->setText("x");
    deleLable->setStyleSheet("color:rgb(255,255,255);");
    deleLable->setVisible(false);
    QFont del;
    del.setPointSize(14);
    QSize deleteSize(10,50);
    deleLable->setFont(del);
    deleLable->setFixedSize(deleteSize);
    changToImage();
    QHBoxLayout *listVideoFile= new QHBoxLayout(this);
    listVideoFile->addWidget(qlabel);
    listVideoFile->addWidget( textLable);
    listVideoFile->addWidget(deleLable);
    this->installEventFilter(this);
    deleLable->installEventFilter(this);

}
MyListWidget::MyListWidget(QWidget *parent) :QWidget(parent)
{
}
bool MyListWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched ==this&&event->type()==QEvent::Enter)
    {
      deleLable->setVisible(true);
    }
    if(watched ==this&&event->type()==QEvent::Leave)
    {
      deleLable->setVisible(false);
    }
    if(watched ==deleLable&&event->type()==QEvent::MouseButtonPress)
    {
       this->mainwindow->deleteSingleItem(item,filePath);

    }
    return QWidget::eventFilter(watched,event);
}
void MyListWidget:: changToList(){
    this->qlabel->setStyleSheet("color:rgb(255,255,255);");
    this->qlabel->setText(timeFormart);
    this->textLable->setText(fileName);
};
void MyListWidget:: changToImage(){
    QFont ft;
    ft.setPointSize(10);
    QFont ft1;
    ft1.setPointSize(12);
    QSize qSize(70,52);
    textLable->setWordWrap(true);
    textLable->setFont(ft);
    textLable->setStyleSheet("color:rgb(255,255,255);");
    textLable->setText(fileName);
    qlabel->setFixedSize( qSize);
    //隐藏删除图标
    QPixmap pic=pixmap.scaled(qlabel->size());
    QPainter painter(&pic);
    painter.begin(&pic);
    painter.setPen(QColor(Qt::GlobalColor::white));
    //设置字体大小
    QFont font = painter.font();
    font.setPixelSize(12);//改变字体大小
    font.setFamily("Microsoft YaHei");
    painter.setFont(font);
    //将文字写在图片上
    painter.drawText(0,0,pic.width(),pic.height(), Qt::AlignBottom,timeFormart);
    painter.end();
    qlabel->setPixmap(pic);
    this->pic=pic;
}
void MyListWidget::toImage(){
    this->qlabel->setPixmap(pic);
    this->textLable->setText(fileName);
}
