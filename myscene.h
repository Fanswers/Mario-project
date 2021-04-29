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

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene();

private:

    // dimension du repère:
    const int WIDTH = 1000;
    const int HEIGHT = 1000;

};

#endif // MYSCENE_H
