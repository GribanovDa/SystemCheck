#ifndef GRAFICS_H
#define GRAFICS_H

#include <QString>

class Grafics{

private:
    QString name;
    QString energy; //sys/class/drm/card1/device/hwmon/hwmon2/power_input
    QString temp; //sys/class/drm/card1/device/hwmon/hwmon2/temp1_input
    QString cores;
    QString threads;

public:
    Processor();

    QString getName() const { return name;}
    QString getCash() const { return cash;}
    QString getCores() const { return cores;}
    QString getThreads() const { return threads;}

    QString getFreq();
    QString getTemperature();

};



#endif // GRAFICS_H
