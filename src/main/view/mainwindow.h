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

private:
    Ui::MainWindow *ui;
    InertialModule module;
};

#endif // MAINWINDOW_H
