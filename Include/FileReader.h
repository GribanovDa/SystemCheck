#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>
#include <QVector>
#include <QMap>

class FileReader{

private:
    QVector<QString> paths;                                         // Paths of files
    QMap<QString, QString> mapKeyValue;                             // Map that include key and value from file
    QVector<QMap<QString, QString>> parsedFiles;                     // Vector of parsed files, contains maps <key, value>

    void fileReaderInitialization(QVector<QString>& paths);
    void keyValueInit(std::ifstream& path);



public:
    FileReader(const QVector<QString>& importedPaths);
    QString readFirstLineFromFile(const QString& path) const;
    void parseInfoFromFileToMap(const std::string& line);
    QVector<QMap<QString, QString>> getRefreshedVectorOfParsedFiles();
    void refreshInfo();

};

#endif // FILEREADER_H
