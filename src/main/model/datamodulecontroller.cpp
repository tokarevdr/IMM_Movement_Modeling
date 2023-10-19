#include "datamodulecontroller.h"

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
}
