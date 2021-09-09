#ifndef OPENFILEWIDGET_H
#define OPENFILEWIDGET_H
#include<QHBoxLayout>
#include <QWidget>

class OpenFileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpenFileWidget(QWidget *parent = nullptr);
    //void paintEvent(QPaintEvent* e);
signals:

};

#endif // OPENFILEWIDGET_H
