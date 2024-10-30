#include "dialoggraphsetting.h"
#include "ui_dialoggraphsetting.h"

DialogGraphSetting::DialogGraphSetting(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogGraphSetting)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider_vertex,&QSlider::valueChanged,ui->spinBox_vertex,&QSpinBox::setValue);
    connect(ui->spinBox_vertex,&QSpinBox::valueChanged,ui->horizontalSlider_vertex,&QSlider::setValue);
    connect(ui->horizontalSlider_edge,&QSlider::valueChanged,ui->spinBox_edge,&QSpinBox::setValue);
    connect(ui->spinBox_edge,&QSpinBox::valueChanged,ui->horizontalSlider_edge,&QSlider::setValue);

}

DialogGraphSetting::~DialogGraphSetting()
{
    delete ui;
}

void DialogGraphSetting::on_pushButton_accept_clicked()
{
    accept();
}


void DialogGraphSetting::on_pushButton_cancel_clicked()
{
    reject();
}

int DialogGraphSetting::getSliderVertexValue()
{
    return ui->horizontalSlider_vertex->value();
}

int DialogGraphSetting::getSliderEdgeValue()
{
    return ui->horizontalSlider_edge->value();
}

