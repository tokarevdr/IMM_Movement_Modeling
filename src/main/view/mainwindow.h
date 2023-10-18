#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "model/inertialmodule.h"

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

    void onModule_dataChanged(QMap<InertialModule::Parameter, double> currentData);

private:
    Ui::MainWindow *ui;
    InertialModule module;
};

#endif // MAINWINDOW_H
