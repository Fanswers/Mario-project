#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QColor>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QImage>
#include <QFile>
#include <QStringList>

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene();

    void startPause();

    void setIsTowardLeft(bool b) {isTowardLeft = b;}
    void setIsTowardRight(bool b) {isTowardRight = b;}

private:
    // dimension du repère:
    const int WIDTH = 480;
    const int HEIGHT = 240;

    signed int objRectPos = 0;

    void init();

    void parseCsv();

    void display();

    // est-on en train de se déplacer ?
    bool isTowardLeft;
    bool isTowardRight;

    // tuile du niveau
    QGraphicsRectItem* objRect;
    qreal objRectWidth = 16;
    qreal objRectHeight = 16;

    // timer
    QTimer* timer;
    int dt = 20;

    // touches gauche et droite
    bool event(QEvent*) override;

private slots:
    void update();

};

#endif // MYSCENE_H
