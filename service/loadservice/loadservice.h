#ifndef LOADSERVICE_H
#define LOADSERVICE_H

#include "basicservice/basicservice.h"
#include "classclass/classclass.h"
#include "studentclass/studentclass.h"

class LoadService : public BasicService
{
    Q_OBJECT
public:
    ~LoadService();
    static LoadService *  getInstance(QObject * parent  = nullptr);
    void afterInitService() override;
    void beforeCloseService() override;
    void loadExcel(QString className,QString path);
    void cleanWaitingData();
    void deleteClass(QString className);
    void saveClass(QString className);
private:
    static LoadService * instance;
    ClassClass loadClass;
    QList<StudentClass>loadStudentList;
private:
    explicit LoadService(QObject *parent = nullptr);
signals:
};
#endif // LOADSERVICE_H
