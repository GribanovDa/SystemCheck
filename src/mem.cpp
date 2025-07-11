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
    std::ifstream cpuinfo("/proc/meminfo");
    if (!cpuinfo.is_open()) {
        throw std::runtime_error("Не удалось открыть /proc/meminfo");
    }

    std::string line;
    while (std::getline(cpuinfo, line)) {
        parseRAMInfoLine(line);
    }
}

void RAM::parseRAMInfoLine(const std::string& line) {
    const size_t colonPos = line.find(':');
    if (colonPos == std::string::npos) return;

    const std::string key = line.substr(0, colonPos);
    const std::string value = line.substr(colonPos + 1);

    if (key.find("MemTotal") != std::string::npos) {
        memTotal = QString::fromStdString(stringFromKilobytesToGigabytes(stod(value))) + " ГБ";
    }
    else if (key.find("MemFree") != std::string::npos) {
        memFree = QString::fromStdString(stringFromKilobytesToGigabytes(stod(value))) + " ГБ";
    }
    else if (key.find("cpu MHz") != std::string::npos) {
        swapFree = QString::fromStdString(stringFromKilobytesToGigabytes(stod(value))) + " ГБ";
    }
    else if (key.find("cache size") != std::string::npos) {
        swapTotal = QString::fromStdString(stringFromKilobytesToGigabytes(stod(value))) + " ГБ";
    }
}


std::string RAM::stringFromKilobytesToGigabytes(double kiloBytes){
    return std::to_string(kiloBytes/1048576);
}
