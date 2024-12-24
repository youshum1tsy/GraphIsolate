#ifndef DIALOGSAVEMATRIX_H
#define DIALOGSAVEMATRIX_H

#include <QDialog>

namespace Ui {
class DialogSaveMatrix;
}

class DialogSaveMatrix : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSaveMatrix(QWidget *parent = nullptr);
    ~DialogSaveMatrix();

    bool getCheckBoxAdjacencyStatus();
    bool getCheckBoxIncidenceStatus();

private slots:
    void on_pushButton_next_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::DialogSaveMatrix *ui;
};

#endif // DIALOGSAVEMATRIX_H
