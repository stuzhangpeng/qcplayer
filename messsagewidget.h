#ifndef MESSSAGEWIDGET_H
#define MESSSAGEWIDGET_H
#include<QWidget>
#include<QLabel>
#include<QHBoxLayout>
class MesssageWidget : public QWidget
{
    Q_OBJECT
public:
    //explicit MesssageWidget(QWidget *parent = nullptr);
    explicit MesssageWidget();
    QHBoxLayout *layOut;
    QLabel * messageLable;
    void changMessage(QString text);
    ~MesssageWidget();
signals:

};

#endif // MESSSAGEWIDGET_H
