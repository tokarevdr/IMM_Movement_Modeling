#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <algorithm>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model.setData(AbstractModuleController::Input::phi, 60 * M_PI / 180.);
    model.setData(AbstractModuleController::Input::lambda, 30 * M_PI / 180.);

    ui->plot->addGraph();

    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);

    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->plot->rescaleAxes();
    ui->plot->replot();

    connect(&model, &AbstractModuleController::dataChanged, this, &MainWindow::on_model_dataChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_x_currentIndexChanged(int index)
{
    ui->plot->graph(0)->setData(model.getDataVector(static_cast<AbstractModuleController::Output>(index)), model.getDataVector(static_cast<AbstractModuleController::Output>(ui->comboBox_y->currentIndex())));

    ui->plot->rescaleAxes();
    ui->plot->replot();
}

void MainWindow::on_comboBox_y_currentIndexChanged(int index)
{
    ui->plot->graph(0)->setData(model.getDataVector(static_cast<AbstractModuleController::Output>(ui->comboBox_x->currentIndex())), model.getDataVector(static_cast<AbstractModuleController::Output>(index)));

    ui->plot->rescaleAxes();
    ui->plot->replot();
}

void MainWindow::on_pushButton_start_clicked()
{
    //model.start();

    QFile file("F:/Учеба/Navigation 2023-10-18 20-17-43/Accelerometer.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    file.readLine(); // скипаем заголовок

    QString line;
    QStringList values;

    QVector<double> n_x;
    QVector<double> n_y;
    QVector<double> n_z;

    while (!file.atEnd()) {
        line = file.readLine();
        values = line.split(',');

        n_x.append(values.at(1).toDouble());
        n_y.append(values.at(2).toDouble());
        n_z.append(values.at(3).toDouble());
    }

    file.close();

    file.setFileName("F:/Учеба/Navigation 2023-10-18 20-17-43/Gyroscope.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    file.readLine(); // скипаем заголовок

    QVector<double> omega_x;
    QVector<double> omega_y;
    QVector<double> omega_z;

    while (!file.atEnd()) {
        line = file.readLine();
        values = line.split(',');

        omega_x.append(values.at(1).toDouble());
        omega_y.append(values.at(2).toDouble());
        omega_z.append(values.at(3).toDouble());
    }

    file.close();

    int samples = std::min<int>({n_x.count(), n_y.count(), n_z.count(),
                                 omega_x.count(), omega_y.count(), omega_z.count()});

    n_x.resize(samples);
    n_y.resize(samples);
    n_z.resize(samples);
    omega_x.resize(samples);
    omega_y.resize(samples);
    omega_z.resize(samples);

    qDebug() << n_x.first() << n_x.last();

    model.setSamplesNumber(samples);
    model.setData(AbstractModuleController::Input::dt, 0.0025);

    model.setInputData(AbstractModuleController::Input::n_x, n_x);
    model.setInputData(AbstractModuleController::Input::n_y, n_y);
    model.setInputData(AbstractModuleController::Input::n_z, n_z);
    model.setInputData(AbstractModuleController::Input::omega_x, omega_x);
    model.setInputData(AbstractModuleController::Input::omega_y, omega_y);
    model.setInputData(AbstractModuleController::Input::omega_z, omega_z);

    //model.handle();
}

void MainWindow::on_pushButton_stop_clicked()
{
    //model.stop();
}

void MainWindow::on_lineEdit_dt_returnPressed()
{
    model.setData(AbstractModuleController::Input::dt, ui->lineEdit_dt->text().toDouble());
}

void MainWindow::on_lineEdit_interval_returnPressed()
{
    //model.setTimerInterval(ui->lineEdit_interval->text().toInt());
}

void MainWindow::on_lineEdit_n_x_returnPressed()
{
    model.setData(AbstractModuleController::Input::n_x, ui->lineEdit_n_x->text().toDouble());
}

void MainWindow::on_lineEdit_n_y_returnPressed()
{
    model.setData(AbstractModuleController::Input::n_y, ui->lineEdit_n_y->text().toDouble());
}

void MainWindow::on_lineEdit_n_z_returnPressed()
{
    model.setData(AbstractModuleController::Input::n_z, ui->lineEdit_n_z->text().toDouble());
}

void MainWindow::on_lineEdit_omega_x_returnPressed()
{
    model.setData(AbstractModuleController::Input::omega_x, ui->lineEdit_omega_x->text().toDouble());
}

void MainWindow::on_lineEdit_omega_y_returnPressed()
{
    model.setData(AbstractModuleController::Input::omega_y, ui->lineEdit_omega_y->text().toDouble());
}

void MainWindow::on_lineEdit_omega_z_returnPressed()
{
    model.setData(AbstractModuleController::Input::omega_z, ui->lineEdit_omega_z->text().toDouble());
}

void MainWindow::on_lineEdit_rho_returnPressed()
{
    model.setData(AbstractModuleController::Input::rho, ui->lineEdit_rho->text().toDouble());
}

void MainWindow::on_model_dataChanged()
{
    ui->label_t->setText(QString::number(model.getData(AbstractModuleController::Output::t)));
    ui->label_K->setText(QString::number(model.getData(AbstractModuleController::Output::K)));
    ui->label_psi->setText(QString::number(model.getData(AbstractModuleController::Output::psi)));
    ui->label_theta->setText(QString::number(model.getData(AbstractModuleController::Output::theta)));
    ui->label_K_dot->setText(QString::number(model.getData(AbstractModuleController::Output::K_dot)));
    ui->label_psi_dot->setText(QString::number(model.getData(AbstractModuleController::Output::psi_dot)));
    ui->label_theta_dot->setText(QString::number(model.getData(AbstractModuleController::Output::theta_dot)));
    ui->label_V_E->setText(QString::number(model.getData(AbstractModuleController::Output::V_E)));
    ui->label_V_N->setText(QString::number(model.getData(AbstractModuleController::Output::V_N)));
    ui->label_V_h->setText(QString::number(model.getData(AbstractModuleController::Output::V_h)));
    ui->label_V_E_dot->setText(QString::number(model.getData(AbstractModuleController::Output::V_E_dot)));
    ui->label_V_N_dot->setText(QString::number(model.getData(AbstractModuleController::Output::V_N_dot)));
    ui->label_V_h_dot->setText(QString::number(model.getData(AbstractModuleController::Output::V_h_dot)));
    ui->label_phi->setText(QString::number(model.getData(AbstractModuleController::Output::phi)));
    ui->label_lambda->setText(QString::number(model.getData(AbstractModuleController::Output::lambda)));
    ui->label_h->setText(QString::number(model.getData(AbstractModuleController::Output::h)));

    ui->plot->graph(0)->addData(model.getData(static_cast<AbstractModuleController::Output>(ui->comboBox_x->currentIndex())),
                                model.getData(static_cast<AbstractModuleController::Output>(ui->comboBox_y->currentIndex())));
    ui->plot->rescaleAxes();
    ui->plot->replot();
}
