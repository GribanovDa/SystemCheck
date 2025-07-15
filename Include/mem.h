#ifndef MEM_H
#define MEM_H
#include <QString>
#include <string>

class RAM{

private:
    QString memTotal;
    QString memFree;
    QString swapTotal;
    QString swapFree;


    void loadRAMInfo();
    void parseRAMInfoLineForTotalMemory(const std::string& line);
    void parseRAMInfoLineForFreeMemory(const std::string& line);
    QString stringFromKilobytesToGigabytes(double kiloBytes, short numbersAfterDecimalPoint);

public:
    RAM();

    QString getMemTotal() const {return memTotal;};
    QString getMemFree() const {return memFree;};
    QString getSwapTotal() const {return swapTotal;};
    QString getSwapFree() const {return swapFree;};
    void refreshFreeMemory();

};



#endif // MEM_H
