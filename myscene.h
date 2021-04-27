#ifndef MYSCENE_H
#define MYSCENE_H


#include <QWidget>
#include <QPushButton>
#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

class myScene : public QWidget
{
public:
    myScene();
    void setIsTowardLeft(bool b) {isTowardLeft = b;}
    void setIsTowardRight(bool b) {isTowardRight = b;}
    bool event(QEvent* event);

private:
    QPushButton *m_bouton;
    bool isTowardLeft;
    bool isTowardRight;

protected:


};

#endif // MYSCENE_H
