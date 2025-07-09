#include "/home/mushroom/Проекты/C++/SystemCheck/Include/processor.h"

#include <fstream>
#include <stdexcept>
#include <QMessageBox>

Processor::Processor() {
    try {
        loadCpuInfo();
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Ошибка",
                              QString("Не удалось загрузить информацию о процессоре:\n%1").arg(e.what()));
    }
}

void Processor::loadCpuInfo() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    if (!cpuinfo.is_open()) {
        throw std::runtime_error("Не удалось открыть /proc/cpuinfo");
    }

    std::string line;
    while (std::getline(cpuinfo, line)) {
        parseCpuInfoLine(line);
    }
}

void Processor::parseCpuInfoLine(const std::string& line) {
    const size_t colonPos = line.find(':');
    if (colonPos == std::string::npos) return;

    const std::string key = line.substr(0, colonPos);
    const std::string value = line.substr(colonPos + 1);

    if (key.find("model name") != std::string::npos) {
        name = QString::fromStdString(value).trimmed();
    }
    else if (key.find("cpu cores") != std::string::npos) {
        cores = QString::fromStdString(value).trimmed();
    }
    else if (key.find("cpu MHz") != std::string::npos) {
        freq = QString::fromStdString(value).trimmed();
    }
    else if (key.find("cache size") != std::string::npos) {
        cache = QString::fromStdString(value).trimmed();
    }
    else if (key.find("siblings") != std::string::npos) {
        threads = QString::fromStdString(value).trimmed();
    }
}

QString Processor::getFreq() const {
    return freq.isEmpty() ? "N/A" : freq;
}

QString Processor::getTemperature() const {
    try {
        const QString tempStr = readFirstLineFromFile("/sys/class/hwmon/hwmon3/temp1_input");
        bool ok;
        const float temp = tempStr.toFloat(&ok) / 1000.0f;

        return ok ? QString::number(temp, 'f', 1) + "°C" : "N/A";
    } catch (...) {
        return "N/A";
    }
}

QString Processor::readFirstLineFromFile(const std::string& path) const {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + path);
    }

    std::string line;
    std::getline(file, line);
    return QString::fromStdString(line).trimmed();
}


