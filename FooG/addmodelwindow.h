#ifndef ADDMODELWINDOW_H
#define ADDMODELWINDOW_H

#include <QDialog>
#include <QFileDialog>
#include <QColorDialog>

struct AddModelParameters
{
    float moveX, moveY, moveZ;
    float scaleX, scaleY, scaleZ;

    QString filename;

    QColor color;
};

namespace Ui {
class AddModelWindow;
}

class AddModelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddModelWindow(QDialog *parent = nullptr);
    ~AddModelWindow();

private:
    Ui::AddModelWindow *ui;
    AddModelParameters params;

private slots:
    void openFileDialog();
    void chooseColor();

    void okButton();
    void cancelButton();

signals:
    void saveModelParams(AddModelParameters&);
};

#endif // ADDMODELWINDOW_H
