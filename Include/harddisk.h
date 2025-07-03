#ifndef HARDDISK_H
#define HARDDISK_H

#include <QApplication>

class HardDisk {
private:
    QVector<QString> name;
    QVector<QString> type;
    QVector<QString> volume;



public:
    HardDisk();

    QString getName(int number) const { return name[number];}
    QString getType(int number) const { return type[number];}
    QString getVolume(int number) const { return volume[number];}


};
#endif // HARDDISK_H
