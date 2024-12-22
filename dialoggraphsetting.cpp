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

    connect(ui->horizontalSlider_vertex, &QSlider::valueChanged, this, &DialogGraphSetting::setSliderMaxValue);
}

DialogGraphSetting::~DialogGraphSetting()
{
    delete ui;
}

int DialogGraphSetting::getSliderVertexValue()
{
    return ui->horizontalSlider_vertex->value();
}

int DialogGraphSetting::getSliderEdgeValue()
{
    return ui->horizontalSlider_edge->value();
}

void DialogGraphSetting::setSliderMaxValue(int value)
{
    int newMax = value * (value - 1) / 2;

    ui->horizontalSlider_edge->setRange(1, newMax);
    ui->spinBox_edge->setRange(1, newMax);
}

void DialogGraphSetting::on_pushButton_accept_clicked()
{
    accept();
}

void DialogGraphSetting::on_pushButton_cancel_clicked()
{
    reject();
}

