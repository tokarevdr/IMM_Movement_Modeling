#ifndef DATAMODULECONTROLLER_H
#define DATAMODULECONTROLLER_H

#include "abstractmodulecontroller.h"

class DataModuleController : public AbstractModuleController
{
public:
    DataModuleController(QObject *parent = 0);
    ~DataModuleController();

    bool setInputData(DataModuleController::Input parameter, QVector<double> values);
    void setSamplesNumber(quint32 num);
    void start() override;
    void stop() override;
    void setTimerInterval(int msec) override;
    void handle();

private:
    QMap< Input, QVector<double> > inputData;
    quint32 samplesNumber = 0;
};

#endif // DATAMODULECONTROLLER_H
