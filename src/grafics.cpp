#include "/home/mushroom/Проекты/C++/SystemCheck/Include/grafics.h"
#include <dirent.h>
#include <QProcess>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <stdexcept>
#include <regex>

Grafics::Grafics() {

    pathsInitialize();

    fileReader = new FileReader(paths);
    parsedFiles = fileReader->getRefreshedVectorOfParsedFiles();
    gpuInfo = getGpuInfoViaLshw();
    refreshGraficsTemp();

}

void Grafics::pathsInitialize() {
    QString name;
    dirent* entry;
    DIR* dir = opendir("/sys/class/drm");

    if (!dir) {
        throw std::runtime_error("Не удалось открыть директорию /sys/class/drm");
    }

    while ((entry = readdir(dir)) != nullptr) {
        name = entry->d_name;
        if ((name.startsWith("card") && name.length() > 4) && !name.contains('-')){
            paths.push_back("/sys/class/drm/" + name + "/device/hwmon/hwmon2/temp1_input");
        }
    }
    closedir(dir);
}


void Grafics::refreshGraficsTemp(){
    parsedFiles = fileReader->getRefreshedVectorOfParsedFiles();
    for (int i = 0; i < parsedFiles.length(); i++) {
        gpuInfo[i].temperature = parsedFiles[i].first();
    }
}


QList<GpuInfo> Grafics::getGpuInfoViaLshw() {
    QList<GpuInfo> gpus;
    QProcess process;

    // Запускаем lshw с JSON-выводом для удобного парсинга
    process.start("lshw", {"-C", "display", "-json"});
    if (!process.waitForFinished(3000)) {  // Таймаут 3 секунды
        throw std::runtime_error("lshw execution failed");
    }

    QByteArray output = process.readAllStandardOutput();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(output, &error);

    if (error.error != QJsonParseError::NoError) {
        throw std::runtime_error("JSON parse error:");
        return gpus;
    }

    QJsonArray devices = doc.array();
    for (const QJsonValue &deviceValue : devices) {
        QJsonObject device = deviceValue.toObject();
        GpuInfo gpu;

        gpu.vendor = device["vendor"].toString();
        gpu.model = deleteEverythingOutsideBrackets(device["product"].toString());
        gpu.driver = device["description"].toString();

        gpus.append(gpu);
    }
    return gpus;
}

QString Grafics::deleteEverythingOutsideBrackets(QString text){
    std::string temp = text.toStdString();
    std::string result;
    bool inBrackets = false;

    for (char c : temp) {
        if (c == '[') {
            inBrackets = true;
            continue;
        }

        if (c == ']') {
            inBrackets = false;
            continue;
        }

        if (inBrackets) result += c;
    }

    return QString::fromStdString(result);
}

QString Grafics::getTemperature(short numberOfCard){
    refreshGraficsTemp();
    return QString::number((gpuInfo[numberOfCard].temperature).toFloat() / 1000.0f);
}
