QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    messsagewidget.cpp \
    mylistwidget.cpp \
    picturelable.cpp \
    player.cpp \
    playingthread.cpp \
    speedcontrolslider.cpp \
    titlebar.cpp \
    translucentwidget.cpp \
    updatetimethread.cpp \
    videowidget.cpp \
    sonic.c
HEADERS += \
    mainwindow.h \
    messsagewidget.h \
    mylistwidget.h \
    picturelable.h \
    player.h \ \
    playingthread.h \
    speedcontrolslider.h \
    titlebar.h \
    translucentwidget.h \
    updatetimethread.h \
    videowidget.h \
    sonic.h
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32: LIBS +=  -L$$PWD/lib/ -lSDL2main \
                -L$$PWD/lib/ -lSDL2 \
                -L$$PWD/lib/ -lavcodec \
                -L$$PWD/lib/ -lavutil \
                -L$$PWD/lib/ -lpostproc \
                -L$$PWD/lib/ -lswresample \
                -L$$PWD/lib/ -lswscale \
                -L$$PWD/lib/ -lavformat \
                -L$$PWD/lib/ -lavdevice \
                -L$$PWD/lib/ -lavfilter \

RC_FILE += myapp.rc
RC_ICONS = app.ico

















