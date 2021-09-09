#ifndef TRANSLUCENTWIDGET_H
#define TRANSLUCENTWIDGET_H
#include<QToolButton>
#include<QHBoxLayout>
#include <QWidget>
#include <QPainter>
#include<QDebug>
class TranslucentWidget : public QWidget
{
    Q_OBJECT
public:
    QToolButton * button;
    explicit TranslucentWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
signals:

};
#endif // TRANSLUCENTWIDGET_H
