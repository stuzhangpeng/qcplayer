#ifndef PICTURELABLE_H
#define PICTURELABLE_H
#include<QLabel>
#include <QWidget>
class PictureLable : public QLabel
{
    Q_OBJECT
public:
    explicit PictureLable(QLabel *parent = nullptr);
signals:

};

#endif // PICTURELABLE_H
