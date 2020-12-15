#ifndef ADDLIGHTWINDOW_H
#define ADDLIGHTWINDOW_H

#include <QDialog>

struct AddLightParameters
{
    float x, y, z;
    float power;

    QString name;
};

namespace Ui {
class AddLightWindow;
}

class AddLightWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddLightWindow(QWidget *parent = nullptr);
    ~AddLightWindow();

private:
    Ui::AddLightWindow *ui;
    AddLightParameters params;

private slots:
    void okButton();
    void cancelButton();

signals:
    void saveLightParams(AddLightParameters&);
};

#endif // ADDLIGHTWINDOW_H
