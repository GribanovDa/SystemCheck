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
    void parseRAMInfoLine(const std::string& line);
    std::string stringFromKilobytesToGigabytes(double kiloBytes);

public:
    RAM();

    QString getMemTotal() const {return memTotal;};
    QString getMemFree() const {return memFree;};
    QString getSwapTotal() const {return swapTotal;};
    QString getSwapFree() const {return swapFree;};

};



#endif // MEM_H
