#include "/home/mushroom/Проекты/C++/SystemCheck/Include/FileReader.h"
#include <fstream>
#include <stdexcept>
#include <QMessageBox>

FileReader::FileReader(const QVector<QString>& importedPaths) : paths(importedPaths) {
    try{
        fileReaderInitialization(paths);
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Ошибка",
                              QString("Не удалось открыть файл:\n%1").arg(e.what()));
    }
}

void FileReader::fileReaderInitialization(QVector<QString>& paths){

    for(int i = 0; i < paths.length(); ++i){
        std::ifstream path(paths[i].toStdString());
        if (!path.is_open()) {
            throw std::runtime_error("Не удалось открыть " + paths[i].toStdString());
        }

        keyValueInit(path);
        parsedFiles.append(mapKeyValue);
        mapKeyValue.clear();
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
    const size_t colonPos = line.find(':');
    if (colonPos == std::string::npos) {
        QString trimmedLine = QString::fromStdString(line).trimmed();
        mapKeyValue[trimmedLine] = trimmedLine;
        return;
    }
    QString key = QString::fromStdString(line.substr(0, colonPos)).trimmed();
    QString value = QString::fromStdString(line.substr(colonPos + 1)).trimmed();

    if (mapKeyValue.contains(key)) {
        qWarning() << "Дубликат ключа:" << key;
    }
    mapKeyValue[key] = value;
}




QString FileReader::readFirstLineFromFile(const QString& path) const{
    std::ifstream file(path.toStdString());
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + path.toStdString());
    }
    std::string line;
    std::getline(file, line);
    return QString::fromStdString(line).trimmed();
}

QVector<QMap<QString, QString>> FileReader::getVectorOFParsedFiles() const{
    return parsedFiles;
}
