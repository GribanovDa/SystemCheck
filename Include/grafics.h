#ifndef GRAFICS_H
#define GRAFICS_H

#include "/home/mushroom/Проекты/C++/SystemCheck/Include/FileReader.h"
#include <QMap>

struct GpuInfo {
    QString vendor;
    QString model;
    QString driver;
    QString temperature;

    QString summary() const {
        return QString("%1 %2 (Driver: %3)")
        .arg(vendor).arg(model).arg(driver);
    }
};

class Grafics{

private:
    QList<GpuInfo> gpuInfo;
    QVector<QString> paths;
    FileReader *fileReader;
    QVector<QMap<QString, QString>> parsedFiles;

    void refreshGraficsTemp();
    void pathsInitialize();
    QList<GpuInfo> getGpuInfoViaLshw();
    QString deleteEverythingOutsideBrackets(QString text);


public:
    Grafics();

    QList<GpuInfo> getGraficsInfo(){return gpuInfo;};
    QString getTemperature(short numberOfCard);


};



#endif // GRAFICS_H
