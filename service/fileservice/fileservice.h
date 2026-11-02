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
    bool checkSaveFile();
    QByteArray loadData();
private:
    static FileService * instance;
private:
    explicit FileService(QObject *parent = nullptr);
signals:
};
#endif // FILESERVICE_H
