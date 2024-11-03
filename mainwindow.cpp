#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialoggraphsetting.h"
#include "dialogsavematrix.h"
#include "dialoguploadmatrix.h"

#include <QDebug>
#include <QFileDialog>

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

    DialogGraphSetting dialogSetting;
    if (dialogSetting.exec() == QDialog::Accepted) {
        int sliderVertexValue = dialogSetting.getSliderVertexValue();
        int sliderEdgeValue = dialogSetting.getSliderEdgeValue();
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


void MainWindow::on_pushButton_save_graph_clicked()
{
    DialogSaveMatrix saveDialog;

    if (saveDialog.exec() == QDialog::Accepted) {

        if (saveDialog.getCheckBoxAdjacencyStatus() && saveDialog.getCheckBoxIncidenceStatus()) {
            QString fileName = getJsonFileName("Adjacency");
            graph.saveAdjacencyMatrixToJson(fileName);

            fileName = getJsonFileName("Incidence");
            graph.saveIncidenceMatrixToJson(fileName);
        }
        else if (saveDialog.getCheckBoxAdjacencyStatus()) {
            QString fileName = getJsonFileName("Adjacency");
            graph.saveAdjacencyMatrixToJson(fileName);
        }
        else if (saveDialog.getCheckBoxIncidenceStatus()) {
            QString fileName = getJsonFileName("Incidence");
            graph.saveIncidenceMatrixToJson(fileName);
        }
    }
}

QString MainWindow::getJsonFileName(const QString name)
{
    QString projectPath = QCoreApplication::applicationDirPath();
    projectPath = QDir(projectPath).absolutePath() + "/../../";

    QString fileName = QFileDialog::getSaveFileName(this, "Save JSON File", projectPath + "/" + name + ".json", tr("JSON Files (*.json)"));
    if (!fileName.endsWith(".json") && !fileName.isEmpty()) {
        fileName += ".json";
    }
    return fileName;
}

QString MainWindow::getJsonFilePath()
{
    QString projectPath = QCoreApplication::applicationDirPath();
    projectPath = QDir(projectPath).absolutePath() + "/../../";

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open JSON file",
                                                    projectPath,
                                                    tr("JSON Files (*.json);;All Files (*)"));
    return fileName;
}


void MainWindow::on_pushButton_upload_graph_clicked()
{
    DialogUploadMatrix uploadDialog;

    if (uploadDialog.exec() == QDialog::Accepted) {
        if (uploadDialog.getRadioButtonAdjacencyStatus()) {
            QString filePath = getJsonFilePath();
            graph.uploadJsonToAdjacencyMatrix(filePath);
            scene->clear();
            graph.createIncidenceGraph();
            graph.createVerteciesArray();
            graph.createEdgesArray();
            graph.drawGraph(scene);
        }
        else if (uploadDialog.getRadioButtonIncidenceStatus()) {
            QString filePath = getJsonFilePath();
            graph.uploadJsonToIncidenceMatrix(filePath);
            scene->clear();
            graph.createVerteciesArray();
            graph.createEdgesArray();
            graph.drawGraph(scene);
        }
    }
}

