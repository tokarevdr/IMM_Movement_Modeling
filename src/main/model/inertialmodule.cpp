#include "inertialmodule.h"

#include <qmath.h>

InertialModule::InertialModule()
{

}

InertialModule::~InertialModule()
{

}

void InertialModule::set_dt(double dt)
{
    if (dt < 0)
        return;

    this->dt = dt;
}

void InertialModule::set_V_x(double V_x)
{
    this->V_x = V_x;
}

void InertialModule::set_V_y(double V_y)
{
    this->V_y = V_y;
}

void InertialModule::set_V_z(double V_z)
{
    this->V_z = V_z;
}

void InertialModule::set_omega_circulation(double omega_circulation)
{
    this->omega_circulation = omega_circulation;
}

void InertialModule::set_K_0(double K_0)
{
    this->K_0 = K_0;
}

void InertialModule::set_psi_0(double psi_0)
{
    this->psi_0 = psi_0;
}

void InertialModule::set_theta_0(double theta_0)
{
    this->theta_0 = theta_0;
}

void InertialModule::set_K_max(double K_max)
{
    this->K_max = K_max;
}

void InertialModule::set_psi_max(double psi_max)
{
    this->psi_max = psi_max;
}

void InertialModule::set_theta_max(double theta_max)
{
    this->theta_max = theta_max;
}

void InertialModule::set_T_K(double T_K)
{
    if (T_K <= 0)
        return;

    this->T_K = T_K;
}

void InertialModule::set_T_psi(double T_psi)
{
    if (T_psi <= 0)
        return;

    this->T_psi = T_psi;
}

void InertialModule::set_T_theta(double T_theta)
{
    if (T_theta <= 0)
        return;

    this->T_theta = T_theta;
}

void InertialModule::set_PSI_K(double PSI_K)
{
    this->PSI_K = PSI_K;
}

void InertialModule::set_PSI_psi(double PSI_psi)
{
    this->PSI_psi = PSI_psi;
}

void InertialModule::set_PSI_theta(double PSI_theta)
{
    this->PSI_theta = PSI_theta;
}

void InertialModule::set_phi_0(double phi_0)
{
    this->phi_0 = phi_0;
}

void InertialModule::set_lambda_0(double lambda_0)
{
    this->lambda_0 = lambda_0;
}

void InertialModule::set_h_0(double h_0)
{
    this->h_0 = h_0;
}

double InertialModule::get_dt()
{
    return dt;
}

double InertialModule::get_V_x()
{
    return V_x;
}

double InertialModule::get_V_y()
{
    return V_y;
}

double InertialModule::get_V_z()
{
    return V_z;
}

double InertialModule::get_omega_circulation()
{
    return omega_circulation;
}

double InertialModule::get_K_0()
{
    return K_0;
}

double InertialModule::get_psi_0()
{
    return psi_0;
}

double InertialModule::get_theta_0()
{
    return theta_0;
}

double InertialModule::get_K_max()
{
    return K_max;
}

double InertialModule::get_psi_max()
{
    return psi_max;
}

double InertialModule::get_theta_max()
{
    return theta_max;
}

double InertialModule::get_T_K()
{
    return T_K;
}

double InertialModule::get_T_psi()
{
    return T_psi;
}

double InertialModule::get_T_theta()
{
    return T_theta;
}

double InertialModule::get_PSI_K()
{
    return PSI_K;
}

double InertialModule::get_PSI_psi()
{
    return PSI_psi;
}

double InertialModule::get_PSI_theta()
{
    return PSI_theta;
}

double InertialModule::get_phi_0()
{
    return phi_0;
}

double InertialModule::get_lambda_0()
{
    return lambda_0;
}

double InertialModule::get_h_0()
{
    return h_0;
}

double InertialModule::get_K()
{
    return K;
}

double InertialModule::get_psi()
{
    return psi;
}

double InertialModule::get_theta()
{
    return theta;
}

double InertialModule::get_phi()
{
    return phi;
}

double InertialModule::get_lambda()
{
    return lambda;
}

double InertialModule::get_h()
{
    return h;
}

array< array<double, 3>, 3> InertialModule::get_C()
{
    return C;
}

double InertialModule::get_R_phi()
{
    return R_phi;
}

double InertialModule::get_R_lambda()
{
    return R_lambda;
}

double InertialModule::get_V_E()
{
    return V_E;
}

double InertialModule::get_V_N()
{
    return V_N;
}

double InertialModule::get_V_h()
{
    return V_h;
}

void InertialModule::handle()
{
    size_t point_num = 100000;

    for (size_t i = 0; i < point_num; ++i)
    {

        R_phi = a * (1 - e_squared) / pow(pow(1 - e_squared * sin(phi), 2.), 3./2) + h;
        R_lambda = a / pow(pow(1 - e_squared * sin(phi), 2.), 1./2) + h;

        K = K + K_0 + omega_circulation * dt + K_max * sin(2*M_PI / T_K * dt + PSI_K);

        psi = psi + psi_0 + psi_max * sin(2*M_PI / T_psi * dt + PSI_psi);

        theta = theta + theta_0 + theta_max * sin(2*M_PI / T_theta * dt + PSI_theta);

        C[0][0] = cos(K) * cos(theta) + sin(K) * sin(psi) * sin(theta);
        C[0][1] = sin(K) * cos(psi);
        C[0][2] = cos(K) * sin(theta) - sin(K) * sin(psi) * cos(theta);
        C[1][0] = -sin(K) * cos(theta) + cos(K) * sin(psi) * sin(theta);
        C[1][1] = cos(K) * cos(psi);
        C[1][2] = -sin(K) * sin(theta) - cos(K) * sin(psi) * cos(theta);
        C[2][0] = -cos(psi) * sin(theta);
        C[2][1] = sin(psi);
        C[2][2] = cos(psi) * cos(theta);

        V_E = C[0][0] * V_x + C[0][1] *  V_y + C[0][2] * V_z;
        V_N = C[1][0] * V_x + C[1][1] *  V_y + C[1][2] * V_z;
        V_h = C[2][0] * V_x + C[2][1] *  V_y + C[2][2] * V_z;

        phi = phi + V_N / R_phi * dt;
        lambda = lambda + V_E / (R_lambda * cos(phi)) * dt;
        h = h + V_h * dt;

        time.append(dt*i);
        data1.append(phi * 180 / M_PI);
        data2.append(lambda * 180 / M_PI);
    }
}

