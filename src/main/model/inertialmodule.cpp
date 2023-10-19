#include "inertialmodule.h"

#include <qmath.h>

InertialModule::InertialModule()
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
                C_b_i[i][j] = 0.;
                C_b_0[i][j] = 0.;
                //C_0_i[i][j] = 1.;
                C_b_i[i][j] = 0.;
                C_i_gamma[i][j] = 0.;
                C_0_gamma[i][j] = 0.;
        }
    }

    C_0_i[0][0] = 1.;
    C_0_i[0][1] = 0.;
    C_0_i[0][2] = 0.;
    C_0_i[1][0] = 0.;
    C_0_i[1][1] = 1.;
    C_0_i[1][2] = 0.;
    C_0_i[2][0] = 0.;
    C_0_i[2][1] = 0.;
    C_0_i[2][2] = 1.;
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

void InertialModule::handle()
{
    C_b_0[0][0] = cos(rho);
    C_b_0[0][1] = sin(rho);
    C_b_0[0][2] = 0.;
    C_b_0[1][0] = -sin(rho);
    C_b_0[1][1] = cos(rho);
    C_b_0[1][2] = 0.;
    C_b_0[2][0] = 0.;
    C_b_0[2][1] = 0.;
    C_b_0[2][2] = 1.;

    omega_x_0 = C_b_0[0][0] * omega_x + C_b_0[0][1] * omega_y + C_b_0[0][2] * omega_z;
    omega_y_0 = C_b_0[1][0] * omega_x + C_b_0[1][1] * omega_y + C_b_0[1][2] * omega_z;
    omega_z_0 = C_b_0[2][0] * omega_x + C_b_0[2][1] * omega_y + C_b_0[2][2] * omega_z;

//    C_0_i[0][0] = C_0_i[0][0] + (C_0_i[0][1] * omega_z - C_0_i[0][2] * omega_y) * dt;
//    C_0_i[0][1] = C_0_i[0][1] + (C_0_i[0][2] * omega_x - C_0_i[0][0] * omega_z) * dt;
//    C_0_i[0][2] = C_0_i[0][2] + (C_0_i[0][0] * omega_y - C_0_i[0][1] * omega_x) * dt;
//    C_0_i[1][0] = C_0_i[1][0] + (C_0_i[1][1] * omega_z - C_0_i[1][2] * omega_y) * dt;
//    C_0_i[1][1] = C_0_i[1][1] + (C_0_i[1][2] * omega_x - C_0_i[1][0] * omega_z) * dt;
//    C_0_i[1][2] = C_0_i[1][2] + (C_0_i[1][0] * omega_y - C_0_i[1][1] * omega_x) * dt;
//    C_0_i[2][0] = C_0_i[2][0] + (C_0_i[2][1] * omega_z - C_0_i[2][2] * omega_y) * dt;
//    C_0_i[2][1] = C_0_i[2][1] + (C_0_i[2][2] * omega_x - C_0_i[2][0] * omega_z) * dt;
//    C_0_i[2][2] = C_0_i[2][2] + (C_0_i[2][0] * omega_y - C_0_i[2][1] * omega_x) * dt;

//    for (size_t i = 0; i < 3; ++i)
//    {
//        for (size_t j = 0; j < 3; ++j)
//        {
//            C_b_i[i][j] = 0.;

//            for (size_t k = 0; k < 3; ++k)
//            {
//                C_b_i[i][j] +=  C_0_i[i][k] * C_b_0[k][j];
//            }
//        }
//    }

//    lambda_star = lambda + Omega*dt*iteration;

//    C_i_gamma[0][0] = cos(lambda_star); //транспонированная
//    C_i_gamma[0][1] = 0.;
//    C_i_gamma[0][2] = -sin(lambda_star);
//    C_i_gamma[1][0] = -sin(lambda_star) * sin(phi);
//    C_i_gamma[1][1] = cos(phi);
//    C_i_gamma[1][2] = -cos(lambda_star) * sin(phi);
//    C_i_gamma[2][0] = sin(lambda_star) * cos(phi);
//    C_i_gamma[2][1] = sin(phi);
//    C_i_gamma[2][2] = cos(lambda_star) * cos(phi);

//    C_i_gamma[0][0] = cos(lambda_star);
//    C_i_gamma[0][1] = -sin(lambda_star) * sin(phi);
//    C_i_gamma[0][2] = sin(lambda_star) * cos(phi);
//    C_i_gamma[1][0] = 0.;
//    C_i_gamma[1][1] = cos(phi);
//    C_i_gamma[1][2] = sin(phi);
//    C_i_gamma[2][0] = -sin(lambda_star);
//    C_i_gamma[2][1] = -cos(lambda_star) * sin(phi);
//    C_i_gamma[2][2] = cos(lambda_star) * cos(phi);

//    for (size_t i = 0; i < 3; ++i)
//    {
//        for (size_t j = 0; j < 3; ++j)
//        {
//            C_0_gamma[i][j] = 0.;

//            for (size_t k = 0; k < 3; ++k)
//            {
//                C_0_gamma[i][j] += C_i_gamma[i][k] * C_b_i[k][j];
//            }
//        }
//    }

    C_0_gamma[0][0] = cos(K)*cos(theta) + sin(K)*sin(psi)*sin(K);
    C_0_gamma[0][1] = sin(K)*cos(psi);
    C_0_gamma[0][2] = cos(K)*sin(theta) - sin(K)*sin(psi)*cos(theta);

    C_0_gamma[1][0] = -sin(K)*cos(theta) + cos(K)*sin(psi)*sin(theta);
    C_0_gamma[1][1] = cos(K)*cos(psi);
    C_0_gamma[1][2] = -(sin(K)*sin(theta) + cos(K)*sin(psi)*cos(theta));

    C_0_gamma[2][0] = -cos(psi)*sin(theta);
    C_0_gamma[2][1] = sin(psi);
    C_0_gamma[2][2] = cos(psi)*cos(theta);


    R_phi = a * (1 - e_squared) / pow(pow(1 - e_squared * sin(phi), 2.), 3./2) + h;
    R_lambda = a / pow(pow(1 - e_squared * sin(phi), 2.), 1./2) + h;

    omega_E = - V_N / R_phi;
    omega_N = Omega * cos(phi) + V_E / R_lambda;
    omega_h = Omega * sin(phi) + V_E / R_lambda * tan(phi);

    // Через обобщенное уравнение Пуассона?
//    C_0_gamma[0][0] = C_0_gamma[0][0] + (C_0_gamma[0][1]*omega_z_0 - C_0_gamma[0][2]*omega_y_0 + C_0_gamma[1][0]*omega_h - C_0_gamma[2][0]*omega_N) * dt;
//    C_0_gamma[0][1] = C_0_gamma[0][1] + (C_0_gamma[0][2]*omega_x_0 - C_0_gamma[0][0]*omega_z_0 + C_0_gamma[1][1]*omega_h - C_0_gamma[2][1]*omega_N) * dt;
//    C_0_gamma[0][2] = C_0_gamma[0][2] + (C_0_gamma[0][0]*omega_y_0 - C_0_gamma[0][1]*omega_x_0 + C_0_gamma[1][2]*omega_h - C_0_gamma[2][2]*omega_N) * dt;
//    C_0_gamma[1][0] = C_0_gamma[1][0] + (C_0_gamma[1][1]*omega_z_0 - C_0_gamma[1][2]*omega_y_0 + C_0_gamma[1][0]*omega_h - C_0_gamma[2][0]*omega_N) * dt;
//    C_0_gamma[1][1] = C_0_gamma[1][1] + (C_0_gamma[0][2]*omega_x_0 - C_0_gamma[0][0]*omega_z_0 + C_0_gamma[1][1]*omega_h - C_0_gamma[2][1]*omega_E) * dt;
//    C_0_gamma[1][2] = C_0_gamma[1][2] + (C_0_gamma[0][0]*omega_y_0 - C_0_gamma[0][1]*omega_x_0 + C_0_gamma[1][2]*omega_h - C_0_gamma[2][2]*omega_E) * dt;

    //psi = atan(C_0_gamma[2][1] / sqrt(1 - C_0_gamma[2][1]*C_0_gamma[2][1]));
    //theta = atan(-C_0_gamma[2][0] / C_0_gamma[2][2]);
    //K = 2 * atan(C_0_gamma[0][1] / (C_0_gamma[1][1] + sqrt(1 - C_0_gamma[2][1]*C_0_gamma[2][1])));

    K = K + (1/cos(psi) * (omega_x_0*sin(theta) - omega_z_0*cos(theta)) - sin(psi)/cos(psi) * (omega_E*sin(K) + omega_N*cos(K)) + omega_h) * dt;
    psi = psi + (omega_z_0*sin(theta) + omega_x_0*cos(theta) + omega_N*sin(K) - omega_E*cos(K)) * dt;
    theta = theta + (omega_y_0 + sin(psi)/cos(psi) * omega_x_0*sin(theta) - omega_z_0*cos(theta) - 1/cos(psi)*(omega_E*sin(K) + omega_N*cos(K))) * dt;

    K = limits(K, 0, 2*M_PI);

    psi_dot = omega_z_0 * sin(theta) + omega_x_0 * cos(theta) + omega_N * sin(K) - omega_E * cos(K);
    theta_dot = omega_y_0 + tan(psi) * (omega_x_0 * sin(theta) - omega_z_0 * cos(theta)) - 1/cos(psi) * (omega_E * sin(K) + omega_N * cos(K));
    K_dot = 1/cos(psi) * (omega_x_0 * sin(theta) - omega_z_0 * cos(theta)) - tan(psi) * (omega_E * sin(K) + omega_N * cos(K)) + omega_h;

    n_E = C_0_gamma[0][0] * n_x + C_0_gamma[0][1] * n_y + C_0_gamma[0][2] * n_z;
    n_N = C_0_gamma[1][0] * n_x + C_0_gamma[1][1] * n_y + C_0_gamma[1][2] * n_z;
    n_h = C_0_gamma[2][0] * n_x + C_0_gamma[2][1] * n_y + C_0_gamma[2][2] * n_z;

    g_h = g * (1 + beta * sin(phi)*sin(phi) + beta_1 * sin(2*phi)*sin(2*phi));

    lambda_dot = (lambda - lambda_prev) / dt;
    phi_dot = (phi - phi_prev) / dt;

    a_E_Cor = g_E + V_h * (2*Omega + lambda_dot) * cos(phi) - V_N * (2*Omega + lambda_dot) * sin(phi);
    a_N_Cor = g_N + V_E * (2*Omega + lambda_dot) * sin(phi) + V_h * phi_dot;
    a_h_Cor = g_h - V_E * (2*Omega + lambda_dot) * cos(phi) - V_N * phi_dot;

    V_E_dot = (V_E - V_E_prev) / dt;
    V_N_dot = (V_N - V_N_prev) / dt;
    V_h_dot = (V_h - V_h_prev) / dt;

    V_E_prev = V_E;
    V_N_prev = V_N;
    V_h_prev = V_h;

    V_E = V_E + (n_E - a_E_Cor) * dt;
    V_N = V_N + (n_N - a_N_Cor) * dt;
    V_h = V_h + (n_h - a_h_Cor) * dt;

    phi_prev = phi;
    lambda_prev = lambda;

    phi = phi + V_N / R_phi * dt;
    lambda = lambda + V_E / (R_lambda * cos(phi)) * dt;
    h = h + V_h * dt;

    phi = triangle(M_PI/2, phi, 2*M_PI);
    lambda = saw(M_PI, lambda, 2*M_PI);

    ++iteration;
}

double InertialModule::limits(double value, double min, double max)
{
    while(value > max)
        value -= max;

    while (value <= min)
        value += max;

    return value;
}

double InertialModule::saw(double amplitude, double value, double period)
{
    return 2*amplitude/M_PI * atan( tan( M_PI*value/period ) );
}

double InertialModule::triangle(double amplitude, double value, double period)
{
    return 2*amplitude/M_PI * asin( sin( 2*M_PI/period *value ) );
}

