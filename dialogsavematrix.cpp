#include "dialogsavematrix.h"
#include "ui_dialogsavematrix.h"

DialogSaveMatrix::DialogSaveMatrix(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogSaveMatrix)
{
    ui->setupUi(this);
}

DialogSaveMatrix::~DialogSaveMatrix()
{
    delete ui;
}

bool DialogSaveMatrix::getCheckBoxAdjacencyStatus()
{
    return ui->checkBox_Adjacency->checkState();
}

bool DialogSaveMatrix::getCheckBoxIncidenceStatus()
{
    return ui->checkBox_Incidence->checkState();
}

void DialogSaveMatrix::on_pushButton_next_clicked()
{
    accept();
}

void DialogSaveMatrix::on_pushButton_cancel_clicked()
{
    reject();
}


