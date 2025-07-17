#ifndef MEM_H
#define MEM_H
#include <QString>
#include "/home/mushroom/Проекты/C++/SystemCheck/Include/FileReader.h"

class RAM{

private:
    QString memTotal;
    QString memFree;
    QString swapTotal;
    QString swapFree;
    QVector<QString> path;
    FileReader *fileReader;
    QVector<QMap<QString, QString>> parsedFile;


    void loadRAMInfo();
    void takeInfoAboutTotalMemory();
    void takeInfoAboutFreeMemory();
    QString stringFromKilobytesToGigabytes(double kiloBytes, short numbersAfterDecimalPoint) const;

public:
    RAM();

    QString getMemTotal() const {return memTotal;};
    QString getMemFree();
    QString getSwapTotal() const {return swapTotal;};
    QString getSwapFree();

};



#endif // MEM_H
