#include "stone.h"
#include <QPainter>

Stone::Stone(QWidget *parent) :
    QWidget(parent)
{
    setFont(QFont("wenquanyi", 20));
}

void Stone::paintEvent(QPaintEvent *)
{
    QPainter paint;
    paint.begin(this);

    if(this->selected)
        paint.setBrush(QBrush(QColor(128,128,0)));
    else
        paint.setBrush(QBrush(QColor(255,255,0)));
    paint.drawEllipse(0, 0, size().width(), size().height());

    if(red)
    {
        paint.setPen(QPen(QColor(255,0,0)));
    }
    else
    {
        paint.setPen(QPen(QColor(0,0,0)));
    }

    switch(type)
    {
    case 0:

        paint.drawText(0, 0,
                       this->size().width(),
                       this->size().height(),
                       Qt::AlignCenter|Qt::AlignVCenter,
                       QObject::trUtf8("帅"));
        break;
    case 1:
        paint.drawText(0, 0,
                       this->size().width(),
                       this->size().height(),
                       Qt::AlignCenter|Qt::AlignVCenter,
                       QObject::trUtf8("士"));
        break;
    case 2:
        paint.drawText(0, 0,
                       this->size().width(),
                       this->size().height(),
                       Qt::AlignCenter|Qt::AlignVCenter,
                       QObject::trUtf8("象"));
        break;
    case 3:
        paint.drawText(0, 0,
                       this->size().width(),
                       this->size().height(),
                       Qt::AlignCenter|Qt::AlignVCenter,
                       QObject::trUtf8("车"));
        break;
    case 4:
        paint.drawText(0, 0,
                       this->size().width(),
                       this->size().height(),
                       Qt::AlignCenter|Qt::AlignVCenter,
                       QObject::trUtf8("马"));
        break;
    case 5:
        paint.drawText(0, 0,
                       this->size().width(),
                       this->size().height(),
                       Qt::AlignCenter|Qt::AlignVCenter,
                       QObject::trUtf8("炮"));
        break;
    case 6:
        paint.drawText(0, 0,
                       this->size().width(),
                       this->size().height(),
                       Qt::AlignCenter|Qt::AlignVCenter,
                       QObject::trUtf8("兵"));
        break;
    }

    paint.end();
}
