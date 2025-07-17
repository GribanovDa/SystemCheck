#ifndef OPERSYS_H
#define OPERSYS_H

#include <QString>
#include "/home/mushroom/Проекты/C++/SystemCheck/Include/FileReader.h"

class OS{

private:
    QString systemName;
    QString kernelVersion;
    QString userName;
    QString comuterName;
    QString desktopEnvironment;
    QString sessionTime;
    QString homeURL;
    QVector<QString> paths;
    FileReader *fileReader;
    QVector<QMap<QString, QString>> parsedFiles;

    void loadOSInfo();
    QString getDesktopEnvironmentFromSystem();
    QString getUserNameFromSystem();
    void dayVariations(int& days, QString& var);

public:
    OS();

    QString getSystemName() {return systemName;};
    QString getKernelVersion() {return kernelVersion;};
    QString getUserName() {return userName;};
    QString getComuterName() {return comuterName;};
    QString getDesktopEnvironment() {return desktopEnvironment;};
    QString getHomeURL() {return homeURL;};
    QString getSessionTime();
};


#endif // OPERSYS_H
