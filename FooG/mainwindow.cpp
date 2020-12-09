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
    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();

    drawer = new Drawer(this);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setAlignment(Qt::AlignCenter);

    QImage tempImage = QImage(width, height, QImage::Format_RGB32);
    tempImage.fill(drawer->getBGColor());

    drawer->initZBuffer(width, height);
    drawer->initImage(tempImage);

    ui->graphicsView->setScene(drawer);

    drawer->addPixmap(QPixmap::fromImage(tempImage));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    switch (key)
    {
    case Qt::Key_Space:
        drawer->drawScene();
        break;
    case Qt::Key_W:
        drawer->cameraMove(Vector3f(0, 0, 50));
        drawer->drawScene();
        break;
    case Qt::Key_S:
        drawer->cameraMove(Vector3f(0, 0, -50));
        drawer->drawScene();
        break;
    case Qt::Key_A:
        drawer->cameraMove(Vector3f(-50, 0, 0));
        drawer->drawScene();
        break;
    case Qt::Key_D:
        drawer->cameraMove(Vector3f(50, 0, 0));
        drawer->drawScene();
        break;
    case Qt::Key_I:
        drawer->cameraTurn(Vector3f(0.1, 0, 0));
        drawer->drawScene();
        break;
    case Qt::Key_J:
        drawer->cameraTurn(Vector3f(0, -0.1, 0));
        drawer->drawScene();
        break;
    case Qt::Key_K:
        drawer->cameraTurn(Vector3f(-0.1, 0, 0));
        drawer->drawScene();
        break;
    case Qt::Key_L:
        drawer->cameraTurn(Vector3f(0, 0.1, 0));
        drawer->drawScene();
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
