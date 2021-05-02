#include "myscene.h"

MyScene::MyScene()
{
    // coordonnées de la scene
    this->setSceneRect(0, 0, WIDTH, HEIGHT);

    // background

    fond = QPixmap("../mario-project/img/fond.png");
    fond = fond.scaled(WIDTH + 2, HEIGHT + 2);
    QBrush *brush = new QBrush(fond);

    this->setBackgroundBrush(*brush);

    // timer
    timer = new QTimer();
    timer->setInterval(dt);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    init();
}

void MyScene::init()
{
    isTowardLeft = false;
    isTowardRight = false;

    createMap();
    qDebug() << map;
}

// Lis le level.csv et le stock dans une liste de string
void MyScene::createMap()
{
    QFile file("../mario-project/lvl/level1.csv");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
    }

    while (!file.atEnd())
    {
        QString line = file.readLine();
        line.remove("\r\n");
        line.replace(',', ' ');
        QTextStream stream(&line);
        QList<int> array;
        while (!stream.atEnd())
        {
            int number;
            stream >> number;
            array.append(number);
        }
        map.append(array);
    }
    mapWidth = map[0].length();
}

// créer les tuiles + Mario
void MyScene::display()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = -1; j < 31; j++)
        {
            if (map[i][matricePos + j + 1] != -1)
            {
                objPixmap.load("../mario-project/img/finalSpriteObject.png");
                objPixmap = objPixmap.copy(map[i][matricePos + j + 1] * 16, 0, 16, 16);
                objRect = this->addPixmap(objPixmap);
                objRect->setPos((j * objRectWidth) + (objRectPos / 10), i * objRectHeight);
            }
        }
    }
    imgMario.load("../mario-project/img/finalSpriteMario.png");
    imgMario = imgMario.copy(marioSprite * 16, 0, 16, 16);
    imgMario = imgMario.scaled(marioWidth, marioHeight);
    mario = this->addPixmap(imgMario);
    mario->setPos(16, sol + marioSaut);
}

// détruit toutes les tuiles présentes
void MyScene::destroy()
{
    QList<QGraphicsItem *> all = items();
    for (int i = 0; i < all.size(); i++)
    {
        QGraphicsItem *gi = all[i];
        if (gi->parentItem() == NULL)
        {
            delete gi;
        }
    }
}

// start / pause
void MyScene::startPause()
{
    if (timer->isActive())
    {
        timer->stop();
    }
    else
    {
        timer->start();
    }
}

void MyScene::update()
{
    //qDebug() << "enclanchement";
    if (isTowardLeft && matricePos > 0)
    {
        if (objRectPos < 100 && objRectPos >= 0)
        {
            objRectPos += 10;
        }
        else
        {
            objRectPos = 0;
            matricePos -= 1;
        }
        qDebug() << objRectPos;
    }
    if (isTowardRight && matricePos < mapWidth - 32)
    {
        if (objRectPos > -100 && objRectPos <= 0)
        {
            objRectPos -= 10;
        }
        else
        {
            objRectPos = 0;
            matricePos += 1;
        }
        qDebug() << objRectPos;
    }

    //action du saut
    if (isTowardUp and sautDispo)
    {
        saut = true;
        sautDispo = false;
    }
    if (saut and (sol + marioSaut) > 96)
    {
        marioSaut -= 1;
        tombe = false;
        qDebug() << "Je saute";

        // changement de l'image
        marioSprite = 6;
    }
    else
    {
        tombe = true;
    }
    //chute
    if (tombe and (sol + marioSaut) < 192)
    {
        marioSaut += 1;
        saut = false;
    }
    if (sol + marioSaut == 192)
    {
        sautDispo = true;

        // changement de l'image
        marioSprite = 0;
    }
    destroy();
    display();
}

bool MyScene::event(QEvent *event)
{

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Left)
        {
            this->setIsTowardLeft(true);
            qDebug() << "On appuie sur la touche de gauche";
        }
        else if (keyEvent->key() == Qt::Key_Right)
        {
            this->setIsTowardRight(true);
            qDebug() << "On appuie sur la touche de droite";
        }
        else if (keyEvent->key() == Qt::Key_Up and saut == false)
        {
            this->setIsTowardUp(true);
            qDebug() << "On appuie sur la touche du haut";
        }
        //qDebug() << "touche appuyée";
    }
    else if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Left)
        {
            this->setIsTowardLeft(false);
            qDebug() << "On relâche sur la touche de gauche";
        }
        else if (keyEvent->key() == Qt::Key_Right)
        {
            this->setIsTowardRight(false);
            qDebug() << "On relâche sur la touche de droite";
        }
        else if (keyEvent->key() == Qt::Key_Up)
        {
            this->setIsTowardUp(false);
            qDebug() << "On relâche sur la touche du haut";
        }
    }
    return QGraphicsScene::event(event);
}
