#include "abstractmodulecontroller.h"

AbstractModuleController::AbstractModuleController(QObject *parent) : QObject(parent)
{

}

AbstractModuleController::~AbstractModuleController()
{

}

bool AbstractModuleController::setData(Input parameter, double value)
{
    switch (parameter)
    {
    case Input::dt:
        module.set_dt(value);
        return true;
    case Input::n_x:
        module.set_n_x(value);
        return true;
    case Input::n_y:
        module.set_n_y(value);
        return true;
    case Input::n_z:
        module.set_n_z(value);
        return true;
    case Input::omega_x:
        module.set_omega_x(value);
        return true;
    case Input::omega_y:
        module.set_omega_y(value);
        return true;
    case Input::omega_z:
        module.set_omega_z(value);
        return true;
    case Input::rho:
        module.set_rho(value);
        return true;
    case Input::phi:
        module.set_phi(value);
        return true;
    case Input::lambda:
        module.set_lambda(value);
        return true;
    case Input::h:
        module.set_h(value);
        return true;
    default:
        return false;
    }
}

double AbstractModuleController::getData(Output parameter) const
{
    switch (parameter)
    {
    case Output::t:
        return module.get_t();
    case Output::K:
        return module.get_K();
    case Output::psi:
        return module.get_psi();
    case Output::theta:
        return module.get_theta();
    case Output::K_dot:
        return module.get_K_dot();
    case Output::psi_dot:
        return module.get_psi_dot();
    case Output::theta_dot:
        return module.get_theta_dot();
    case Output::V_E:
        return module.get_V_E();
    case Output::V_N:
        return module.get_V_N();
    case Output::V_h:
        return module.get_V_h();
    case Output::V_E_dot:
        return module.get_V_E_dot();
    case Output::V_N_dot:
        return module.get_V_N_dot();
    case Output::V_h_dot:
        return module.get_V_h_dot();
    case Output::lambda:
        return module.get_lambda();
    case Output::phi:
        return module.get_phi();
    case Output::h:
        return module.get_h();
    default:
        return 0.;
    }
}

QVector<double> AbstractModuleController::getDataVector(Output parameter) const
{
    return data.value(parameter);
}

void AbstractModuleController::setIterationCount(quint8 count)
{
    iterationCount = count;
}

void AbstractModuleController::reset()
{
    module.reset();
    data.clear();

    emit dataChanged();
}

void AbstractModuleController::handle()
{
    for (size_t i = 0; i < iterationCount; ++i)
        module.handle();

    data[Output::t].append(module.get_t());
    data[Output::K].append(module.get_K());
    data[Output::psi].append(module.get_psi());
    data[Output::theta].append(module.get_theta());
    data[Output::K_dot].append(module.get_K_dot());
    data[Output::psi_dot].append(module.get_psi_dot());
    data[Output::theta_dot].append(module.get_theta_dot());
    data[Output::V_E].append(module.get_V_E());
    data[Output::V_N].append(module.get_V_N());
    data[Output::V_h].append(module.get_V_h());
    data[Output::V_E_dot].append(module.get_V_E_dot());
    data[Output::V_N_dot].append(module.get_V_N_dot());
    data[Output::V_h_dot].append(module.get_V_h_dot());
    data[Output::phi].append(module.get_phi());
    data[Output::lambda].append(module.get_lambda());
    data[Output::h].append(module.get_h());
}

