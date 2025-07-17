#include "/home/mushroom/Проекты/C++/SystemCheck/Include/processor.h"

#include <QMessageBox>

Processor::Processor() {
    paths = {{"/proc/cpuinfo"}, {"/sys/class/hwmon/hwmon3/temp1_input"}};
    fileReader = new FileReader(paths);
    parsedFiles = fileReader->getRefreshedVectorOfParsedFiles();
    loadCpuInfo();
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

QString Processor::getTemperature(){
    parsedFiles = fileReader->getRefreshedVectorOfParsedFiles();
    bool ok;
    const float temp = parsedFiles[1].first().toFloat(&ok) / 1000.0f;
    return ok ? QString::number(temp, 'f', 1) + "°C" : "N/A";
}


QString Processor::getFrequency() {
    parsedFiles = fileReader->getRefreshedVectorOfParsedFiles();

    if (parsedFiles[0].contains("cpu MHz")) {
        frequency = parsedFiles[0].value("cpu MHz");
    }
    return frequency + " МГц";
}



