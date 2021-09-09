#include "speedcontrolslider.h"

SpeedControlSlider::SpeedControlSlider(QSlider *parent) : QSlider(parent)
{
    setOrientation(Qt::Vertical);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint);
    setStyleSheet("  \
        QSlider\
        {\
            background-color: rgb(25, 38, 58);\
            min-width:5px;\
            max-width:5px;\
            border:15px solid rgb(25, 38, 58);\
        }\
         QSlider::add-page:vertical\
         {     \
            background-color: rgb(37, 168, 198);\
            width:4px;\
         }\
         QSlider::sub-page:vertical \
        {\
            background-color: rgb(87, 97, 106);\
            width:4px;\
         }\
        QSlider::groove:vertical \
        {\
            background:transparent;\
            width:6px;\
        }\
        QSlider::handle:vertical \
        {\
             height: 13px;\
            width:13px;\
            border-image: url(:/player/picture/player/circlevolume.png);\
            margin: -0 -4px; \
         }\
        ");
    setMinimum(50);
    setFixedHeight(100);
    setFixedWidth(20);
    setMaximum(200);
}

