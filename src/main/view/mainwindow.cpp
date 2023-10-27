#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "model/datamodulecontroller.h"
#include "model/timermodulecontroller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //model->setData(AbstractModuleController::Input::phi, 60 * M_PI / 180.);
    //model->setData(AbstractModuleController::Input::lambda, 30 * M_PI / 180.);

    ui->tabWidget->setCurrentIndex(0);

    model = new TimerModuleController();

    ui->plot->addGraph();

    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);

    //ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    //ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->plot->rescaleAxes();
    ui->plot->replot();

    angularTicker = QSharedPointer<QCPAxisTickerAngle>(new QCPAxisTickerAngle);
    ticker = QSharedPointer<QCPAxisTicker>(new QCPAxisTicker);

    connect(model, &AbstractModuleController::dataChanged, this, &MainWindow::on_model_dataChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::on_comboBox_x_currentIndexChanged(int index)
{
    ui->plot->graph(0)->setData(model->getDataVector(static_cast<AbstractModuleController::Output>(index)), model->getDataVector(static_cast<AbstractModuleController::Output>(ui->comboBox_y->currentIndex())));

    ui->plot->rescaleAxes();
    ui->plot->replot();
}

void MainWindow::on_comboBox_y_currentIndexChanged(int index)
{
    ui->plot->graph(0)->setData(model->getDataVector(static_cast<AbstractModuleController::Output>(ui->comboBox_x->currentIndex())), model->getDataVector(static_cast<AbstractModuleController::Output>(index)));

    ui->plot->rescaleAxes();
    ui->plot->replot();
}

void MainWindow::on_pushButton_start_clicked()
{
    model->start();
}

void MainWindow::on_pushButton_stop_clicked()
{
    model->stop();
}

void MainWindow::on_lineEdit_dt_returnPressed()
{
    model->setData(AbstractModuleController::Input::dt, ui->lineEdit_dt->text().toDouble());
}

void MainWindow::on_lineEdit_interval_returnPressed()
{
    model->setTimerInterval(ui->lineEdit_interval->text().toInt());
}

void MainWindow::on_lineEdit_n_x_returnPressed()
{
    model->setData(AbstractModuleController::Input::n_x, ui->lineEdit_n_x->text().toDouble());
}

void MainWindow::on_lineEdit_n_y_returnPressed()
{
    model->setData(AbstractModuleController::Input::n_y, ui->lineEdit_n_y->text().toDouble());
}

void MainWindow::on_lineEdit_n_z_returnPressed()
{
    model->setData(AbstractModuleController::Input::n_z, ui->lineEdit_n_z->text().toDouble());
}

void MainWindow::on_lineEdit_omega_x_returnPressed()
{
    model->setData(AbstractModuleController::Input::omega_x, ui->lineEdit_omega_x->text().toDouble());
}

void MainWindow::on_lineEdit_omega_y_returnPressed()
{
    model->setData(AbstractModuleController::Input::omega_y, ui->lineEdit_omega_y->text().toDouble());
}

void MainWindow::on_lineEdit_omega_z_returnPressed()
{
    model->setData(AbstractModuleController::Input::omega_z, ui->lineEdit_omega_z->text().toDouble());
}

void MainWindow::on_lineEdit_rho_returnPressed()
{
    model->setData(AbstractModuleController::Input::rho, ui->lineEdit_rho->text().toDouble());
}

void MainWindow::on_model_dataChanged()
{
    ui->label_t->setText(QString::number(model->getData(AbstractModuleController::Output::t)));
    ui->label_K->setText(QString::number(model->getData(AbstractModuleController::Output::K)));
    ui->label_psi->setText(QString::number(model->getData(AbstractModuleController::Output::psi)));
    ui->label_theta->setText(QString::number(model->getData(AbstractModuleController::Output::theta)));
    ui->label_K_dot->setText(QString::number(model->getData(AbstractModuleController::Output::K_dot)));
    ui->label_psi_dot->setText(QString::number(model->getData(AbstractModuleController::Output::psi_dot)));
    ui->label_theta_dot->setText(QString::number(model->getData(AbstractModuleController::Output::theta_dot)));
    ui->label_V_E->setText(QString::number(model->getData(AbstractModuleController::Output::V_E)));
    ui->label_V_N->setText(QString::number(model->getData(AbstractModuleController::Output::V_N)));
    ui->label_V_h->setText(QString::number(model->getData(AbstractModuleController::Output::V_h)));
    ui->label_V_E_dot->setText(QString::number(model->getData(AbstractModuleController::Output::V_E_dot)));
    ui->label_V_N_dot->setText(QString::number(model->getData(AbstractModuleController::Output::V_N_dot)));
    ui->label_V_h_dot->setText(QString::number(model->getData(AbstractModuleController::Output::V_h_dot)));
    ui->label_phi->setText(QString::number(model->getData(AbstractModuleController::Output::phi)));
    ui->label_lambda->setText(QString::number(model->getData(AbstractModuleController::Output::lambda)));
    ui->label_h->setText(QString::number(model->getData(AbstractModuleController::Output::h)));

    ui->plot->graph(0)->addData(model->getData(static_cast<AbstractModuleController::Output>(ui->comboBox_x->currentIndex())),
                                model->getData(static_cast<AbstractModuleController::Output>(ui->comboBox_y->currentIndex())));
    ui->plot->rescaleAxes();
    ui->plot->replot();
}

void MainWindow::on_lineEdit_filepath_textChanged(const QString &arg1)
{
    model->setSensorsDataFilePath(arg1);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    disconnect(model, &AbstractModuleController::dataChanged, this, &MainWindow::on_model_dataChanged);

    switch (index)
    {
    case 0:
        model = new TimerModuleController();
        break;
    case 1:
        model = new DataModuleController();
        break;
    default:
        return;
    }

    on_model_dataChanged();

    ui->plot->graph(0)->setData(QVector<double>(), QVector<double>());

    connect(model, &AbstractModuleController::dataChanged, this, &MainWindow::on_model_dataChanged);
}

void MainWindow::on_lineEdit_dt_2_returnPressed()
{
    model->setData(AbstractModuleController::Input::dt, ui->lineEdit_dt->text().toDouble());
}

void MainWindow::on_pushButton_search_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open sensors data file"), "", tr("*.csv"));

    ui->lineEdit_filepath->setText(fileName);
}

void MainWindow::on_pushButton_reset_clicked()
{
    model->reset();

    ui->plot->graph(0)->setData(QVector<double>(), QVector<double>());
}

void MainWindow::on_lineEdit_iterations_returnPressed()
{
    model->setIterationCount(ui->lineEdit_iterations->text().toInt());
}

void MainWindow::on_checkBox_angular_x_clicked(bool checked)
{
    switch (checked)
    {
    case true:
        ui->plot->xAxis->setTicker(angularTicker);
        break;
    case false:
        ui->plot->xAxis->setTicker(ticker);
        break;
    }

    ui->plot->replot();
}

void MainWindow::on_checkBox_angular_y_clicked(bool checked)
{
    switch (checked)
    {
    case true:
        ui->plot->yAxis->setTicker(angularTicker);
        break;
    case false:
        ui->plot->yAxis->setTicker(ticker);
        break;
    }

    ui->plot->replot();
}
