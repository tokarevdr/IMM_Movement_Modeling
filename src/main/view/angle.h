#ifndef ANGLE_H
#define ANGLE_H

#include <QString>

class Angle
{
public:
    Angle(qint16 deg = 0, qint8 min = 0, qint8 sec = 0);
    Angle(const QString &text);
    Angle(double rad);
    ~Angle();

    double toRadians() const;
    QString toString() const;

    int getDegrees() const;
    int getMinutes() const;
    int getSeconds() const;

private:
    qint16 _deg;
    qint8 _min;
    qint8 _sec;
};

#endif // ANGLE_H
