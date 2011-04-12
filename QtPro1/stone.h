#ifndef STONE_H
#define STONE_H

#include <QWidget>

class Stone : public QWidget
{
    Q_OBJECT
public:
    explicit Stone(QWidget *parent = 0);

    QPoint pos; // plate
    int red; // 1 red, 0 black

    int selected; // 1 selected 0 not
    int killed; // 1 killed 0 not killed
    int type; // 0 帅jiang 1 shi 2 xiang 3che 4 ma 5 pao 6 bing

    void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // STONE_H
