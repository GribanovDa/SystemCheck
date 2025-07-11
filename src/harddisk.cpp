#include "/home/mushroom/Проекты/C++/SystemCheck/Include/harddisk.h"
/*
#include <dirent.h>
#include <fstream>
#include <QMessageBox>

QVector<QString> listDisks() {
    QVector<QString> disks;
    DIR* dir = opendir("/sys/block");
    if (!dir) return disks;

    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        QString name = entry->d_name;
        if (name != "." && name != ".." && name != "loop*") {
            disks.push_back(name);
        }
    }
    closedir(dir);
    return disks;
}

HardDisk::HardDisk(){
    QVector<QString> disks = listDisks();
    QString tempLine;

    try {
        std::string tempLine;
        for (int i = 0; i < disks.size(); ++i){
            std::ifstream file("/sys/block/" + disks[i].toStdString() + "/device/model");
            file.exceptions(std::ifstream::badbit); // Включаем генерацию исключений

            std::getline(file, tempLine);
            name.push_back(QString::fromStdString(tempLine));
            file.close();
        }
    }
    catch (const std::exception& e) {
        // Показываем ошибку в диалоговом окне
        QMessageBox::critical(nullptr,
                              "Ошибка",
                              QString("Не удалось обработать файл:\n%1\n\nПричина: %2")
                                  .arg("/sys/block/название_накопителя/device/model")
                                  .arg(e.what()));
        name.push_back("Ошибка отображения имени");
    }

    try {
        std::string tempLine;
        for (int i = 0; i < disks.size(); ++i){
            std::ifstream file("/sys/block/" + disks[i].toStdString() + "/queue/rotational");
            file.exceptions(std::ifstream::badbit); // Включаем генерацию исключений

            std::getline(file, tempLine);
            if (tempLine == "0") type.push_back("SSD");
            else type.push_back("HDD");
            file.close();

        }
    }
    catch (const std::exception& e) {
        // Показываем ошибку в диалоговом окне
        QMessageBox::critical(nullptr,
                              "Ошибка",
                              QString("Не удалось обработать файл:\n%1\n\nПричина: %2")
                                  .arg("/sys/block/название_накопителя/queue/rotational")
                                  .arg(e.what()));
        type.push_back("Ошибка отображения типа накопителя");
    }

    try {
        std::string tempLine;
        for (int i = 0; i < disks.size(); ++i){
            std::ifstream file("/sys/block/" + disks[i].toStdString() + "/size");
            file.exceptions(std::ifstream::badbit); // Включаем генерацию исключений

            std::getline(file, tempLine);
            volume.push_back(QString::number(stoi(tempLine)* 512 / 1024 / 1024 / 1024));

            file.close();
        }
    }
    catch (const std::exception& e) {
        // Показываем ошибку в диалоговом окне
        QMessageBox::critical(nullptr,
                              "Ошибка",
                              QString("Не удалось обработать файл:\n%1\n\nПричина: %2")
                                  .arg("/sys/block/название_накопителя/size")
                                  .arg(e.what()));
        volume.push_back(0);
    }

}
*/

#include <dirent.h>
#include <fstream>
#include <stdexcept>

HardDisk::HardDisk() {
    QVector<QString> disks = listDisks();

    for (const QString& disk : disks) {
        try {
            DiskInfo info;
            info.name = getDiskModel(disk);
            info.type = getDiskType(disk);
            info.volumeGB = getDiskVolumeGB(disk);
            disksInfo.push_back(info);
        } catch (const std::exception& e) {
            showError(disk, e.what());
            disksInfo.push_back({"Ошибка чтения", "Неизвестно", 0});
        }
    }
}

QVector<QString> HardDisk::listDisks() const {
    QVector<QString> disks;
    DIR* dir = opendir("/sys/block");
    if (!dir) {
        throw std::runtime_error("Не удалось открыть директорию /sys/block");
    }

    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        QString name = entry->d_name;
        if (name != "." && name != ".." && !name.startsWith("loop") && !name.startsWith("zram") && !name.startsWith("ram")) {
            disks.push_back(name);
        }
    }
    closedir(dir);
    return disks;
}

QString HardDisk::readFirstLineFromFile(const QString& path) const {
    std::ifstream file(path.toStdString());
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл");
    }

    std::string line;
    std::getline(file, line);
    return QString::fromStdString(line).trimmed();
}

QString HardDisk::getDiskModel(const QString& diskName) const {
    QString path = QString("/sys/block/%1/device/model").arg(diskName);
    return readFirstLineFromFile(path);
}

QString HardDisk::getDiskType(const QString& diskName) const {
    QString path = QString("/sys/block/%1/queue/rotational").arg(diskName);
    QString value = readFirstLineFromFile(path);
    return (value == "0") ? "SSD" : "HDD";
}

int HardDisk::getDiskVolumeGB(const QString& diskName) const {
    QString path = QString("/sys/block/%1/size").arg(diskName);
    QString value = readFirstLineFromFile(path);
    bool ok;
    long long sectors = value.toLongLong(&ok);

    if (!ok) {
        throw std::runtime_error("Неверный формат размера диска");
    }

    // Размер в GB (512 байт * количество секторов / 1024^3)
    return static_cast<int>((sectors * 512LL) / (1024LL * 1024LL * 1024LL));
}

void HardDisk::showError(const QString& filePath, const QString& error) const {
    QMessageBox::critical(nullptr, "Ошибка",
                          QString("Не удалось обработать файл:\n%1\n\nПричина: %2").arg(filePath).arg(error));
}
