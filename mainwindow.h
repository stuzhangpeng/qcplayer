#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"speedcontrolslider.h"
#include <QTextCodec>
#include <QMainWindow>
#include<QListWidget>
#include<QListWidgetItem>
#include<list>
#include "translucentwidget.h"
#include<QSize>
#include<string>
#include<updatetimethread.h>
#include <QFileDialog>
#include<QFileInfo>
#include<QDebug>
#include"player.h"
#include<QPixmap>
#include<iostream>
#include<QPainter>
#include<QTimer>
#include<QStaticText>
#include<QFile>
#include<videowidget.h>
#include<QResizeEvent>
#include<QThread>
#include"updatetimethread.h"
#include<QMenu>
#include"playingthread.h"
#include<QAction>
#include "messsagewidget.h"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
//鼠标的状态
enum WindowStretchRectState
{
    NO_SELECT = 0,              // 鼠标未进入下方矩形区域;
    LEFT_TOP_RECT,              // 鼠标在左上角区域;
    TOP_BORDER,                 // 鼠标在上边框区域;
    RIGHT_TOP_RECT,             // 鼠标在右上角区域;
    RIGHT_BORDER,               // 鼠标在右边框区域;
    RIGHT_BOTTOM_RECT,          // 鼠标在右下角区域;
    BOTTOM_BORDER,              // 鼠标在下边框区域;
    LEFT_BOTTOM_RECT,           // 鼠标在左下角区域;
    LEFT_BORDER                 // 鼠标在左边框区域;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MesssageWidget *messageWidget;
    SpeedControlSlider * slider;
    QMenu *  toolMenu;
    //播放模式 0 顺序播放 1 随机播放 2  单个播放 3单个循环 4列表循环
    int playingMode;
    //音乐播放渲染定时器
    QTimer* qtimer=new QTimer();
    //消息提示定时器
    QTimer* timer=new QTimer();
    QString storeFilePath="C:\\Users\\zhangpeng\\Desktop\\a.text";
    //解决双击触发单击的定时器
    QTimer* clickedTimer=new QTimer();
    //定时显示隐藏视频列表按钮
    QTimer* hiddenVideoListTimer=new QTimer();
    QString playingPath="null";
    //视频列表
    int lastVolume;
    //播放模式按钮菜单
    QMenu * playModelMenu;
    list<QString>videoList;
    //是否双击flag
    bool doubleClicked=false;
    //绘图标记
    bool boolFlag=false;
    //播放图片旋转角度
    int imageRotate = 0;
    //绘制消息
    bool hiddenVideoList=false;
    bool hiddenFlag=true;
    bool messageFlag=false;
    UpdateTimeThread * updateTimeThread=NULL;
    //记录当前正在播放的类型
    string playingType="null";
    bool imageList=true;
    void addHistoryVideoList();
    QPoint _previewInitPoit;
    QSize _previewInitSize    ;
    void initPlayer();
    QString formartPlayingTime(long long duration,long long  playingTime);
    bool findVideoList(QString filePath);
    void deleteSingleItem(QListWidgetItem * item,QString filePath);
    void graphMessageBox(QWidget *w);
    void closeShowPlayingTime();
    void pauseOrPlayVideo();
    QString formartTime(long long time);
    void addFile(QString filePath);
    void openFile();
    void showPlayingTime(long long duration);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPainter *painter;
    void translatePic();
    void playVideoByType(QString filePath);
    TranslucentWidget* transWidget;
    void createToolMenu();
    void createQslider();
    //窗口拉伸
    void  calculateStrenchRect();
    //窗口拉伸的8个区域
    QRect m_leftTopRect;
    QRect m_leftBottomRect;
    QRect m_rightTopRect;
    QRect m_rightBottomRect;
    QRect m_topBorderRect;
    QRect m_rightBorderRect;
    QRect m_bottomBorderRect;
    QRect m_leftBorderRect;
    //角的宽高
    int STRETCH_RECT_HEIGHT= 2;
    int STRETCH_RECT_WIDTH= 2;
    //窗口显示事件
    void showEvent(QShowEvent *event) override;
    //根据鼠标位置确定鼠标所在区域
    WindowStretchRectState getCurrentStretchState(QPoint cursorPos);
    //根据所在区域更新鼠标样式
    void updateMouseStyle(WindowStretchRectState stretchState);
    //窗口拉伸实现
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    //拉伸区域是否按下左键
    bool m_isMousePressed;
    //窗口拉伸前的鼠标位置
    QPoint m_startPoint;
    //窗口拉伸后鼠标位置
    QPoint m_endPoint;
    //鼠标样式区域
    WindowStretchRectState m_stretchRectState;
    //窗口拉伸前窗口所在的位置
    QRect  m_windowRectBeforeStretch;
    //拉伸窗口大小
    void updateWindowSize();
private slots:
    void on_toolButton_2_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_toolButton_clicked();
    void on_toolButton_6_clicked();
    void on_toolButton_7_clicked();
    void on_toolButton_9_clicked();
    void on_toolButton_5_clicked();
    void on_toolButton_8_clicked();
    void on_toolButton_10_clicked();
    void on_toolButton_3_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_toolButton_4_clicked();
    void selectPlayMode(QAction * action);
    void on_toolButton_14_clicked();

    void on_toolButton_13_clicked();

    void on_toolButton_12_clicked();

    void on_toolButton_16_clicked();

    void on_toolButton_11_clicked();

    void on_toolButton_17_clicked();
    void on_horizontalSlider_2_sliderReleased();

    void on_horizontalSlider_2_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    //绘图
    bool eventFilter(QObject *watched, QEvent *event);
    void graphChart(QWidget *w);
    void closeEvent(QCloseEvent *event);
    //最大化和最小化处理
    void changeEvent(QEvent *event);
    //窗口拉伸事件
    void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H
