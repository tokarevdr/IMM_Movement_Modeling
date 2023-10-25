#include "timermodulecontroller.h"

TimerModuleController::TimerModuleController(QObject *parent) :
    AbstractModuleController(parent)
{
    timer.setInterval(1000);

    connect(&timer, QTimer::timeout, this, TimerModuleController::handle);
}

TimerModuleController::~TimerModuleController()
{

}

void TimerModuleController::handle()
{
    AbstractModuleController::handle();

    emit dataChanged();
}

void TimerModuleController::start()
{
    timer.start();
}

void TimerModuleController::stop()
{
    timer.stop();
}

void TimerModuleController::setTimerInterval(int msec)
{
    timer.setInterval(msec);
}

void TimerModuleController::setSensorsDataFilePath(const QString &filepath)
{
    Q_UNUSED(filepath);
}

