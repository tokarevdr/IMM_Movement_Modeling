#ifndef INERTIALMODULE_H
#define INERTIALMODULE_H

#include <array>

#include <QVector>

class InertialModule
{
public:
    InertialModule();
    ~InertialModule();

    void set_dt(double dt);
    void set_V_x(double V_x);
    void set_V_y(double V_y);
    void set_V_z(double V_z);
    void set_omega_circulation(double omega_circulation);
    void set_K_0(double K_0);
    void set_psi_0(double psi_0);
    void set_theta_0(double theta_0);
    void set_K_max(double K_max);
    void set_psi_max(double psi_max);
    void set_theta_max(double theta_max);
    void set_T_K(double T_K);
    void set_T_psi(double T_psi);
    void set_T_theta(double T_theta);
    void set_PSI_K(double PSI_K);
    void set_PSI_psi(double PSI_psi);
    void set_PSI_theta(double PSI_theta);
    void set_phi_0(double phi_0);
    void set_lambda_0(double lambda_0);
    void set_h_0(double h_0);

    double get_dt();
    double get_V_x();
    double get_V_y();
    double get_V_z();
    double get_omega_circulation();
    double get_K_0();
    double get_psi_0();
    double get_theta_0();
    double get_K_max();
    double get_psi_max();
    double get_theta_max();
    double get_T_K();
    double get_T_psi();
    double get_T_theta();
    double get_PSI_K();
    double get_PSI_psi();
    double get_PSI_theta();
    double get_phi_0();
    double get_lambda_0();
    double get_h_0();
    double get_K();
    double get_psi();
    double get_theta();
    double get_phi();
    double get_lambda();
    double get_h();
    array< array<double, 3>, 3> get_C();
    double get_R_phi();
    double get_R_lambda();
    double get_V_E();
    double get_V_N();
    double get_V_h();

    void handle();

private:
    double dt = 0.01;

    double V_x = 0.;
    double V_y = 0.;
    double V_z = 0.;

    double W_x = 0.;
    double W_y = 0.;
    double W_z = 0.;

    double omega_circulation = 0.;

    double K_0 = 0.;
    double psi_0 = 0.;
    double theta_0 = 0.;

    double K_max = 0.;
    double psi_max = 0.;
    double theta_max = 0.;

    double T_K = 1.;
    double T_psi = 1.;
    double T_theta = 1.;

    double PSI_K = 0.;
    double PSI_psi = 0.;
    double PSI_theta = 0.;

    double phi_0 = 0.;
    double lambda_0 = 0.;
    double h_0 = 0.;

    double K = 0;
    double psi = 0;
    double theta = 0;

    double phi = 0.;
    double lambda = 0.;
    double h = 0.;

    array< array<double, 3>, 3> C[3][3]{};

    const double e_squared = 0.0066934;
    const double a = 6378245;

    double R_phi = 0.;
    double R_lambda = 0.;

    double V_E = 0.;
    double V_N = 0.;
    double V_h = 0.;

    QVector<double> time;
    QVector<double> data_phi;
    QVector<double> data_lambda;
};

#endif // INERTIALMODULE_H
