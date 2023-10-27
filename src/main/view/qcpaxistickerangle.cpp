#include "qcpaxistickerangle.h"
#include "angle.h"

QCPAxisTickerAngle::QCPAxisTickerAngle()
{

}

QCPAxisTickerAngle::~QCPAxisTickerAngle()
{

}

QString QCPAxisTickerAngle::getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision)
{
    Q_UNUSED(locale)
    Q_UNUSED(formatChar)
    Q_UNUSED(precision)
    return Angle(tick).toString();
}
