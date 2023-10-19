#ifndef TIMERMODULECONTROLLER_H
#define TIMERMODULECONTROLLER_H

#include "abstractmodulecontroller.h"

#include <QTimer>

class TimerModuleController : public AbstractModuleController
{
public:
    TimerModuleController(QObject *parent = 0);
    ~TimerModuleController();

    void start();
    void stop();
    void setTimerInterval(int msec);

private:
    QTimer timer;
};

#endif // TIMERMODULECONTROLLER_H
