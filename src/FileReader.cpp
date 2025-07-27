#include "/home/mushroom/Проекты/C++/SystemCheck/Include/FileReader.h"
#include <fstream>
#include <stdexcept>
#include <QMessageBox>

FileReader::FileReader(const QVector<QString>& importedPaths) : paths(importedPaths) {
    refreshInfo();
}

void FileReader::refreshInfo(){
    mapKeyValue.clear();
    parsedFiles.clear();

    try{
        fileReaderInitialization(paths);
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Ошибка",
                              QString("Не удалось открыть файл:\n%1").arg(e.what()));
    }
}

void FileReader::fileReaderInitialization(QVector<QString>& paths) {
    for (int i = 0; i < paths.size(); ) {
        std::ifstream file(paths[i].toStdString());
        if (!file.is_open()) {
            QString errorPath = paths[i];
            mapKeyValue.insert(errorPath, "unknown");
            parsedFiles.append(mapKeyValue);
            paths.remove(i);

            throw std::runtime_error("Не удалось открыть " + errorPath.toStdString());
        }

        keyValueInit(file);
        parsedFiles.append(mapKeyValue);
        mapKeyValue.clear();
        file.close();

        i++;
    }
}

void FileReader::keyValueInit(std::ifstream& path){
    std::string line;
    while (std::getline(path, line)) {
        if (line.empty() || line.find_first_not_of(' ') == std::string::npos) {
            continue;  // Пропускаем пустые строки
        }
        parseInfoFromFileToMap(line);
    }
}

void FileReader::parseInfoFromFileToMap(const std::string& line) {
    size_t colonPos = line.find(':');

    if(colonPos == std::string::npos){
        colonPos = line.find('=');
    }

    if (colonPos == std::string::npos) {
        QString trimmedLine = QString::fromStdString(line).trimmed();
        mapKeyValue[trimmedLine] = trimmedLine;
        return;
    }
    QString key = QString::fromStdString(line.substr(0, colonPos)).trimmed();
    QString value = QString::fromStdString(line.substr(colonPos + 1)).trimmed();

    mapKeyValue[key] = value;
}


QVector<QMap<QString, QString>> FileReader::getRefreshedVectorOfParsedFiles() {
    refreshInfo();
    return parsedFiles;
}
