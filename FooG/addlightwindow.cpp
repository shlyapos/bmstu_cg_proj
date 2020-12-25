#include "addlightwindow.h"
#include "ui_addlightwindow.h"

AddLightWindow::AddLightWindow(int lightCnt, QWidget *parent) :
    QDialog(parent), ui(new Ui::AddLightWindow), lightCnt(lightCnt)
{
    ui->setupUi(this);

    this->setWindowTitle("Add new Light");

    ui->label_1->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_2->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_3->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_4->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_5->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_6->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");

    name = "light_" + std::to_string(lightCnt);
    ui->le_name->setText(name.c_str());

    ui->le_x->setText("0");
    ui->le_y->setText("0");
    ui->le_z->setText("0");

    ui->le_power->setText("100");

    connect(ui->pushButton_ok, SIGNAL(released()), this, SLOT(okButton()));
    connect(ui->pushButton_cancel, SIGNAL(released()), this, SLOT(cancelButton()));
}

AddLightWindow::~AddLightWindow()
{
    delete ui;
}


void AddLightWindow::okButton()
{
    params.x = ui->le_x->text().toFloat();
    params.y = ui->le_y->text().toFloat();
    params.z = ui->le_z->text().toFloat();

    params.power = ui->le_power->text().toFloat();
    params.name = ui->le_name->text();

    if (params.name.size() == 0)
        params.name = QString(name.c_str());

    emit saveLightParams(params);

    this->destroy();
}

void AddLightWindow::cancelButton()
{
    this->destroy();
}
