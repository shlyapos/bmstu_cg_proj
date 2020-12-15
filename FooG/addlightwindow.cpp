#include "addlightwindow.h"
#include "ui_addlightwindow.h"

AddLightWindow::AddLightWindow(QWidget *parent) :
    QDialog(parent), ui(new Ui::AddLightWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Add new Light");

    ui->label_0->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_1->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_2->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_3->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_4->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");
    ui->label_5->setStyleSheet("QLabel {color: rgba(200, 200, 200, 255);}");

    connect(ui->pushButton_ok, SIGNAL(released()), this, SLOT(okButton()));
    connect(ui->pushButton_cancel, SIGNAL(released()), this, SLOT(cancelButton()));
}

AddLightWindow::~AddLightWindow()
{
    delete ui;
}


void AddLightWindow::okButton()
{
    params.name = ui->le_name->text();

    params.x = ui->le_x->text().toFloat();
    params.y = ui->le_y->text().toFloat();
    params.z = ui->le_z->text().toFloat();

    params.power = ui->le_power->text().toFloat();

    emit saveLightParams(params);

    this->destroy();
}

void AddLightWindow::cancelButton()
{
    this->destroy();
}
