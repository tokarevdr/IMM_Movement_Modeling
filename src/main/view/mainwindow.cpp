#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "model/inertialmodule.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InertialModule module;

    module.set_V_x(1.);
    module.set_V_y(1.);
    //module.set_W_x(0.1);
    module.set_W_y(0.01);
    //module.set_omega_circulation(0.05 * M_PI / 180.);
    module.set_phi(60 * M_PI / 180.);
    module.set_lambda(30 * M_PI / 180.);

    module.handle();

    ui->plot->addGraph();

    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);

    ui->plot->graph(0)->setData(module.getParameter(InertialModule::Parameter::lambda), module.getParameter(InertialModule::Parameter::phi));

    ui->plot->rescaleAxes();
}

MainWindow::~MainWindow()
{
    delete ui;
}
