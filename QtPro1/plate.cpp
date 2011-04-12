#include "plate.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

void Plate::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        // if event->pos not in Plate
        // just return
        if(event->pos().x() > 18*radio
           || event->pos().y() > 20*radio)
        {
            return;
        }


        clickid = -1;
        qDebug() << "left button";
        for(int i=0; i<32; i++)
        {
            Stone* p = stone[i];
            QRect rect = p->geometry();
            if(event->pos().x() >= rect.left()
                && event->pos().x() <= rect.right()
                && event->pos().y() >= rect.top()
                && event->pos().y() <= rect.bottom()
                && !stone[i]->killed)
            {
                clickid = i;
                break;
            }
        }

        if(selectid==-1)
        {
            if(clickid == -1)
            {

            }
            else
            {
                // clickid something
                if((clickid < 16 && redturn)
                   || (clickid >= 16 && !redturn))
                {
                    selectid = clickid;
                    stone[selectid]->selected = 1;
                    stone[selectid]->update();
                }
                else
                {
                    // clickid not my stone
                }
            }
        }
        else
        {
            if(clickid == -1)
            {

                QPoint p;
                p.setX(event->pos().x()/(radio*2) * radio*2);
                p.setY(event->pos().y()/(radio*2) * radio*2);
                stone[selectid]->setGeometry(p.x(), p.y(),
                                             radio*2, radio*2);
                stone[selectid]->selected = 0;
                stone[selectid]->update();
                this->redturn = !this->redturn;

                selectid = -1;
            }
            else
            {
                if((clickid < 16 && redturn)
                   || (clickid >= 16 && !redturn))
                {
                    // user change select
                    stone[selectid]->selected = 0;
                    stone[selectid]->update();
                    selectid = clickid;
                    stone[selectid]->selected = 1;
                    stone[selectid]->update();
                }
                else
                {
                    // user want to eat something
                    stone[clickid]->killed = 1;
                    stone[clickid]->hide();

                    stone[selectid]->pos = stone[clickid]->pos;
                    stone[selectid]->setGeometry
                            (stone[clickid]->geometry());

                    stone[selectid]->selected = 0;
                    stone[selectid]->update();
                    this->redturn = !this->redturn;
                    selectid = -1;
                }
            }
        }
    }
}

Plate::Plate(QWidget *parent) :
    QWidget(parent)
{
    radio = 30;
    selectid = -1;
    redturn = 1;


    Stone* p = new Stone(this);
    stone[0] = p;
    stone[0]->pos = QPoint(0, 0);
    stone[0]->type = 3;


    p = new Stone(this);
    stone[1] = p;
    stone[1]->pos = QPoint(1, 0);
    stone[1]->type = 4;


    p = new Stone(this);
    stone[2] = p;
    stone[2]->pos = QPoint(2, 0);
    stone[2]->type = 2;

    p = new Stone(this);
    stone[3] = p;
    stone[3]->pos = QPoint(3, 0);
    stone[3]->type = 1;


    p = new Stone(this);
    stone[4] = p;
    stone[4]->pos = QPoint(4, 0);
    stone[4]->type = 0;

    p = new Stone(this);
    stone[5] = p;
    stone[5]->pos = QPoint(5, 0);
    stone[5]->type = 1;


    p = new Stone(this);
    stone[6] = p;
    stone[6]->pos = QPoint(6, 0);
    stone[6]->type = 2;


    p = new Stone(this);
    stone[7] = p;
    stone[7]->pos = QPoint(7, 0);
    stone[7]->type = 4;


    p = new Stone(this);
    stone[8] = p;
    stone[8]->pos = QPoint(8, 0);
    stone[8]->type = 3;


    p = new Stone(this);
    stone[9] = p;
    stone[9]->pos = QPoint(1, 2);
    stone[9]->type = 5;


    p = new Stone(this);
    stone[10] = p;
    stone[10]->pos = QPoint(7, 2);
    stone[10]->type = 5;


    p = new Stone(this);
    stone[11] = p;
    stone[11]->pos = QPoint(0, 3);
    stone[11]->type = 6;

    p = new Stone(this);
    stone[12] = p;
    stone[12]->pos = QPoint(2, 3);
    stone[12]->type = 6;

    p = new Stone(this);
    stone[13] = p;
    stone[13]->pos = QPoint(4, 3);
    stone[13]->type = 6;

    p = new Stone(this);
    stone[14] = p;
    stone[14]->pos = QPoint(6, 3);
    stone[14]->type = 6;

    p = new Stone(this);
    stone[15] = p;
    stone[15]->pos = QPoint(8, 3);
    stone[15]->type = 6;
//------------------------------------------
    int a = 16;
    p = new Stone(this);
    stone[a+0] = p;
    stone[a+0]->pos = QPoint(0, 9);
    stone[a+0]->type = 3;


    p = new Stone(this);
    stone[a+1] = p;
    stone[a+1]->pos = QPoint(1, 9);
    stone[a+1]->type = 4;


    p = new Stone(this);
    stone[a+2] = p;
    stone[a+2]->pos = QPoint(2, 9);
    stone[a+2]->type = 2;

    p = new Stone(this);
    stone[a+3] = p;
    stone[a+3]->pos = QPoint(3, 9);
    stone[a+3]->type = 1;


    p = new Stone(this);
    stone[a+4] = p;
    stone[a+4]->pos = QPoint(4, 9);
    stone[a+4]->type = 0;

    p = new Stone(this);
    stone[a+5] = p;
    stone[a+5]->pos = QPoint(5, 9);
    stone[a+5]->type = 1;


    p = new Stone(this);
    stone[a+6] = p;
    stone[a+6]->pos = QPoint(6, 9);
    stone[a+6]->type = 2;


    p = new Stone(this);
    stone[a+7] = p;
    stone[a+7]->pos = QPoint(7, 9);
    stone[a+7]->type = 4;


    p = new Stone(this);
    stone[a+8] = p;
    stone[a+8]->pos = QPoint(8, 9);
    stone[a+8]->type = 3;


    p = new Stone(this);
    stone[a+9] = p;
    stone[a+9]->pos = QPoint(1, 7);
    stone[a+9]->type = 5;


    p = new Stone(this);
    stone[a+10] = p;
    stone[a+10]->pos = QPoint(7, 7);
    stone[a+10]->type = 5;


    p = new Stone(this);
    stone[a+11] = p;
    stone[a+11]->pos = QPoint(0, 6);
    stone[a+11]->type = 6;

    p = new Stone(this);
    stone[a+12] = p;
    stone[a+12]->pos = QPoint(2, 6);
    stone[a+12]->type = 6;

    p = new Stone(this);
    stone[a+13] = p;
    stone[a+13]->pos = QPoint(4, 6);
    stone[a+13]->type = 6;

    p = new Stone(this);
    stone[a+14] = p;
    stone[a+14]->pos = QPoint(6, 6);
    stone[a+14]->type = 6;

    p = new Stone(this);
    stone[a+15] = p;
    stone[a+15]->pos = QPoint(8, 6);
    stone[a+15]->type = 6;

    for(int i=0; i<32; i++)
    {
        p = stone[i];
        stone[i]->show();
        stone[i]->selected = 0;
        stone[i]->killed = 0;
        stone[i]->red = i<16;

        stone[i]->setGeometry(p->pos.x()*radio*2,
                              p->pos.y()*radio*2,
                              radio*2, radio*2);
    }
}

void Plate::paintEvent(QPaintEvent *)
{
    int i;
    QPainter paint;
    paint.begin(this);

    paint.drawRect(radio, radio,
                   16*radio, 18*radio);
    for(i=1; i<=8; i++)
    {
        paint.drawLine(QPoint(radio, radio+i*2*radio),
                       QPoint(radio+16*radio, radio+i*2*radio));
    }

    for(i=1; i<=7; i++)
    {
        paint.drawLine(QPoint(radio+i*2*radio, radio),
                       QPoint(radio+i*2*radio, radio+8*radio));
        paint.drawLine(QPoint(radio+i*2*radio, radio+10*radio),
                       QPoint(radio+i*2*radio, radio+18*radio));
    }

    paint.drawLine(QPoint(radio*7, radio),
                   QPoint(radio*11, 5*radio));
    paint.drawLine(QPoint(radio*11, radio),
                   QPoint(radio*7, 5*radio));

    paint.drawLine(QPoint(radio*7, 15*radio),
                   QPoint(radio*11, 19*radio));
    paint.drawLine(QPoint(radio*11, 15*radio),
                   QPoint(radio*7, 19*radio));

    paint.end();
}
