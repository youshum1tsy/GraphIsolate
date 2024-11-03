#ifndef DIALOGUPLOADMATRIX_H
#define DIALOGUPLOADMATRIX_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class DialogUploadMatrix;
}

class DialogUploadMatrix : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUploadMatrix(QWidget *parent = nullptr);
    ~DialogUploadMatrix();

    bool getRadioButtonAdjacencyStatus();
    bool getRadioButtonIncidenceStatus();

private slots:

    void on_pushButton_cancel_clicked();
    void on_pushButton_next_clicked();

private:
    Ui::DialogUploadMatrix *ui;
};

#endif // DIALOGUPLOADMATRIX_H
