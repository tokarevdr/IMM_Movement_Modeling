#include "datamodulecontroller.h"

#include <QFile>
#include <QStringList>
#include <algorithm>

DataModuleController::DataModuleController(QObject *parent) :
    AbstractModuleController(parent)
{

}

DataModuleController::~DataModuleController()
{

}

bool DataModuleController::setInputData(DataModuleController::Input parameter, QVector<double> values)
{
    if (values.count() != samplesNumber)
        return false;

    inputData[parameter] = values;

    return true;
}

void DataModuleController::setSamplesNumber(quint32 num)
{
    samplesNumber = num;
}

void DataModuleController::start()
{
    QFile file(sensorsDataFilePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString line;
    QStringList values;

    QVector<double> n_x;
    QVector<double> n_y;
    QVector<double> n_z;
    QVector<double> omega_x;
    QVector<double> omega_y;
    QVector<double> omega_z;

    while (!file.atEnd())
    {
        line = file.readLine();
        values = line.split(',');

        n_x.append(values.at(0).toDouble());
        n_y.append(values.at(1).toDouble());
        n_z.append(values.at(2).toDouble());

        omega_x.append(values.at(3).toDouble());
        omega_y.append(values.at(4).toDouble());
        omega_z.append(values.at(5).toDouble());
    }

    int samples = std::min({n_x.count(), n_y.count(), n_z.count(),
                                 omega_x.count(), omega_y.count(), omega_z.count()});

    n_x.resize(samples);
    n_y.resize(samples);
    n_z.resize(samples);
    omega_x.resize(samples);
    omega_y.resize(samples);
    omega_z.resize(samples);

    setSamplesNumber(samples);

    setInputData(Input::n_x, n_x);
    setInputData(Input::n_y, n_y);
    setInputData(Input::n_z, n_z);
    setInputData(Input::omega_x, omega_x);
    setInputData(Input::omega_y, omega_y);
    setInputData(Input::omega_z, omega_z);

    handle();
}

void DataModuleController::stop()
{

}

void DataModuleController::setTimerInterval(int msec)
{
    Q_UNUSED(msec);
}

void DataModuleController::setSensorsDataFilePath(const QString &filepath)
{
    sensorsDataFilePath = filepath;
}

void DataModuleController::handle()
{
    for (size_t i = 0; i < samplesNumber; ++i)
    {
        module.set_n_x(inputData.value(Input::n_x).at(i));
        module.set_n_y(inputData.value(Input::n_y).at(i));
        module.set_n_z(inputData.value(Input::n_z).at(i));
        module.set_omega_x(inputData.value(Input::omega_x).at(i));
        module.set_omega_y(inputData.value(Input::omega_y).at(i));
        module.set_omega_z(inputData.value(Input::omega_z).at(i));
        //module.set_rho(inputData.value(Input::rho).at(i));

        AbstractModuleController::handle();
    }

    emit dataChanged();
}
