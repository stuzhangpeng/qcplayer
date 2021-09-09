#ifndef SPEEDCONTROLSLIDER_H
#define SPEEDCONTROLSLIDER_H
#include<QSlider>
class SpeedControlSlider : public QSlider
{
    Q_OBJECT
public:
    explicit SpeedControlSlider(QSlider *parent = nullptr);
signals:

};

#endif // SPEEDCONTROLSLIDER_H
