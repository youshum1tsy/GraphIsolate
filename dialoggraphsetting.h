#ifndef DIALOGGRAPHSETTING_H
#define DIALOGGRAPHSETTING_H

#include <QDialog>

namespace Ui {
class DialogGraphSetting;
}

class DialogGraphSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGraphSetting(QWidget *parent = nullptr);
    ~DialogGraphSetting();

    int getSliderVertexValue();
    int getSliderEdgeValue();

private slots:

    void on_pushButton_accept_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::DialogGraphSetting *ui;
};

#endif // DIALOGGRAPHSETTING_H
