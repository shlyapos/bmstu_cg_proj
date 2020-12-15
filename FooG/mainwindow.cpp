#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("FooG");

    initDrawer();
    initButton();
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

void MainWindow::initButton()
{
    connect(ui->pushButton_addModel, SIGNAL(released()), this, SLOT(openAddModelWindow()));
    connect(ui->pushButton_addLight, SIGNAL(released()), this, SLOT(openAddLightWindow()));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    switch (key)
    {
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
        drawer->upDownCamera(0.25);
        drawer->draw();
        break;
    case Qt::Key_J:
        drawer->rotateCamera(-0.05);
        drawer->draw();
        break;
    case Qt::Key_K:
        drawer->upDownCamera(-0.25);
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
    if (addModelWindow->isVisible())
        addModelWindow->destroyed();

    if (addLightWindow->isVisible())
        addLightWindow->destroyed();

    delete ui;
}


// Add new model
void MainWindow::openAddModelWindow()
{
    addModelWindow = new AddModelWindow();

    connect(addModelWindow, SIGNAL(saveModelParams(AddModelParameters&)),
            this, SLOT(setAddModelParams(AddModelParameters&)));

    addModelWindow->show();
}

void MainWindow::setAddModelParams(AddModelParameters& newParams)
{
    Vector3f center(newParams.moveX, newParams.moveY, newParams.moveZ);
    Vector3f scaleK(newParams.scaleX, newParams.scaleY, newParams.scaleZ);

    drawer->addModel(center, scaleK, newParams.filename, newParams.color);
    drawer->draw();
}


// Add new light
void MainWindow::openAddLightWindow()
{
    addLightWindow = new AddLightWindow();

    connect(addLightWindow, SIGNAL(saveLightParams(AddLightParameters&)),
            this, SLOT(setAddLightParams(AddLightParameters&)));

    addLightWindow->show();
}

void MainWindow::setAddLightParams(AddLightParameters& newParams)
{
    Vector3f pos(-newParams.x, -newParams.y, -newParams.z);

    drawer->addLight(pos, newParams.power);
    drawer->draw();
}
