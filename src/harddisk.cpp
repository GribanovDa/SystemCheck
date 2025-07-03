#include "/home/mushroom/Проекты/C++/SystemCheck/Include/harddisk.h"
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
