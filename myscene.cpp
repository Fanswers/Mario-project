#include "myscene.h"


myScene::myScene() : QWidget()
{
    this -> setFixedSize(1500,1000);


    QPixmap bkgnd(QCoreApplication::applicationDirPath() + "/../../mario-project/Img/Map.png");
    bkgnd = bkgnd.scaled(15000,1000);

    //Décalage du background
    QRegion exposed;
    int x = 0;
    bkgnd.scroll(x, 0, bkgnd.rect(), &exposed);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    m_bouton = new QPushButton("", this);
    m_bouton->setCursor(Qt::PointingHandCursor);
    m_bouton->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/../../mario-project/Img/Starto.png"));
    m_bouton->setIconSize(QSize(500,250));
    m_bouton->setGeometry(500,375,500,250);

    QObject::connect(m_bouton, SIGNAL(clicked()), m_bouton, SLOT(close()));
}



bool myScene::event(QEvent* event) {
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key()==Qt::Key_Z) {
            qDebug() << "Haut";
        } else if (key->key()==Qt::Key_Q) {
            qDebug() << "Gauche";
        } else if (key->key()==Qt::Key_S) {
            qDebug() << "Bas";
        } else if (key->key()==Qt::Key_D) {
            qDebug() << "Droite";
        }
        else {
            return QWidget::event(event);
        }
        return true;
    } else {
        return QWidget::event(event);
    }
    return false;
}


