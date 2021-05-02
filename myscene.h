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
#include <QPainter>
#include <QPixmap>
#include <QCoreApplication>

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

    // creation map
    QList<QList<int>> map;
    int mapWidth;
    QPixmap fond;

    signed int objRectPos = 0;
    int matricePos = 0;

    void init();

    void createMap();

    void display();

    void destroy();

    // est-on en train de se déplacer ?
    bool isTowardLeft;
    bool isTowardRight;
    bool isTowardUp;
    bool saut = false;
    bool tombe = false;
    bool sautDispo = true;

    // tuile du niveau
    QPixmap objPixmap;
    QGraphicsPixmapItem * objRect;
    qreal objRectWidth = 16;
    qreal objRectHeight = 16;
    qreal sol = 192;

    // Mario
    QPixmap imgMario;
    QGraphicsPixmapItem* mario;
    qreal marioWidth = 16;
    qreal marioHeight = 16;
    signed int marioSaut = 0;
    int marioSprite = 0;


    // timer
    QTimer* timer;
    int dt = 5;

    // touches gauche et droite
    bool event(QEvent*) override;

private slots:
    void update();

};

#endif // MYSCENE_H
