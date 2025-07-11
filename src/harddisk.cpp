#include "/home/mushroom/Проекты/C++/SystemCheck/Include/harddisk.h"
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

    // Size(GB) (512 bytes * sectors / 1024^3)
    return static_cast<int>((sectors * 512LL) / (1024LL * 1024LL * 1024LL));
}

void HardDisk::showError(const QString& filePath, const QString& error) const {
    QMessageBox::critical(nullptr, "Ошибка",
                          QString("Не удалось обработать файл:\n%1\n\nПричина: %2").arg(filePath).arg(error));
}
