#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QImage>
#include <QPixmap>
#include <QKeyEvent>

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

    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
