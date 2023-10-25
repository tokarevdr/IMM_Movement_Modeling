#ifndef ABSTRACTMODULECONTROLLER_H
#define ABSTRACTMODULECONTROLLER_H

#include <QObject>
#include <QMap>
#include <QVector>

#include "inertialmodule.h"

class AbstractModuleController : public QObject
{
    Q_OBJECT
public:
    explicit AbstractModuleController(QObject *parent = 0);
    ~AbstractModuleController();

    enum class Input
    {
        dt,
        n_x,
        n_y,
        n_z,
        omega_x,
        omega_y,
        omega_z,
        rho,
        phi,
        lambda,
        h
    };

    enum class Output
    {
        t,
        K,
        psi,
        theta,
        K_dot,
        psi_dot,
        theta_dot,
        V_E,
        V_N,
        V_h,
        V_E_dot,
        V_N_dot,
        V_h_dot,
        phi,
        lambda,
        h
    };

    bool setData(AbstractModuleController::Input parameter, double value);
    double getData(AbstractModuleController::Output parameter) const;
    QVector<double> getDataVector(AbstractModuleController::Output parameter) const;
    void reset();
    void handle();

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void setTimerInterval(int msec) = 0;

    virtual void setSensorsDataFilePath(const QString &filepath) = 0;

signals:
    void dataChanged();

protected:
    InertialModule module;
    QMap< Output, QVector<double> > data;
};

#endif // ABSTRACTMODULECONTROLLER_H
