#include "/home/mushroom/Проекты/C++/SystemCheck/Include/processor.h"
#include <string>
#include <fstream>
#include <QMessageBox>


Processor::Processor(){

    try {
        std::ifstream cpuinfo("/proc/cpuinfo");
        cpuinfo.exceptions(std::ifstream::badbit); // Включаем генерацию исключений

        std::string tempLine;
        char *resultLine;

        while (std::getline(cpuinfo, tempLine)) {
            if (tempLine.find("model name") != std::string::npos) {
                resultLine = &tempLine[13];
                name = (resultLine);
            }
            else if (tempLine.find("cpu cores") != std::string::npos) {
                resultLine = &tempLine[12];
                cores = (resultLine);
            }
            else if (tempLine.find("cpu MHz") != std::string::npos) {
                resultLine = &tempLine[11];
                freq = (resultLine);
            }
            else if (tempLine.find("cache size") != std::string::npos) {
                resultLine = &tempLine[13];
                cash = (resultLine);
            }
            else if (tempLine.find("siblings") != std::string::npos) {
                resultLine = &tempLine[11];
                threads = (resultLine);
            }

        }
        cpuinfo.close();
    }
    catch (const std::exception& e) {
        // Показываем ошибку в диалоговом окне
        QMessageBox::critical(nullptr,
                              "Ошибка",
                              QString("Не удалось обработать файл:\n%1\n\nПричина: %2 \n ")
                                  .arg("/proc/cpuinfo")
                                  .arg(e.what()));
    }
}

QString Processor::getFreq() {

    std::ifstream cpuinfo("/proc/cpuinfo");
    if (!cpuinfo.is_open()) throw std::runtime_error("Failed to open file");

    std::string tempLine, tempFreq;
    char *resultLine;

    while (std::getline(cpuinfo, tempLine)) {
        if (tempLine.find("cpu MHz") != std::string::npos) {
            resultLine = &tempLine[11];
            tempFreq = (resultLine);
            break;
        }
    }
    QString tempFreqSnd = QString::fromStdString(tempFreq);
    return tempFreqSnd;
}



QString Processor::getTemperature() {

    std::ifstream tempFile("/sys/class/hwmon/hwmon3/temp1_input");
    if (!tempFile.is_open()) {
        return "-1.0f";
    }

    std::string tempStr;
    std::getline(tempFile, tempStr);
    tempFile.close();

    try {
        float temp = std::stof(tempStr) / 1000.0f; // Переводим из миллиградусов
        return QString::fromStdString(std::to_string(temp));
    } catch (...) {
        return "-1.0f";
    }
}


