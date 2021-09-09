/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <titlebar.h>
#include "videowidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    TitleBar *widget_12;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_8;
    QWidget *widget_14;
    QHBoxLayout *horizontalLayout_8;
    QToolButton *toolButton_15;
    QToolButton *toolButton_14;
    QToolButton *toolButton_13;
    QToolButton *toolButton_12;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_11;
    QVBoxLayout *verticalLayout_5;
    VideoWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QToolButton *toolButton_10;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSlider;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_6;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer_6;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *toolButton_6;
    QToolButton *toolButton_9;
    QToolButton *toolButton_7;
    QToolButton *toolButton_8;
    QToolButton *toolButton_5;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_5;
    QSlider *horizontalSlider_2;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *toolButton_17;
    QToolButton *toolButton_11;
    QToolButton *toolButton_16;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_3;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *toolButton_4;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_2;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer_3;
    QListWidget *listWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(920, 548);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/player/picture/player/\346\222\255\346\224\276\345\231\250.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMouseTracking(true);
        centralwidget->setStyleSheet(QString::fromUtf8("#centralwidget {\n"
"background-color: rgb(17, 17, 17);\n"
"\n"
"}"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        widget_12 = new TitleBar(centralwidget);
        widget_12->setObjectName(QString::fromUtf8("widget_12"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_12->sizePolicy().hasHeightForWidth());
        widget_12->setSizePolicy(sizePolicy1);
        widget_12->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 17, 17);"));
        horizontalLayout_9 = new QHBoxLayout(widget_12);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 2);
        label_3 = new QLabel(widget_12);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMaximumSize(QSize(30, 30));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/player/picture/player/player.png")));
        label_3->setScaledContents(true);
        label_3->setWordWrap(false);

        horizontalLayout_9->addWidget(label_3);

        label_4 = new QLabel(widget_12);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_9->addWidget(label_4);

        horizontalSpacer_7 = new QSpacerItem(156, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_7);

        label_2 = new QLabel(widget_12);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setMinimumSize(QSize(200, 0));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 12pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";"));
        label_2->setTextFormat(Qt::MarkdownText);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(label_2);

        horizontalSpacer_8 = new QSpacerItem(368, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);

        widget_14 = new QWidget(widget_12);
        widget_14->setObjectName(QString::fromUtf8("widget_14"));
        sizePolicy2.setHeightForWidth(widget_14->sizePolicy().hasHeightForWidth());
        widget_14->setSizePolicy(sizePolicy2);
        horizontalLayout_8 = new QHBoxLayout(widget_14);
        horizontalLayout_8->setSpacing(12);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        toolButton_15 = new QToolButton(widget_14);
        toolButton_15->setObjectName(QString::fromUtf8("toolButton_15"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/player/picture/player/mini.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_15->setIcon(icon1);
        toolButton_15->setIconSize(QSize(16, 16));
        toolButton_15->setAutoRaise(true);

        horizontalLayout_8->addWidget(toolButton_15);

        toolButton_14 = new QToolButton(widget_14);
        toolButton_14->setObjectName(QString::fromUtf8("toolButton_14"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/player/picture/player/minisize.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_14->setIcon(icon2);
        toolButton_14->setIconSize(QSize(16, 16));
        toolButton_14->setAutoRaise(true);

        horizontalLayout_8->addWidget(toolButton_14);

        toolButton_13 = new QToolButton(widget_14);
        toolButton_13->setObjectName(QString::fromUtf8("toolButton_13"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/player/picture/player/maxsize.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_13->setIcon(icon3);
        toolButton_13->setIconSize(QSize(16, 16));
        toolButton_13->setAutoRaise(true);

        horizontalLayout_8->addWidget(toolButton_13);

        toolButton_12 = new QToolButton(widget_14);
        toolButton_12->setObjectName(QString::fromUtf8("toolButton_12"));
        toolButton_12->setFocusPolicy(Qt::TabFocus);
        toolButton_12->setAutoFillBackground(false);
        toolButton_12->setStyleSheet(QString::fromUtf8(""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/player/picture/player/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_12->setIcon(icon4);
        toolButton_12->setIconSize(QSize(22, 22));
        toolButton_12->setAutoRepeat(true);
        toolButton_12->setAutoRaise(true);

        horizontalLayout_8->addWidget(toolButton_12);


        horizontalLayout_9->addWidget(widget_14);


        gridLayout->addWidget(widget_12, 0, 0, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        widget->setMouseTracking(true);
        widget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_5 = new QWidget(widget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        sizePolicy3.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy3);
        widget_5->setMinimumSize(QSize(660, 400));
        widget_5->setMouseTracking(true);
        widget_5->setLayoutDirection(Qt::LeftToRight);
        widget_5->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_4 = new QVBoxLayout(widget_5);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_11 = new QWidget(widget_5);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        widget_11->setMouseTracking(true);
        widget_11->setStyleSheet(QString::fromUtf8("border-right-color: rgb(170, 0, 0);"));
        verticalLayout_5 = new QVBoxLayout(widget_11);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget_2 = new VideoWidget(widget_11);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        sizePolicy3.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy3);
        widget_2->setMinimumSize(QSize(400, 300));
        QFont font;
        font.setPointSize(9);
        widget_2->setFont(font);
        widget_2->setMouseTracking(true);
        widget_2->setAutoFillBackground(false);
        widget_2->setStyleSheet(QString::fromUtf8("#widget_2{\n"
"		border-image: url(:/pic/picture/bg.jpg);\n"
"}\n"
"\n"
""));
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(9, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        toolButton_10 = new QToolButton(widget_2);
        toolButton_10->setObjectName(QString::fromUtf8("toolButton_10"));
        sizePolicy2.setHeightForWidth(toolButton_10->sizePolicy().hasHeightForWidth());
        toolButton_10->setSizePolicy(sizePolicy2);
        toolButton_10->setMouseTracking(true);
        toolButton_10->setFocusPolicy(Qt::NoFocus);
        toolButton_10->setStyleSheet(QString::fromUtf8("\n"
"\n"
"#toolButton_10{\n"
" font: 12pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/player/picture/player/\346\226\207\344\273\266\345\244\271.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_10->setIcon(icon5);
        toolButton_10->setIconSize(QSize(40, 40));
        toolButton_10->setPopupMode(QToolButton::InstantPopup);
        toolButton_10->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_10->setAutoRaise(true);
        toolButton_10->setArrowType(Qt::NoArrow);

        horizontalLayout_7->addWidget(toolButton_10);


        verticalLayout_3->addLayout(horizontalLayout_7);


        verticalLayout_5->addWidget(widget_2);


        verticalLayout_4->addWidget(widget_11);

        widget_6 = new QWidget(widget_5);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        sizePolicy1.setHeightForWidth(widget_6->sizePolicy().hasHeightForWidth());
        widget_6->setSizePolicy(sizePolicy1);
        widget_6->setMinimumSize(QSize(100, 50));
        widget_6->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 17,17);"));
        verticalLayout = new QVBoxLayout(widget_6);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSlider = new QSlider(widget_6);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        sizePolicy1.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy1);
        horizontalSlider->setMinimumSize(QSize(0, 12));
        horizontalSlider->setMaximumSize(QSize(16777215, 12));
        horizontalSlider->setCursor(QCursor(Qt::PointingHandCursor));
        horizontalSlider->setFocusPolicy(Qt::StrongFocus);
        horizontalSlider->setToolTipDuration(-1);
        horizontalSlider->setAutoFillBackground(false);
        horizontalSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal,QSlider::add-page:horizontal{\n"
"height:3px;\n"
"border-radius:3px;\n"
"background:#18181a;\n"
"margin-top:0px;\n"
"}\n"
"\n"
"\n"
"QSlider::sub-page:horizontal{\n"
"height:8px;\n"
"border-radius:3px;\n"
"background:#008aff;\n"
"}\n"
"\n"
"\n"
"QSlider::handle:horizontal{\n"
"width:12px;\n"
"margin-top:-5px;\n"
"margin-bottom:-4px;\n"
"border-radius:6px;\n"
"background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #565656,stop:0.8 #565656);\n"
"}\n"
"\n"
"\n"
"QSlider::groove:vertical,QSlider::sub-page:vertical{\n"
"width:8px;\n"
"border-radius:3px;\n"
"background:#D8D8D8;\n"
"}\n"
"\n"
"\n"
"QSlider::add-page:vertical{\n"
"width:8px;\n"
"border-radius:3px;\n"
"background:#008aff;\n"
"}\n"
"\n"
"\n"
"QSlider::handle:vertical{\n"
"height:12px;\n"
"margin-left:-5px;\n"
"margin-right:-4px;\n"
"border-radius:6px;\n"
"background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #565656,stop:0.8 #565656);\n"
"}"));
        horizontalSlider->setMaximum(0);
        horizontalSlider->setSingleStep(5);
        horizontalSlider->setPageStep(5);
        horizontalSlider->setValue(0);
        horizontalSlider->setSliderPosition(0);
        horizontalSlider->setTracking(true);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedAppearance(false);
        horizontalSlider->setInvertedControls(false);
        horizontalSlider->setTickPosition(QSlider::NoTicks);
        horizontalSlider->setTickInterval(0);

        verticalLayout->addWidget(horizontalSlider);

        widget_7 = new QWidget(widget_6);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        sizePolicy3.setHeightForWidth(widget_7->sizePolicy().hasHeightForWidth());
        widget_7->setSizePolicy(sizePolicy3);
        horizontalLayout_6 = new QHBoxLayout(widget_7);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 4, 0, 0);
        widget_9 = new QWidget(widget_7);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        sizePolicy1.setHeightForWidth(widget_9->sizePolicy().hasHeightForWidth());
        widget_9->setSizePolicy(sizePolicy1);
        horizontalLayout_3 = new QHBoxLayout(widget_9);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(12, 0, 0, 2);
        label = new QLabel(widget_9);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(110, 0));
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_6 = new QSpacerItem(32, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        horizontalLayout_6->addWidget(widget_9);

        widget_8 = new QWidget(widget_7);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        sizePolicy2.setHeightForWidth(widget_8->sizePolicy().hasHeightForWidth());
        widget_8->setSizePolicy(sizePolicy2);
        widget_8->setToolTipDuration(-5);
        horizontalLayout_4 = new QHBoxLayout(widget_8);
        horizontalLayout_4->setSpacing(16);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 2);
        toolButton_6 = new QToolButton(widget_8);
        toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));
        toolButton_6->setStyleSheet(QString::fromUtf8(""));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/player/picture/player/media-stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_6->setIcon(icon6);
        toolButton_6->setIconSize(QSize(12, 12));
        toolButton_6->setAutoRepeat(false);
        toolButton_6->setAutoExclusive(false);
        toolButton_6->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButton_6->setAutoRaise(true);

        horizontalLayout_4->addWidget(toolButton_6);

        toolButton_9 = new QToolButton(widget_8);
        toolButton_9->setObjectName(QString::fromUtf8("toolButton_9"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/player/picture/player/media-previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_9->setIcon(icon7);
        toolButton_9->setIconSize(QSize(12, 12));
        toolButton_9->setAutoRaise(true);

        horizontalLayout_4->addWidget(toolButton_9);

        toolButton_7 = new QToolButton(widget_8);
        toolButton_7->setObjectName(QString::fromUtf8("toolButton_7"));
        toolButton_7->setAutoFillBackground(false);
        toolButton_7->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);\n"
"QToolButton {\n"
"font-size:100px; \n"
"color:yellow; \n"
"border-radius:150px; \n"
"background-color:rgba(0,255,0,200);\n"
"}\n"
"\n"
"QToolButton:hover { \n"
"font-size:100px;\n"
"color:green;\n"
"border-radius:150px;\n"
"background-color:rgba(255,255,0,200); \n"
"}\n"
"QToolButton:pressed { \n"
"color:orange;\n"
"border-width:3;\n"
"border-color:orange;\n"
"border-style:solid;;\n"
"background-color:cyan; \n"
"}\n"
""));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/player/picture/player/media-pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_7->setIcon(icon8);
        toolButton_7->setIconSize(QSize(30, 30));
        toolButton_7->setAutoRepeat(false);
        toolButton_7->setAutoRaise(true);

        horizontalLayout_4->addWidget(toolButton_7);

        toolButton_8 = new QToolButton(widget_8);
        toolButton_8->setObjectName(QString::fromUtf8("toolButton_8"));
        toolButton_8->setStyleSheet(QString::fromUtf8("background-color: rgba(17, 17, 17, 0);\n"
""));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/player/picture/player/media-next.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_8->setIcon(icon9);
        toolButton_8->setIconSize(QSize(12, 12));
        toolButton_8->setAutoRaise(true);

        horizontalLayout_4->addWidget(toolButton_8);

        toolButton_5 = new QToolButton(widget_8);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/player/picture/player/sound.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_5->setIcon(icon10);
        toolButton_5->setIconSize(QSize(16, 16));
        toolButton_5->setAutoRepeat(true);
        toolButton_5->setAutoRaise(true);

        horizontalLayout_4->addWidget(toolButton_5);


        horizontalLayout_6->addWidget(widget_8);

        widget_10 = new QWidget(widget_7);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        sizePolicy1.setHeightForWidth(widget_10->sizePolicy().hasHeightForWidth());
        widget_10->setSizePolicy(sizePolicy1);
        horizontalLayout_5 = new QHBoxLayout(widget_10);
        horizontalLayout_5->setSpacing(14);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 12, 2);
        horizontalSlider_2 = new QSlider(widget_10);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        sizePolicy2.setHeightForWidth(horizontalSlider_2->sizePolicy().hasHeightForWidth());
        horizontalSlider_2->setSizePolicy(sizePolicy2);
        horizontalSlider_2->setMinimumSize(QSize(84, 22));
        horizontalSlider_2->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal,QSlider::add-page:horizontal{\n"
"height:3px;\n"
"border-radius:3px;\n"
"background:#18181a;\n"
"margin-top:0px;\n"
"}\n"
"\n"
"\n"
"QSlider::sub-page:horizontal{\n"
"height:8px;\n"
"border-radius:3px;\n"
"background:#008aff;\n"
"}\n"
"\n"
"\n"
"QSlider::handle:horizontal{\n"
"width:12px;\n"
"margin-top:-5px;\n"
"margin-bottom:-4px;\n"
"border-radius:6px;\n"
"background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #565656,stop:0.8 #565656);\n"
"}\n"
"\n"
"\n"
"QSlider::groove:vertical,QSlider::sub-page:vertical{\n"
"width:8px;\n"
"border-radius:3px;\n"
"background:#D8D8D8;\n"
"}\n"
"\n"
"\n"
"QSlider::add-page:vertical{\n"
"width:8px;\n"
"border-radius:3px;\n"
"background:#008aff;\n"
"}\n"
"\n"
"\n"
"QSlider::handle:vertical{\n"
"height:12px;\n"
"margin-left:-5px;\n"
"margin-right:-4px;\n"
"border-radius:6px;\n"
"background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #565656,stop:0.8 #565656);\n"
"}"));
        horizontalSlider_2->setMaximum(128);
        horizontalSlider_2->setSingleStep(5);
        horizontalSlider_2->setValue(80);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(horizontalSlider_2);

        horizontalSpacer_5 = new QSpacerItem(8, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        toolButton_17 = new QToolButton(widget_10);
        toolButton_17->setObjectName(QString::fromUtf8("toolButton_17"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/player/picture/player/menubeisu.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_17->setIcon(icon11);
        toolButton_17->setIconSize(QSize(16, 16));
        toolButton_17->setAutoRaise(true);

        horizontalLayout_5->addWidget(toolButton_17);

        toolButton_11 = new QToolButton(widget_10);
        toolButton_11->setObjectName(QString::fromUtf8("toolButton_11"));
        sizePolicy2.setHeightForWidth(toolButton_11->sizePolicy().hasHeightForWidth());
        toolButton_11->setSizePolicy(sizePolicy2);
        toolButton_11->setStyleSheet(QString::fromUtf8("#toolButton_11::menu-indicator {\n"
"     image: none;\n"
"}"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/player/picture/player/tool.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_11->setIcon(icon12);
        toolButton_11->setIconSize(QSize(16, 16));
        toolButton_11->setAutoRaise(true);

        horizontalLayout_5->addWidget(toolButton_11);

        toolButton_16 = new QToolButton(widget_10);
        toolButton_16->setObjectName(QString::fromUtf8("toolButton_16"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/player/picture/player/menumaxsize.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_16->setIcon(icon13);
        toolButton_16->setIconSize(QSize(16, 16));
        toolButton_16->setAutoRaise(true);

        horizontalLayout_5->addWidget(toolButton_16);


        horizontalLayout_6->addWidget(widget_10);


        verticalLayout->addWidget(widget_7);


        verticalLayout_4->addWidget(widget_6);


        horizontalLayout_2->addWidget(widget_5);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy4);
        widget_3->setMinimumSize(QSize(256, 500));
        widget_3->setMouseTracking(true);
        widget_3->setStyleSheet(QString::fromUtf8("background-color: rgb(17,17,17);"));
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        sizePolicy2.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy2);
        widget_4->setMinimumSize(QSize(100, 0));
        widget_4->setMouseTracking(true);
        widget_4->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(widget_4);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(90, 4, 0, 0);
        toolButton_3 = new QToolButton(widget_4);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setToolTipDuration(-1);
        toolButton_3->setAutoFillBackground(false);
        toolButton_3->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgba(255, 255, 255, 0);"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/player/picture/player/suonuetu.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon14);
        toolButton_3->setIconSize(QSize(20, 20));
        toolButton_3->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_3);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        toolButton_4 = new QToolButton(widget_4);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        toolButton_4->setStyleSheet(QString::fromUtf8("#toolButton_4::menu-indicator {\n"
"     image: none;\n"
"}\n"
"\n"
""));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/player/picture/player/listxunhuan.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_4->setIcon(icon15);
        toolButton_4->setIconSize(QSize(20, 20));
        toolButton_4->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_4);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButton_2 = new QToolButton(widget_4);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/player/picture/player/player-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon16);
        toolButton_2->setIconSize(QSize(20, 20));
        toolButton_2->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_2);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        toolButton = new QToolButton(widget_4);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/player/picture/player/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon17);
        toolButton->setIconSize(QSize(20, 20));
        toolButton->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_2->addWidget(widget_4);

        listWidget = new QListWidget(widget_3);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        sizePolicy4.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy4);
        listWidget->setMinimumSize(QSize(150, 0));
        listWidget->setMouseTracking(true);
        listWidget->setStyleSheet(QString::fromUtf8("background-color: rgba(17, 17, 17, 0);"));
        listWidget->setFrameShape(QFrame::NoFrame);
        listWidget->setFrameShadow(QFrame::Plain);
        listWidget->setLineWidth(0);
        listWidget->setIconSize(QSize(100, 70));
        listWidget->setTextElideMode(Qt::ElideLeft);
        listWidget->setMovement(QListView::Static);
        listWidget->setResizeMode(QListView::Fixed);
        listWidget->setSpacing(0);
        listWidget->setViewMode(QListView::ListMode);

        verticalLayout_2->addWidget(listWidget);


        horizontalLayout_2->addWidget(widget_3);


        gridLayout->addWidget(widget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MyMediaPlayer", nullptr));
        label_3->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "MyMediaPlayer", nullptr));
        label_2->setText(QString());
#if QT_CONFIG(tooltip)
        toolButton_15->setToolTip(QCoreApplication::translate("MainWindow", "\350\277\267\344\275\240\346\250\241\345\274\217", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_15->setText(QString());
#if QT_CONFIG(tooltip)
        toolButton_14->setToolTip(QCoreApplication::translate("MainWindow", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_14->setText(QString());
#if QT_CONFIG(tooltip)
        toolButton_13->setToolTip(QCoreApplication::translate("MainWindow", "\346\234\200\345\244\247\345\214\226", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_13->setText(QString());
#if QT_CONFIG(tooltip)
        toolButton_12->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_12->setText(QString());
        toolButton_10->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        horizontalSlider->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/pic/picture/fileadd.png\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QString());
#if QT_CONFIG(tooltip)
        toolButton_6->setToolTip(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\346\222\255\346\224\276", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_6->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_9->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\344\270\212\344\270\200\344\270\252", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_9->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_7->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_7->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_8->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\344\270\213\344\270\200\344\270\252", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_8->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_5->setToolTip(QCoreApplication::translate("MainWindow", "\351\235\231\351\237\263", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_5->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        horizontalSlider_2->setToolTip(QCoreApplication::translate("MainWindow", "\351\237\263\351\207\217\350\260\203\350\212\202", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        toolButton_17->setToolTip(QCoreApplication::translate("MainWindow", "\345\200\215\351\200\237\350\256\276\347\275\256", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_17->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_11->setToolTip(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267\347\256\261", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_11->setText(QString());
#if QT_CONFIG(tooltip)
        toolButton_16->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\250\345\261\217\346\250\241\345\274\217", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_16->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_3->setToolTip(QCoreApplication::translate("MainWindow", "\345\210\207\346\215\242\345\210\260\345\210\227\350\241\250", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_3->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_4->setToolTip(QCoreApplication::translate("MainWindow", "\351\241\272\345\272\217\346\222\255\346\224\276", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_4->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_2->setToolTip(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton->setToolTip(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\345\210\227\350\241\250", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
