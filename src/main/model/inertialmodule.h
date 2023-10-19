#ifndef INERTIALMODULE_H
#define INERTIALMODULE_H

#include <array>

class InertialModule
{
public:
    InertialModule();
    ~InertialModule();

    void set_dt(double dt);

    void set_n_x(double n_x) {this->n_x = n_x;}
    void set_n_y(double n_y) {this->n_y = n_y;}
    void set_n_z(double n_z) {this->n_z = n_z;}

    void set_omega_x(double omega_x) {this->omega_x = omega_x;}
    void set_omega_y(double omega_y) {this->omega_y = omega_y;}
    void set_omega_z(double omega_z) {this->omega_z = omega_z;}

    void set_rho(double rho) {this->rho = rho;}

    void set_phi(double phi) {this->phi = phi; this->phi_prev = phi;}
    void set_lambda(double lambda) {this->lambda = lambda; this->lambda_prev = lambda;}
    void set_h(double h) {this->h = h;}

    void set_K(double K) {this->K = K;}
    void set_psi(double psi) {this->psi = psi;}
    void set_theta(double theta) {this->theta = theta;}

    double get_t() const { return dt*iteration; }
    double get_K() const { return K; }
    double get_psi() const { return psi; }
    double get_theta() const { return theta; }
    double get_K_dot() const { return K_dot; }
    double get_psi_dot() const { return psi_dot; }
    double get_theta_dot() const { return theta_dot; }
    double get_V_E() const { return V_E; }
    double get_V_N() const { return V_N; }
    double get_V_h() const { return V_h; }
    double get_V_E_dot() const { return V_E_dot; }
    double get_V_N_dot() const { return V_N_dot; }
    double get_V_h_dot() const { return V_h_dot; }
    double get_phi() const { return phi; }
    double get_lambda() const { return lambda; }
    double get_h() const { return h; }

    void handle();

private:
    double limits(double value, double min, double max);

    // пилообразный сигнал для ограничения долготы в пределах [-180; 180]
    double saw(double amplitude, double value, double period);

    // пилообразный сигнал для ограничения широты в пределах [-90; 90]
    double triangle(double amplitude, double value, double period);

    double dt = 0.01;

    double n_x = 0.;
    double n_y = 0.;
    double n_z = 0.;

    double n_E = 0.;
    double n_N = 0.;
    double n_h = 0.;

    double omega_x = 0.;
    double omega_y = 0.;
    double omega_z = 0.;

    double omega_x_0 = 0.;
    double omega_y_0 = 0.;
    double omega_z_0 = 0.;

    double omega_E = 0.;
    double omega_N = 0.;
    double omega_h = 0.;

    double rho = 0.;

    double K = 0;
    double psi = 0;
    double theta = 0;

    double K_dot = 0;
    double psi_dot = 0;
    double theta_dot = 0;

    double phi = 0.;
    double lambda = 0.;
    double h = 0.;

    double lambda_star = 0.;

    double lambda_prev = 0.;
    double lambda_dot = 0.;
    double phi_prev = 0.;
    double phi_dot = 0.;

    std::array< std::array<double, 3>, 3> C_b_0;
    std::array< std::array<double, 3>, 3> C_0_i;
    std::array< std::array<double, 3>, 3> C_b_i;
    std::array< std::array<double, 3>, 3> C_i_gamma;
    std::array< std::array<double, 3>, 3> C_0_gamma;

    const double e_squared = 0.0066934;
    const double a = 6378245;
    const double Omega = 7.292116e-5;
    const double beta = 0.0053171;
    const double beta_1 = 0.0000071;

    double g_E = 0.;
    double g_N = 0.;
    double g_h = 0.;
    double g = 9.780318;

    double a_E_Cor = 0.;
    double a_N_Cor = 0.;
    double a_h_Cor = 0.;

    double R_phi = 0.;
    double R_lambda = 0.;

    double V_E = 0.;
    double V_N = 0.;
    double V_h = 0.;

    double V_E_prev = 0.;
    double V_N_prev = 0.;
    double V_h_prev = 0.;

    double V_E_dot = 0.;
    double V_N_dot = 0.;
    double V_h_dot = 0.;

    long unsigned int iteration = 0;
};

#endif // INERTIALMODULE_H
