#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //module.set_n_x(1);
    //module.set_n_y(0.01);
    //module.set_omega_x(0.1);
    //module.set_omega_y(0.1);

    module.set_phi(60 * M_PI / 180.);
    module.set_lambda(30 * M_PI / 180.);

    ui->plot->addGraph();

    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);

    ui->plot->graph(0)->setData(module.getParameter(InertialModule::Parameter::t), module.getParameter(InertialModule::Parameter::K));

    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->plot->rescaleAxes();
    ui->plot->replot();

    connect(&module, &InertialModule::dataChanged, this, &MainWindow::onModule_dataChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_x_currentIndexChanged(int index)
{
    ui->plot->graph(0)->setData(module.getParameter(static_cast<InertialModule::Parameter>(index)), module.getParameter(static_cast<InertialModule::Parameter>(ui->comboBox_y->currentIndex())));

    ui->plot->rescaleAxes();
    ui->plot->replot();
}

void MainWindow::on_comboBox_y_currentIndexChanged(int index)
{
    ui->plot->graph(0)->setData(module.getParameter(static_cast<InertialModule::Parameter>(ui->comboBox_x->currentIndex())), module.getParameter(static_cast<InertialModule::Parameter>(index)));

    ui->plot->rescaleAxes();
    ui->plot->replot();
}

void MainWindow::on_pushButton_start_clicked()
{
    module.start();
}

void MainWindow::on_pushButton_stop_clicked()
{
    module.stop();
}

void MainWindow::on_lineEdit_dt_returnPressed()
{
    module.set_dt(ui->lineEdit_dt->text().toDouble());
}

void MainWindow::on_lineEdit_interval_returnPressed()
{
    module.setTimerInterval(ui->lineEdit_interval->text().toInt());
}

void MainWindow::on_lineEdit_n_x_returnPressed()
{
    module.set_n_x(ui->lineEdit_n_x->text().toDouble());
}

void MainWindow::on_lineEdit_n_y_returnPressed()
{
    module.set_n_y(ui->lineEdit_n_y->text().toDouble());
}

void MainWindow::on_lineEdit_n_z_returnPressed()
{
    module.set_n_z(ui->lineEdit_n_z->text().toDouble());
}

void MainWindow::on_lineEdit_omega_x_returnPressed()
{
    module.set_omega_x(ui->lineEdit_omega_x->text().toDouble());
}

void MainWindow::on_lineEdit_omega_y_returnPressed()
{
    module.set_omega_y(ui->lineEdit_omega_y->text().toDouble());
}

void MainWindow::on_lineEdit_omega_z_returnPressed()
{
    module.set_omega_z(ui->lineEdit_omega_z->text().toDouble());
}

void MainWindow::on_lineEdit_rho_returnPressed()
{
    module.set_rho(ui->lineEdit_rho->text().toDouble());
}

void MainWindow::onModule_dataChanged(QMap<InertialModule::Parameter, double> currentData)
{
    ui->plot->graph(0)->addData(currentData.value(static_cast<InertialModule::Parameter>(ui->comboBox_x->currentIndex())),
                                currentData.value(static_cast<InertialModule::Parameter>(ui->comboBox_y->currentIndex())));
    ui->plot->rescaleAxes();
    ui->plot->replot();
}
