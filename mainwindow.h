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

private:
    QGraphicsScene *scene;
    Graph graph;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
