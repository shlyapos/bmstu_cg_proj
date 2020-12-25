#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

int frames = 0;
auto frameTime = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("FooG");
    this->setWindowIcon(QIcon("icon_speedrun.png"));

    ui->centralwidget->setStyleSheet("QWidget {background: rgba(50, 50, 50, 255);}");

    initDrawer();
    initLables();
    initButton();

    // Combobox
    connect(ui->comboBox_model, SIGNAL(currentIndexChanged(QString)), SLOT(changeModel()));
    connect(ui->comboBox_sprite, SIGNAL(currentIndexChanged(QString)), SLOT(changeSprite()));
    connect(ui->comboBox_light, SIGNAL(currentIndexChanged(QString)), SLOT(changeLight()));


    connect(ui->checkBox, SIGNAL(toggled(bool)), this, SLOT(constructorMode(bool)));

    modelCnt  = 0;
    spriteCnt = 0;
    lightCnt  = 0;

    lightPos.push_back(Vector3f(100, 1000, 100));
    drawer->addLight(Vector3f(100, 1000, 100), 1300);
    ui->comboBox_light->addItem("Main light");
}

MainWindow::~MainWindow()
{
    if (addModelWindow->isVisible())
        addModelWindow->destroyed();

    if (addLightWindow->isVisible())
        addLightWindow->destroyed();

    delete ui;
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

    connect(ui->pushButton_mapply, SIGNAL(released()), this, SLOT(applyModelChange()));
    connect(ui->pushButton_mcancel, SIGNAL(released()), this, SLOT(cancelLineEditsModel()));

    connect(ui->pushButton_sapply, SIGNAL(released()), this, SLOT(applySpriteChange()));
    connect(ui->pushButton_scancel, SIGNAL(released()), this, SLOT(cancelLineEditsSprite()));

    connect(ui->pushButton_lapply, SIGNAL(released()), this, SLOT(applyLightChange()));
    connect(ui->pushButton_lcancel, SIGNAL(released()), this, SLOT(cancelLineEditsLight()));
}

void MainWindow::initLables()
{
    // Models
    ui->lbl_models->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_model_move->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_mmove_x->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_mmove_y->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_mmove_z->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");

    ui->lbl_model_scale->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_mscale_x->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_mscale_y->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_mscale_z->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");

    ui->lbl_mrotate->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_mrotate_x->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_mrotate_y->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_mrotate_z->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");


    //Sprites
    ui->lbl_sprites->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_smove->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_smove_x->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_smove_y->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_smove_z->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");

    ui->lbl_sscale->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_sscale_x->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_sscale_y->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_sscale_z->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");

    ui->lbl_srotate->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_srotate_x->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_srotate_y->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_srotate_z->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");

    ui->lbl_smovement->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_smovement_x->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_smovement_y->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_smovement_z->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");

    ui->lbl_speed->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");


    // Lights
    ui->lbl_lights->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_lmove->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_lmove_x->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_lmove_y->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->lbl_lmove_z->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");

    ui->lbl_power->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
}



// Model
void MainWindow::changeModel()
{
    int idx = ui->comboBox_model->currentIndex();
    Vector3f currentCenter = centersM[idx];

    ui->le_mmove_x->setText(std::to_string(currentCenter.x).c_str());
    ui->le_mmove_y->setText(std::to_string(currentCenter.y).c_str());
    ui->le_mmove_z->setText(std::to_string(currentCenter.z).c_str());

    ui->le_mscale_x->setText("1");
    ui->le_mscale_y->setText("1");
    ui->le_mscale_z->setText("1");

    ui->le_mrotate_x->setText("0");
    ui->le_mrotate_y->setText("0");
    ui->le_mrotate_z->setText("0");
}

void MainWindow::applyModelChange()
{
    if (centersM.size() == 0)
        return;

    int idx = ui->comboBox_model->currentIndex();

    Vector3f center, scale, rotate;

    // For move
    if (ui->le_mmove_x->text().isEmpty() ||
        ui->le_mmove_y->text().isEmpty() ||
        ui->le_mmove_z->text().isEmpty())
    {
        center = Vector3f(centersM[idx]);
    }
    else
    {
        center = Vector3f(ui->le_mmove_x->text().toFloat(),
                          ui->le_mmove_y->text().toFloat(),
                          ui->le_mmove_z->text().toFloat());
    }

    // For scale
    if (ui->le_mscale_x->text().isEmpty() ||
        ui->le_mscale_y->text().isEmpty() ||
        ui->le_mscale_z->text().isEmpty())
    {
        scale = Vector3f(1, 1, 1);
    }
    else
    {
        scale = Vector3f(ui->le_mscale_x->text().toFloat(),
                         ui->le_mscale_y->text().toFloat(),
                         ui->le_mscale_z->text().toFloat());
    }

    // For rotate
    if (ui->le_mrotate_x->text().isEmpty() ||
        ui->le_mrotate_y->text().isEmpty() ||
        ui->le_mrotate_z->text().isEmpty())
    {
        rotate = Vector3f(0, 0, 0);
    }
    else
    {
        rotate = Vector3f(ui->le_mrotate_x->text().toFloat(),
                          ui->le_mrotate_y->text().toFloat(),
                          ui->le_mrotate_z->text().toFloat());
    }

    drawer->editModel(idx, center, scale, rotate);
    drawer->draw();
}

void MainWindow::cancelLineEditsModel()
{
    int idx = ui->comboBox_model->currentIndex();
    Vector3f currentCenter = centersM[idx];

    ui->le_lmove_x->setText(std::to_string(currentCenter.x).c_str());
    ui->le_lmove_y->setText(std::to_string(currentCenter.y).c_str());
    ui->le_lmove_z->setText(std::to_string(currentCenter.z).c_str());

    ui->le_mscale_x->setText("1");
    ui->le_mscale_y->setText("1");
    ui->le_mscale_z->setText("1");

    ui->le_mrotate_x->setText("0");
    ui->le_mrotate_y->setText("0");
    ui->le_mrotate_z->setText("0");
}



// Sprite
void MainWindow::changeSprite()
{
    int idx = ui->comboBox_sprite->currentIndex();
    Vector3f currentCenter = centersS[idx];

    ui->le_smove_x->setText(std::to_string(currentCenter.x).c_str());
    ui->le_smove_y->setText(std::to_string(currentCenter.y).c_str());
    ui->le_smove_z->setText(std::to_string(currentCenter.z).c_str());

    ui->le_sscale_x->setText("1");
    ui->le_sscale_y->setText("1");
    ui->le_sscale_z->setText("1");

    ui->le_srotate_x->setText("0");
    ui->le_srotate_y->setText("0");
    ui->le_srotate_z->setText("0");

    ui->le_smovement_x->setText(std::to_string(currentCenter.x).c_str());
    ui->le_smovement_y->setText(std::to_string(currentCenter.y).c_str());
    ui->le_smovement_z->setText(std::to_string(currentCenter.z).c_str());
}

void MainWindow::applySpriteChange()
{
    if (centersS.size() == 0)
        return;

    int idx = ui->comboBox_sprite->currentIndex();

    Vector3f center, scale, rotate;

    Vector3f endmovement;
    float speed;

    // For move
    if (ui->le_smove_x->text().isEmpty() ||
        ui->le_smove_y->text().isEmpty() ||
        ui->le_smove_z->text().isEmpty())
    {
        center = Vector3f(centersS[idx]);
    }
    else
    {
        center = Vector3f(ui->le_smove_x->text().toFloat(),
                          ui->le_smove_y->text().toFloat(),
                          ui->le_smove_z->text().toFloat());
    }

    // For scale
    if (ui->le_sscale_x->text().isEmpty() ||
        ui->le_sscale_y->text().isEmpty() ||
        ui->le_sscale_z->text().isEmpty())
    {
        scale = Vector3f(1, 1, 1);
    }
    else
    {
        scale = Vector3f(ui->le_sscale_x->text().toFloat(),
                         ui->le_sscale_y->text().toFloat(),
                         ui->le_sscale_z->text().toFloat());
    }

    // For rotate
    if (ui->le_srotate_x->text().isEmpty() ||
        ui->le_srotate_y->text().isEmpty() ||
        ui->le_srotate_z->text().isEmpty())
    {
        rotate = Vector3f(0, 0, 0);
    }
    else
    {
        rotate = Vector3f(ui->le_srotate_x->text().toFloat(),
                          ui->le_srotate_y->text().toFloat(),
                          ui->le_srotate_z->text().toFloat());
    }

    // For speed
    if (ui->le_speed->text().isEmpty())
        speed = 0.1;
    else
        speed = ui->le_speed->text().toFloat();

    // For end point of movement
    if (ui->le_smovement_x->text().isEmpty() ||
        ui->le_smovement_y->text().isEmpty() ||
        ui->le_smovement_z->text().isEmpty())
    {
        drawer->editSprite(idx, center, scale, rotate);
    }
    else
    {
        endmovement = Vector3f(ui->le_smovement_x->text().toFloat(),
                               ui->le_smovement_y->text().toFloat(),
                               ui->le_smovement_z->text().toFloat());
        if (ui->le_speed->text().isEmpty())
            speed = 0.1;
        else
            speed = ui->le_speed->text().toFloat();

        drawer->editSprite(idx, center, scale, rotate, endmovement, speed);
    }

    drawer->draw();
}

void MainWindow::cancelLineEditsSprite()
{
    int idx = ui->comboBox_sprite->currentIndex();
    Vector3f currentCenter = centersS[idx];

    ui->le_smove_x->setText(std::to_string(currentCenter.x).c_str());
    ui->le_smove_y->setText(std::to_string(currentCenter.y).c_str());
    ui->le_smove_z->setText(std::to_string(currentCenter.z).c_str());

    ui->le_sscale_x->setText("1");
    ui->le_sscale_y->setText("1");
    ui->le_sscale_z->setText("1");

    ui->le_srotate_x->setText("0");
    ui->le_srotate_y->setText("0");
    ui->le_srotate_z->setText("0");

    ui->le_smovement_x->setText(std::to_string(currentCenter.x).c_str());
    ui->le_smovement_y->setText(std::to_string(currentCenter.y).c_str());
    ui->le_smovement_z->setText(std::to_string(currentCenter.z).c_str());
}



// Light
void MainWindow::changeLight()
{
    int idx = ui->comboBox_light->currentIndex();
    Vector3f currentCenter = lightPos[idx];

    ui->le_lmove_x->setText(std::to_string(currentCenter.x).c_str());
    ui->le_lmove_y->setText(std::to_string(currentCenter.y).c_str());
    ui->le_lmove_z->setText(std::to_string(currentCenter.z).c_str());

    ui->le_power->setText("500");
}

void MainWindow::applyLightChange()
{
    if (lightPos.size() == 0)
        return;

    int idx = ui->comboBox_light->currentIndex();
    Vector3f pos;

    if (ui->le_lmove_x->text().isEmpty() ||
        ui->le_lmove_y->text().isEmpty() ||
        ui->le_lmove_z->text().isEmpty())
    {
        pos = lightPos[idx];
    }
    else
    {
        pos = Vector3f(ui->le_lmove_x->text().toFloat(),
                       ui->le_lmove_y->text().toFloat(),
                       ui->le_lmove_z->text().toFloat());
    }

    if (ui->le_power->text().isEmpty())
        drawer->editLight(idx, pos);
    else
        drawer->editLight(idx, pos, ui->le_power->text().toFloat());

    drawer->draw();
}

void MainWindow::cancelLineEditsLight()
{
    int idx = ui->comboBox_light->currentIndex();
    Vector3f currentCenter = lightPos[idx];

    ui->le_lmove_x->setText(std::to_string(currentCenter.x).c_str());
    ui->le_lmove_y->setText(std::to_string(currentCenter.y).c_str());
    ui->le_lmove_z->setText(std::to_string(currentCenter.z).c_str());

    ui->le_power->setText("200");
}



void MainWindow::constructorMode(bool value)
{
    if (value)
    {
        this->resize(990, 800);
    }
    else
    {
        this->resize(800, 800);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    switch (key)
    {
    case Qt::Key_W:
        drawer->movingCamera(1);
        break;
    case Qt::Key_S:
        drawer->movingCamera(-1);
        break;
    case Qt::Key_A:
        drawer->strafeCamera(-0.5);
        break;
    case Qt::Key_D:
        drawer->strafeCamera(0.5);
        break;

    case Qt::Key_I:
        drawer->upDownCamera(0.25);
        break;
    case Qt::Key_J:
        drawer->rotateCamera(-0.05);
        break;
    case Qt::Key_K:
        drawer->upDownCamera(-0.25);
        break;
    case Qt::Key_L:
        drawer->rotateCamera(0.05);
        break;
    }

    drawer->draw();
}



// Add new model
void MainWindow::openAddModelWindow()
{
    addModelWindow = new AddModelWindow(modelCnt);

    connect(addModelWindow, SIGNAL(saveModelParams(AddModelParameters&)),
            this, SLOT(setAddModelParams(AddModelParameters&)));

    addModelWindow->show();
}

void MainWindow::setAddModelParams(AddModelParameters& newParams)
{
    Vector3f center(newParams.moveX, newParams.moveY, newParams.moveZ);
    Vector3f scaleK(newParams.scaleX, newParams.scaleY, newParams.scaleZ);

    if (newParams.isSprite)
    {
        Vector3f end(newParams.enX, newParams.enY, newParams.enZ);
        drawer->addSprite(center, scaleK, newParams.filename, newParams.color, end, newParams.speed);

        centersS.push_back(center);
        ui->comboBox_sprite->addItem(newParams.modelName);

        spriteCnt++;
    }
    else
    {
        drawer->addModel(center, scaleK, newParams.filename, newParams.color);

        centersM.push_back(center);
        ui->comboBox_model->addItem(newParams.modelName);

        modelCnt++;
    }

    frames = 0;
    frameTime = 0;
    drawer->draw();
}


// Add new light
void MainWindow::openAddLightWindow()
{
    addLightWindow = new AddLightWindow(lightCnt);

    connect(addLightWindow, SIGNAL(saveLightParams(AddLightParameters&)),
            this, SLOT(setLightParams(AddLightParameters&)));

    addLightWindow->show();
}

void MainWindow::setLightParams(AddLightParameters& newParams)
{
    Vector3f pos(newParams.x, newParams.y, newParams.z);
    drawer->addLight(pos, newParams.power);

    lightPos.push_back(pos);
    ui->comboBox_light->addItem(newParams.name);

    drawer->draw();
}
