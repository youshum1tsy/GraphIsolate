#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graph.h"

#include <QMainWindow>
#include <QGraphicsScene>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_sidebar_toggled(bool checked);

    void on_pushButton_create_graph_clicked();
    void on_pushButton_create_graph_icon_clicked();

    void on_pushButton_clear_all_clicked();

    void on_pushButton_save_graph_clicked();
    void on_pushButton_save_icon_clicked();

    void on_pushButton_upload_graph_clicked();
    void on_pushButton_upload_graph_icon_clicked();

    void on_pushButton_mis_clicked();

    void on_listEdgesSet_itemClicked(QListWidgetItem *item);

    void on_pushButton_quit_clicked();
    void on_pushButton_quit_icon_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    Graph graph;

    void createAndDrawGraph();

    void saveGraph();
    void uploadGraph();

    QString getJsonFileName(const QString name);
    QString getJsonFilePath();
};
#endif // MAINWINDOW_H
