#ifndef FILESERVICE_H
#define FILESERVICE_H

#include "basicservice/basicservice.h"

class FileService : public BasicService
{
    Q_OBJECT
public:
    ~FileService();
    static FileService *  getInstance(QObject * parent  = nullptr);
    void afterInitService() override;
    void beforeCloseService() override;
    void saveData();
    void saveOption();
    bool checkDataFile();
    bool checkOptionFile();
    QByteArray loadData();
    QByteArray loadOption();
private:
    static FileService * instance;
private:
    explicit FileService(QObject *parent = nullptr);
    void saveDataToFile(QString dataJsonString,QString fileName,bool isEmpty);
    QByteArray loadDataFromFile(QString fileName);
    bool checkFileExsit(QString fileName);
signals:
};
#endif // FILESERVICE_H
