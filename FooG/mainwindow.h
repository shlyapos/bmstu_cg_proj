#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QImage>
#include <QPixmap>
#include <QKeyEvent>

#include "addmodelwindow.h"
#include "addlightwindow.h"

#include "MathObjects/vector3.h"
#include "drawer.h"

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
    Drawer *drawer;

    void initDrawer();
    void initButton();

    void keyPressEvent(QKeyEvent *event);

    AddModelWindow *addModelWindow;
    AddModelParameters addModelparams;

    AddLightWindow *addLightWindow;
    AddLightParameters addLightParams;

private slots:
    void openAddModelWindow();
    void setAddModelParams(AddModelParameters&);

    void openAddLightWindow();
    void setAddLightParams(AddLightParameters&);
};
#endif // MAINWINDOW_H
