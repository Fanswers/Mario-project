#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QColor>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QImage>
#include <QFile>
#include <QStringList>
#include <QApplication>
#include <QPainter>

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene();

    void startPause();

    void setIsTowardLeft(bool b) {isTowardLeft = b;}
    void setIsTowardRight(bool b) {isTowardRight = b;}
    void setIsTowardUp(bool b) {isTowardUp = b;}

private:
    // dimension du repère:
    const int WIDTH = 480;
    const int HEIGHT = 240;

    signed int objRectPos = 0;
    signed int marioPos = 0;

    void init();

    void parseCsv();

    void display();

    // est-on en train de se déplacer ?
    bool isTowardLeft;
    bool isTowardRight;
    bool isTowardUp;
    bool saut = false;
    bool chute = false;

    // tuile du niveau
    QGraphicsRectItem* objRect;

    QPainter fondCube;
    QImage test;
    QGraphicsPixmapItem test2;
    QGraphicsPixmapItem testo;
    QPixmap test3;
    qreal objRectWidth = 20;
    qreal objRectHeight = 20;
    QGraphicsRectItem* mario;
    QImage imgMario;
    qreal marioWidthPos = 180;
    qreal marioHeightPos = 180;
    // timer
    QTimer* timer;
    int dt = 20;

    // touches gauche et droite
    bool event(QEvent*) override;

private slots:
    void update();

};

#endif // MYSCENE_H
