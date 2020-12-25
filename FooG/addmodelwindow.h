#ifndef ADDMODELWINDOW_H
#define ADDMODELWINDOW_H

#include <QDialog>
#include <QFileDialog>
#include <QColorDialog>

#include <cstdlib>

struct AddModelParameters
{
    float moveX, moveY, moveZ;
    float scaleX, scaleY, scaleZ;

    QString filename;
    QString modelName;

    QColor color;

    bool isSprite;

    float enX, enY, enZ;
    float speed;
};

namespace Ui {
class AddModelWindow;
}

class AddModelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddModelWindow(int, QDialog *parent = nullptr);
    ~AddModelWindow();

private:
    Ui::AddModelWindow *ui;
    AddModelParameters params;

    // For auto name
    int modelCnt;
    std::string name;

    void initLabels();
    void initLineEdits();
    void initParams();

private slots:
    void isSpriteToggledCheckButton(bool);

    void openFileDialog();
    void chooseColor();

    void okButton();
    void cancelButton();

signals:
    void saveModelParams(AddModelParameters&);
};

#endif // ADDMODELWINDOW_H
