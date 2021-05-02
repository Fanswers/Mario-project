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
    for (int i = 0; i < 1; i++) { //16
        for (int j = 0; j < 1; j++) { //8
            objRect = new QGraphicsRectItem();

            test = QImage(QCoreApplication::applicationDirPath() + "/../../mario-project/Img/52571.png");
            test = test.copy(i*17,11+j*17,17,17);

            objRect -> setBrush(QImage(test.scaled(20,20)));

            this -> addItem(objRect);
            objRect -> setRect((i*objRectWidth)+objRectPos, j*objRectWidth,objRectWidth,objRectHeight);
        }
    }

    mario = new QGraphicsRectItem();
    imgMario = QImage(QCoreApplication::applicationDirPath() + "/../../mario-project/Img/Mario.png");
    imgMario = imgMario.copy(100,40,200,310);

    test3.load(QCoreApplication::applicationDirPath() + "/../../mario-project/Img/Mario.png");
    test3 = test3.copy(100,40,200,310);
    test3 = test3.scaled(20,20);
    test2.setPixmap(test3);

    QGraphicsPixmapItem *testo = this->addPixmap(test3);

    testo->setPos(marioWidthPos+10, marioHeightPos+marioPos);

    //mario -> setRect(marioWidthPos+10, marioHeightPos+marioPos,20,30);
    //mario -> setBrush(testo);

    //this -> addItem(mario);
    //mario -> setBrush(QImage(imgMario.scaled(20,30,Qt::IgnoreAspectRatio,Qt::TransformationMode())));
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
    //qDebug() << "enclanchement";
    if(isTowardLeft){
        objRectPos -= 3;
        qDebug() << objRectPos;
    }
    if(isTowardRight){
        objRectPos += 3;
        qDebug() << objRectPos;
    }
    // saut
    if(isTowardUp){
        saut = true;
    }
    if(saut and (marioHeightPos + marioPos) > 100) {
        marioPos -= 3;
        qDebug() << marioHeightPos;
    } else {
        saut = false;
        chute = true;
    }
    if (chute and marioPos < 0) {
        marioPos += 3;
    } else {
        chute = false;
    }

    this->removeItem(objRect);
    this->removeItem(mario);
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
        else if (keyEvent-> key() == Qt::Key_Up) {
            this -> setIsTowardUp(true);
            qDebug() << "On appuie sur la touche du haut";
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
        else if (keyEvent-> key() == Qt::Key_Up) {
            this -> setIsTowardUp(false);
            qDebug() << "On relâche sur la touche du haut";
        }
    }
    return QGraphicsScene::event(event);
}
