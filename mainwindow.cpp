#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialoggraphsetting.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->icon_name_widget->hide();
    ui->pushButton_sidebar->setIcon(QIcon(":/icons/assets/icons/show.png"));

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 10000, 10000);

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::on_pushButton_sidebar_toggled(bool checked)
{
    if (checked) {
        ui->icon_only_widget->hide();
        ui->icon_name_widget->show();
        ui->pushButton_sidebar->setIcon(QIcon(":/icons/assets/icons/hide.png"));
    }
    else {
        ui->icon_name_widget->hide();
        ui->icon_only_widget->show();
        ui->pushButton_sidebar->setIcon(QIcon(":/icons/assets/icons/show.png"));
    }
}

void MainWindow::on_pushButton_create_graph_clicked()
{
    scene->clear();
    graph.deleteAdjacencyGraph();
    graph.deleteIncidenceGraph();
    graph.deleteVerteciesArray();
    graph.deleteEdgesArray();

    DialogGraphSetting setting;
    if (setting.exec() == QDialog::Accepted) {
        int sliderVertexValue = setting.getSliderVertexValue();
        int sliderEdgeValue = setting.getSliderEdgeValue();
        graph.setVertex(sliderVertexValue);
        graph.setEdges(sliderEdgeValue);
    }
    graph.createAdjacencyGraph();
    graph.createIncidenceGraph();
    graph.createVerteciesArray();
    graph.createEdgesArray();
    graph.drawGraph(scene);

}


void MainWindow::on_pushButton_create_graph_icon_clicked()
{
    scene->clear();
    graph.deleteAdjacencyGraph();
    graph.deleteIncidenceGraph();
    graph.deleteVerteciesArray();
    graph.deleteEdgesArray();

    DialogGraphSetting setting;
    if (setting.exec() == QDialog::Accepted) {
        int sliderVertexValue = setting.getSliderVertexValue();
        int sliderEdgeValue = setting.getSliderEdgeValue();
        graph.setVertex(sliderVertexValue);
        graph.setEdges(sliderEdgeValue);
    }
    graph.createAdjacencyGraph();
    graph.createIncidenceGraph();
    graph.createVerteciesArray();
    graph.createEdgesArray();
    graph.drawGraph(scene);
}


void MainWindow::on_pushButton_clear_all_clicked()
{
    scene->clear();
    graph.deleteAdjacencyGraph();
    graph.deleteIncidenceGraph();
    graph.deleteVerteciesArray();
    graph.deleteEdgesArray();
}

