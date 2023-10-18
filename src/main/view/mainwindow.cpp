#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //module.set_n_x(0.01);
    //module.set_n_y(0.01);
    //module.set_omega_x(0.1);
    //module.set_omega_y(0.1);

    module.set_phi(60 * M_PI / 180.);
    module.set_lambda(30 * M_PI / 180.);

    for (size_t i = 0; i < 100000; ++i)
    {
        module.handle();
    }

    ui->plot->addGraph();

    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);

    ui->plot->graph(0)->setData(module.getParameter(InertialModule::Parameter::t), module.getParameter(InertialModule::Parameter::K));

    ui->plot->rescaleAxes();
    ui->plot->replot();
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
