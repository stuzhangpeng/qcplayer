#ifndef FILETOOLBUTTON_H
#define FILETOOLBUTTON_H
#include<QTOOlButton>

class FileToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit FileToolButton(QToolButton *parent = nullptr);
    //void paintEvent(QPaintEvent* e);
signals:

};

#endif // FILETOOLBUTTON_H
