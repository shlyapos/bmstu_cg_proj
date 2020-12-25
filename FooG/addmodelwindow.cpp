#include "addmodelwindow.h"
#include "ui_addmodelwindow.h"

AddModelWindow::AddModelWindow(int modelCnt, QDialog *parent)
    : QDialog(parent), ui(new Ui::AddModelWindow), modelCnt(modelCnt)
{
    ui->setupUi(this);
    this->setWindowTitle("Add new Model");

    initParams();
    initLabels();
    initLineEdits();

    connect(ui->checkBox_isSprite, SIGNAL(toggled(bool)), this, SLOT(isSpriteToggledCheckButton(bool)));

    connect(ui->pushButton_file, SIGNAL(released()), this, SLOT(openFileDialog()));
    connect(ui->pushButton_color, SIGNAL(released()), this, SLOT(chooseColor()));

    connect(ui->pushButton_ok, SIGNAL(released()), this, SLOT(okButton()));
    connect(ui->pushButton_cancel, SIGNAL(released()), this, SLOT(cancelButton()));
}

AddModelWindow::~AddModelWindow()
{
    delete ui;
}


void AddModelWindow::initLabels()
{
    ui->label_0->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_1->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_2->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_3->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_4->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_5->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_6->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_7->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_8->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_9->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_10->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");

    ui->label->setPalette(QPalette(Qt::white));
    ui->label->setAutoFillBackground(true);

    ui->label_en->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_en_x->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_en_y->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_en_z->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");

    ui->label_sp->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
}

void AddModelWindow::initLineEdits()
{
    ui->le_moveX->setText("0");
    ui->le_moveY->setText("0");
    ui->le_moveZ->setText("0");

    ui->le_scaleX->setText("1");
    ui->le_scaleY->setText("1");
    ui->le_scaleZ->setText("1");

    name = "model_" + std::to_string(modelCnt);
    ui->le_name->setText(name.c_str());

    ui->le_en_x->setText("0");
    ui->le_en_y->setText("0");
    ui->le_en_z->setText("0");

    ui->le_speed->setText("0");
}

void AddModelWindow::initParams()
{
    params.color = Qt::white;
    params.isSprite = false;
}



void AddModelWindow::isSpriteToggledCheckButton(bool value)
{
    if (value)
    {
        params.isSprite = true;
        this->resize(479, 289);
    }
    else
    {
        params.isSprite = false;
        this->resize(328, 289);
    }
}



void AddModelWindow::openFileDialog()
{
    QString filename = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.obj");

    ui->le_file->setText(filename);

    this->params.filename = filename;
}

void AddModelWindow::chooseColor()
{
    QColor initialColor = ui->label->palette().color(QPalette::Background);
    QColor colorSelected = QColorDialog::getColor(initialColor);

    if (colorSelected.isValid())
    {
        ui->label->setPalette(QPalette(colorSelected));
        ui->label->setAutoFillBackground(true);

        this->params.color = colorSelected;
    }
}

void AddModelWindow::okButton()
{
    this->params.modelName = ui->le_name->text();

    this->params.moveX = ui->le_moveX->text().toFloat();
    this->params.moveY = ui->le_moveY->text().toFloat();
    this->params.moveZ = ui->le_moveZ->text().toFloat();

    this->params.scaleX = ui->le_scaleX->text().toFloat();
    this->params.scaleY = -ui->le_scaleY->text().toFloat();
    this->params.scaleZ = ui->le_scaleZ->text().toFloat();

    if (params.isSprite)
    {
        params.enX = ui->le_en_x->text().toFloat();
        params.enY = ui->le_en_y->text().toFloat();
        params.enZ = ui->le_en_z->text().toFloat();

        params.speed = ui->le_speed->text().toFloat();
    }

    emit saveModelParams(params);

    this->destroy();
}

void AddModelWindow::cancelButton()
{
    this->destroy();
}
