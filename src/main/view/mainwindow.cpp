#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "model/inertialmodule.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InertialModule module;

    module.handle();

    ui->plot->addGraph();

    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);

    ui->plot->graph(0)->setData(module.time, module.data2);

    ui->plot->rescaleAxes();
}

MainWindow::~MainWindow()
{
    delete ui;
}
