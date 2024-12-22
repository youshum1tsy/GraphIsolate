#include "dialoguploadmatrix.h"
#include "ui_dialoguploadmatrix.h"

DialogUploadMatrix::DialogUploadMatrix(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogUploadMatrix)
{
    ui->setupUi(this);
}

DialogUploadMatrix::~DialogUploadMatrix()
{
    delete ui;
}

bool DialogUploadMatrix::getRadioButtonAdjacencyStatus()
{
    return ui->radioButton_Adjacency->isChecked();
}

bool DialogUploadMatrix::getRadioButtonIncidenceStatus()
{
    return ui->radioButton_Incidence->isChecked();
}

void DialogUploadMatrix::on_pushButton_cancel_clicked()
{
    reject();
}

void DialogUploadMatrix::on_pushButton_next_clicked()
{
    accept();
}

