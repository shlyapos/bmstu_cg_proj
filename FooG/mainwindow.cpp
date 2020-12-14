#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initDrawer();
}

void MainWindow::initDrawer()
{
    size_t w = ui->graphicsView->width();
    size_t h = ui->graphicsView->height();

    drawer = new Drawer(w, h, this);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setAlignment(Qt::AlignCenter);

    ui->graphicsView->setScene(drawer);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    switch (key)
    {
    case Qt::Key_Space:
        drawer->draw();
        break;

    case Qt::Key_W:
        drawer->movingCamera(1);
        drawer->draw();
        break;
    case Qt::Key_S:
        drawer->movingCamera(-1);
        drawer->draw();
        break;
    case Qt::Key_A:
        drawer->strafeCamera(-0.5);
        drawer->draw();
        break;
    case Qt::Key_D:
        drawer->strafeCamera(0.5);
        drawer->draw();
        break;

    case Qt::Key_I:
        drawer->upDownCamera(-0.25);
        drawer->draw();
        break;
    case Qt::Key_J:
        drawer->rotateCamera(-0.05);
        drawer->draw();
        break;
    case Qt::Key_K:
        drawer->upDownCamera(0.25);
        drawer->draw();
        break;
    case Qt::Key_L:
        drawer->rotateCamera(0.05);
        drawer->draw();
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
