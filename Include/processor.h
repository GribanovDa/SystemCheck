#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QApplication>

class Processor {
private:
    QString name;
    QString cash;
    QString freq;
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

#endif // PROCESSOR_H
