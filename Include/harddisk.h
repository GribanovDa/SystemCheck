#ifndef HARDDISK_H
#define HARDDISK_H

#include <QVector>
#include <QString>
#include <QMessageBox>

class HardDisk {
public:
    HardDisk();

    struct DiskInfo {
        QString name;
        QString type;
        int volumeGB;
    };

    const QVector<DiskInfo>& getDisksInfo() const { return disksInfo; }

private:
    QVector<DiskInfo> disksInfo;

    QVector<QString> listDisks() const;
    QString readFirstLineFromFile(const QString& path) const;
    QString getDiskModel(const QString& diskName) const;
    QString getDiskType(const QString& diskName) const;
    int getDiskVolumeGB(const QString& diskName) const;
    void showError(const QString& filePath, const QString& error) const;
};

#endif // HARDDISK_H
