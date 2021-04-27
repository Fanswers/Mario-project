#include "myscene.h"


myScene::myScene() : QWidget()
{
    this -> setFixedSize(1500,1000);

    fond = new QRect(100,100,100,100);


    QPixmap bkgnd(QCoreApplication::applicationDirPath() + "/../../mario-project/Img/Map.png");
    bkgnd = bkgnd.scaled(15000,1000);

    //Décalage du background
    QRegion exposed;
    bkgnd.scroll(-10000, 0, bkgnd.rect(), &exposed);

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
