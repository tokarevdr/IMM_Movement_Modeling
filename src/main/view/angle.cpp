#include "angle.h"

#include <cmath>
#include <qmath.h>
#include <QStringList>

Angle::Angle(qint16 deg, qint8 min, qint8 sec)
{
    _deg = deg % 360;
    _min = min % 60;
    _sec = sec % 60;
}

Angle::Angle(const QString &text) // TODO некорректный ввод минусов?
{
    if ((text.count("°") != 1) || (text.count("'") != 3) || (text.count("''") != 1))
    {
        _deg = 0;
        _min = 0;
        _sec = 0;
    }
    else
    {
        QStringList degAndMinSec = text.split("°");

        _deg = degAndMinSec.at(0).toInt();

        QStringList minAndSec = degAndMinSec.at(1).split("'", QString::SkipEmptyParts);

        if (_deg < 0)
        {
            _min = - minAndSec.at(0).toInt();
            _sec = - minAndSec.at(1).toInt();
        }
        else
        {
            _min = minAndSec.at(0).toInt();
            _sec = minAndSec.at(1).toInt();
        }
    }
}

Angle::Angle(double rad)
{
    double deg, min, sec;

    deg = rad * 180.0 / M_PI;

    _deg = static_cast<qint64>(deg) % 360;

    min = (deg - _deg) * 60;

    //_deg %= 360;

    _min = static_cast<qint8>(min);

    sec = (min - _min) * 60;

    _sec = static_cast<qint8>(round(sec));

    if (_sec == 60)
    {
        _sec = 0;

        _min++;

        if (_min == 60)
        {
            _min = 0;

            _deg++;

            _deg %= 360;
        }
    }
}

Angle::~Angle()
{

}

double Angle::toRadians() const
{
    return (_deg + _min / 60. + _sec / 3600.) * M_PI / 180.;
}

QString Angle::toString() const
{
    QString angle = QString::number(abs(_deg)) + "° " + QString::number(abs(_min)) + "' " + QString::number(abs(_sec)) + "''";

    if (_deg < 0 || _min < 0 || _sec < 0)
        return "-" + angle;

    return angle;
}

int Angle::getDegrees() const
{
    return _deg;
}

int Angle::getMinutes() const
{
    return _min;
}

int Angle::getSeconds() const
{
    return _sec;
}

