#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QApplication>
#include "/home/mushroom/Проекты/C++/SystemCheck/Include/FileReader.h"

class Processor {
private:
    QString name;
    QString cache;
    QString frequency;
    QString cores;
    QString threads;
    QVector<QString> paths;
    FileReader *fileReader;
    QVector<QMap<QString, QString>> parsedFiles;

    void loadCpuInfo();
    QString readFirstLineFromFile(const std::string& path) const;
    void parseCpuInfoLineFrequency(const std::string& line);

public:
    Processor();
    ~Processor(){delete fileReader;}

    QString getName() const { return name;}
    QString getCash() const { return cache;}
    QString getCores() const { return cores;}
    QString getThreads() const { return threads;}
    QString getTemperature();
    QString getFrequency();
};

#endif // PROCESSOR_H
