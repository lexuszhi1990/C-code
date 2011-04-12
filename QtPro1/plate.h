#ifndef PLATE_H
#define PLATE_H

#include <QWidget>
#include "stone.h"

class Plate : public QWidget
{
    Q_OBJECT
public:
    explicit Plate(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    int radio;
    int selectid;
    int clickid;
    int redturn;

    Stone* stone[32];
signals:

public slots:

};

#endif // PLATE_H
