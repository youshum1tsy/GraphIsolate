#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->icon_name_widget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_sidebar_toggled(bool checked)
{
    if (checked) {
        ui->icon_only_widget->hide();
        ui->icon_name_widget->show();
    }
    else {
        ui->icon_name_widget->hide();
        ui->icon_only_widget->show();
    }
}




