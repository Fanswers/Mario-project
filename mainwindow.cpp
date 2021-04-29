#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // raccourci clavier : ecape pour quitter
    QShortcut* escape = new QShortcut(Qt::Key::Key_Escape, this);
    connect(escape, SIGNAL(activated()), this, SLOT(escapeAction()));

    // initialisation de la scene
    myScene = new MyScene();
    ui->graphicsView->setScene(myScene);
    QTimer::singleShot(0, this, SLOT(afterLoad()));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resize(){
    int widthGraphicsView = centralWidget()->width()- 200;
    int heightGraphicsView = centralWidget()->height()*0.95;

    if (widthGraphicsView < 200) {
        widthGraphicsView = 200;
    }
    if (heightGraphicsView < 200) {
        heightGraphicsView = 200;
    }

    if (widthGraphicsView > heightGraphicsView) {
        widthGraphicsView = heightGraphicsView;
    }
    else if (widthGraphicsView < heightGraphicsView) {
        heightGraphicsView = widthGraphicsView;
    }
    ui -> graphicsView -> setFixedSize(widthGraphicsView,heightGraphicsView);
    ui -> graphicsView -> fitInView(myScene->sceneRect());
}

void MainWindow::resizeEvent(QResizeEvent *) {
    resize();
}

void MainWindow::afterLoad() {
    resize();
    ui->graphicsView->show();
    ui->graphicsView->setFocus();
}

void MainWindow::escapeAction(){
    QApplication::quit();
}
