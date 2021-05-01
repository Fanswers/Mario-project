#include "myscene.h"


MyScene::MyScene()
{
    // coordonnées de la scene
    this -> setSceneRect(0, 0, WIDTH, HEIGHT);

    // background
//    QImage *image = new QImage("../mario-project/img/Map.png");
//    QBrush *brush = new QBrush(*image);
//    this -> setBackgroundBrush(*brush);

    // timer
    timer = new QTimer();
    timer -> setInterval(dt);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    init();
}

void MyScene::init()
{
    objRectPos = 0;

    isTowardLeft = false;
    isTowardRight = false;

    parseCsv();
    display();
}

// parse csv
void MyScene::parseCsv()
{
    QFile file("../mario-project/lvl/level1.csv");
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();
        }

        QStringList wordList;
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            wordList.append(line.split(',').first());
        }

        qDebug() << wordList;
}

// créer les tuiles
void MyScene::display()
{
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 1; j++) {
            objRect = new QGraphicsRectItem();
            objRect -> setBrush(QBrush(QColor(i+j,0,0)));
            objRect -> setPen(Qt::NoPen);
            this -> addItem(objRect);
            objRect -> setRect((i*objRectWidth)+objRectPos, j*objRectWidth,objRectWidth,objRectHeight);
        }
    }
}

// start / pause
void MyScene::startPause() {
    if (timer->isActive()) {
        timer->stop();
    }
    else {
        timer->start();
    }
}


void MyScene::update()
{
    qDebug() << "enclanchement";
    if(isTowardLeft){
        objRectPos -= dt;
        qDebug() << objRectPos;
    }
    if(isTowardRight){
        objRectPos += dt;
        qDebug() << objRectPos;
    }
    this->removeItem(objRect);
    display();
}

bool MyScene::event(QEvent* event) {

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent-> key() == Qt::Key_Left) {
            this -> setIsTowardLeft(true);
            qDebug() << "On appuie sur la touche de gauche";
        }
        else if (keyEvent-> key() == Qt::Key_Right) {
            this -> setIsTowardRight(true);
            qDebug() << "On appuie sur la touche de droite";
        }
        //qDebug() << "touche appuyée";
    }
    else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent-> key() == Qt::Key_Left) {
            this -> setIsTowardLeft(false);
            qDebug() << "On relâche sur la touche de gauche";
        }
        else if (keyEvent-> key() == Qt::Key_Right) {
            this -> setIsTowardRight(false);
            qDebug() << "On relâche sur la touche de droite";
        }
    }
    return QGraphicsScene::event(event);
}
