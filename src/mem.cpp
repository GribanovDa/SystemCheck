#include "/home/mushroom/Проекты/C++/SystemCheck/Include/mem.h"
#include <dirent.h>
#include <QMessageBox>

RAM::RAM() {
    path = {{"/proc/meminfo"}};
    fileReader = new FileReader(path);
    parsedFile = fileReader->getRefreshedVectorOfParsedFiles();
    loadRAMInfo();
}

void RAM::loadRAMInfo() {
        takeInfoAboutTotalMemory();
        takeInfoAboutFreeMemory();
}

void RAM::takeInfoAboutTotalMemory() {
    std::string temp;

    for (const QMap<QString, QString>& currentMap : parsedFile) {
        if (currentMap.contains("MemTotal")) {
            temp = currentMap.value("MemTotal").toStdString();
            memTotal = stringFromKilobytesToGigabytes(stod(temp), 1) + " ГБ";
        }
        if (currentMap.contains("SwapTotal")) {
            temp = currentMap.value("SwapTotal").toStdString();
            swapTotal = stringFromKilobytesToGigabytes(stod(temp), 1) + " ГБ";
        }
    }
}

void RAM::takeInfoAboutFreeMemory() {
    parsedFile = fileReader->getRefreshedVectorOfParsedFiles();
    std::string temp;

    for (const QMap<QString, QString>& currentMap : parsedFile) {
        if (currentMap.contains("MemAvailable")) {
            temp = currentMap.value("MemAvailable").toStdString();
            memFree = stringFromKilobytesToGigabytes(stod(temp), 3) + " ГБ";
        }
        if (currentMap.contains("SwapFree")) {
            temp = currentMap.value("SwapFree").toStdString();
            swapFree = stringFromKilobytesToGigabytes(stod(temp), 3) + " ГБ";
        }
    }
}

QString RAM::stringFromKilobytesToGigabytes(double kiloBytes, short numbersAfterDecimalPoint) const{
    return QString::number(kiloBytes/1048576, 'f', numbersAfterDecimalPoint);
}

QString RAM::getSwapFree(){
    takeInfoAboutFreeMemory();
    return swapFree;
}

QString RAM::getMemFree(){
    takeInfoAboutFreeMemory();
    return memFree;
}

