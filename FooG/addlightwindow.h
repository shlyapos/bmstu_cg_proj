#ifndef SETLIGHTWINDOW_H
#define SETLIGHTWINDOW_H

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
    explicit AddLightWindow(int, QWidget *parent = nullptr);
    ~AddLightWindow();

private:
    Ui::AddLightWindow *ui;
    AddLightParameters params;

    int lightCnt;
    std::string name;

private slots:
    void okButton();
    void cancelButton();

signals:
    void saveLightParams(AddLightParameters&);
};

#endif // ADDLIGHTWINDOW_H
