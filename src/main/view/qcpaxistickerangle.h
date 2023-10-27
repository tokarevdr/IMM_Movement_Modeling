#ifndef QCPAXISTICKERANGLE_H
#define QCPAXISTICKERANGLE_H

#include "../import/qcustomplot.h"

class QCPAxisTickerAngle : public QCPAxisTicker
{
public:
    QCPAxisTickerAngle();
    ~QCPAxisTickerAngle();

    QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision);
};

#endif // QCPAXISTICKERANGLE_H
