#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QApplication>

class Processor {
private:
    QString name;
    QString cache;
    QString freq;
    QString cores;
    QString threads;

    void loadCpuInfo();
    void parseCpuInfoLine(const std::string& line);
    QString readFirstLineFromFile(const std::string& path) const;

public:
    Processor();

    QString getName() const { return name;}
    QString getCash() const { return cache;}
    QString getCores() const { return cores;}
    QString getThreads() const { return threads;}

    QString getFreq() const;
    QString getTemperature() const;
};

#endif // PROCESSOR_H
