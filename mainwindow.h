#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QDebug>
#include <QTimer>
#include <QShortcut>

#include "myscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // scène principale
    MyScene* myScene;

    // redimensionnements
    void resize();
    void resizeEvent(QResizeEvent*) override;

private slots:
    void afterLoad();
    void escapeAction();
    void spaceAction();
};
#endif // MAINWINDOW_H
