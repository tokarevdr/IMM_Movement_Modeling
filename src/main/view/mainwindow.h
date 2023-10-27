#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "model/abstractmodulecontroller.h"
#include "qcpaxistickerangle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBox_x_currentIndexChanged(int index);

    void on_comboBox_y_currentIndexChanged(int index);

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void on_lineEdit_dt_returnPressed();

    void on_lineEdit_interval_returnPressed();

    void on_lineEdit_n_x_returnPressed();

    void on_lineEdit_n_y_returnPressed();

    void on_lineEdit_n_z_returnPressed();

    void on_lineEdit_omega_x_returnPressed();

    void on_lineEdit_omega_y_returnPressed();

    void on_lineEdit_omega_z_returnPressed();

    void on_lineEdit_rho_returnPressed();

    void on_model_dataChanged();

    void on_lineEdit_filepath_textChanged(const QString &arg1);

    void on_tabWidget_currentChanged(int index);

    void on_lineEdit_dt_2_returnPressed();

    void on_pushButton_search_clicked();

    void on_pushButton_reset_clicked();

    void on_lineEdit_iterations_returnPressed();

    void on_checkBox_angular_x_clicked(bool checked);

    void on_checkBox_angular_y_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    AbstractModuleController *model;
    QSharedPointer<QCPAxisTickerAngle> angularTicker;
    QSharedPointer<QCPAxisTicker> ticker;
};

#endif // MAINWINDOW_H
