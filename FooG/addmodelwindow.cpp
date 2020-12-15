#include "addmodelwindow.h"
#include "ui_addmodelwindow.h"

AddModelWindow::AddModelWindow(QDialog *parent) : QDialog(parent), ui(new Ui::AddModelWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Add new Model");

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


    ui->label->setStyleSheet("{background-color: rgba(255, 255, 255, 255);}");

    connect(ui->pushButton_file, SIGNAL(released()), this, SLOT(openFileDialog()));
    connect(ui->pushButton_color, SIGNAL(released()), this, SLOT(chooseColor()));

    connect(ui->pushButton_ok, SIGNAL(released()), this, SLOT(okButton()));
    connect(ui->pushButton_cancel, SIGNAL(released()), this, SLOT(cancelButton()));
}

AddModelWindow::~AddModelWindow()
{
    delete ui;
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
    this->params.moveX = ui->le_moveX->text().toFloat();
    this->params.moveY = ui->le_moveY->text().toFloat();
    this->params.moveZ = ui->le_moveZ->text().toFloat();

    this->params.scaleX = ui->le_scaleX->text().toFloat();
    this->params.scaleY = ui->le_scaleY->text().toFloat();
    this->params.scaleZ = ui->le_scaleZ->text().toFloat();

    emit saveModelParams(params);

    this->destroy();
}

void AddModelWindow::cancelButton()
{
    this->destroy();
}
