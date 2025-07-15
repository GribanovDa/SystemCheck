#include "/home/mushroom/Проекты/C++/SystemCheck/Include/processor.h"

#include <fstream>
#include <stdexcept>
#include <QMessageBox>

Processor::Processor() {
    paths = {{"/proc/cpuinfo"}, {"/sys/class/hwmon/hwmon3/temp1_input"}};
    fileReader = new FileReader(paths);
    parsedFiles = fileReader->getVectorOFParsedFiles();
    try {
        loadCpuInfo();
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Ошибка",
                              QString("Не удалось загрузить информацию о процессоре:\n%1").arg(e.what()));
    }
}

void Processor::loadCpuInfo() {

    for (const QMap<QString, QString>& currentMap : parsedFiles) {
        if (currentMap.contains("model name")) {
            name = currentMap.value("model name");  // Берём значение из текущего элемента
        }
        if (currentMap.contains("cpu cores")) {
            cores = currentMap.value("cpu cores");
        }
        if (currentMap.contains("cache size")) {
            cache = currentMap.value("cache size");
        }
        if (currentMap.contains("siblings")) {
            threads = currentMap.value("siblings");
        }
    }
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

QString Processor::getFrequency() {
    std::ifstream meminfo("/proc/cpuinfo");
    std::string line;

    try{
        while (std::getline(meminfo, line)) {
            parseCpuInfoLineFrequency(line);
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Ошибка",
                              QString("Не удалось загрузить информацию о свободной оперативной памяти:\n%1").arg(e.what()));
    }
    return frequency + " МГц";
}

void Processor::parseCpuInfoLineFrequency(const std::string& line){
    const size_t colonPos = line.find(':');
    if (colonPos == std::string::npos) return;

    const std::string key = line.substr(0, colonPos);
    const std::string value = line.substr(colonPos + 1);

    if (key.find("cpu MHz") != std::string::npos) {
        frequency = QString::fromStdString(value).trimmed();
    }
}


