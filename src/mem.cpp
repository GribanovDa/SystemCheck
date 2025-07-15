#include "/home/mushroom/Проекты/C++/SystemCheck/Include/mem.h"
#include <dirent.h>
#include <fstream>
#include <QMessageBox>

RAM::RAM() {
    try {
        loadRAMInfo();
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Ошибка",
                              QString("Не удалось загрузить информацию об оперативной памяти:\n%1").arg(e.what()));
    }
}

void RAM::loadRAMInfo() {
    std::ifstream meminfo("/proc/meminfo");
    if (!meminfo.is_open()) {
        throw std::runtime_error("Не удалось открыть /proc/meminfo");
    }

    std::string line;
    while (std::getline(meminfo, line)) {
        parseRAMInfoLineForTotalMemory(line);
        parseRAMInfoLineForFreeMemory(line);
    }
}

void RAM::parseRAMInfoLineForTotalMemory(const std::string& line) {
    const size_t colonPos = line.find(':');
    if (colonPos == std::string::npos) return;



    std::string key = line.substr(0, colonPos);
    std::string value = line.substr(colonPos + 1);

    if (key.find("MemTotal") != std::string::npos) {
        memTotal = stringFromKilobytesToGigabytes(stod(value), 1) + " ГБ";
    }
    else if (key.find("SwapTotal") != std::string::npos) {
        swapTotal = stringFromKilobytesToGigabytes(stod(value), 1) + " ГБ";
    }
}

void RAM::parseRAMInfoLineForFreeMemory(const std::string& line) {
    const size_t colonPos = line.find(':');
    if (colonPos == std::string::npos) return;

    std::string key = line.substr(0, colonPos);
    std::string value = line.substr(colonPos + 1);

    if (key.find("MemAvailable") != std::string::npos) {
        memFree = stringFromKilobytesToGigabytes(stod(value), 3) + " ГБ";
    }
    else if (key.find("SwapFree") != std::string::npos) {
        swapFree = stringFromKilobytesToGigabytes(stod(value), 3) + " ГБ";
    }
}

QString RAM::stringFromKilobytesToGigabytes(double kiloBytes, short numbersAfterDecimalPoint){
    return QString::number(kiloBytes/1048576, 'f', numbersAfterDecimalPoint);
}

void RAM::refreshFreeMemory(){
    std::ifstream meminfo("/proc/meminfo");
    std::string line;

    try{
        while (std::getline(meminfo, line)) {
            parseRAMInfoLineForFreeMemory(line);
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Ошибка",
                              QString("Не удалось загрузить информацию о свободной оперативной памяти:\n%1").arg(e.what()));
    }
}
