#ifndef MYSCENE_H
#define MYSCENE_H


#include <QWidget>
#include <QPushButton>
#include <QApplication>

class myScene : public QWidget
{
public:
    myScene();

private:
    QPushButton *m_bouton;
    QRect *fond;
};

#endif // MYSCENE_H
