#ifndef TIMERMODULECONTROLLER_H
#define TIMERMODULECONTROLLER_H

#include "abstractmodulecontroller.h"

#include <QTimer>

class TimerModuleController : public AbstractModuleController
{
public:
    TimerModuleController(QObject *parent = 0);
    ~TimerModuleController();

    void start() override;
    void stop() override;
    void setTimerInterval(int msec) override;

private:
    QTimer timer;
};

#endif // TIMERMODULECONTROLLER_H
