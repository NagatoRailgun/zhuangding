#ifndef CATCHNUMBERSERVICE_H
#define CATCHNUMBERSERVICE_H

#include "basicservice/basicservice.h"

class CatchNumberService : public BasicService
{
    Q_OBJECT
public:
    typedef struct {
        int studentId;
        QString name;
        int chance;
    }SelectStudentData;
public:
    ~CatchNumberService();
    static CatchNumberService *  getInstance(QObject * parent  = nullptr);
    void initBasicData() override;
    void afterInitService() override;
    void beforeCloseService() override;
    int getLastCatchStudentId();
private:
    static CatchNumberService * instance;
    QList<SelectStudentData>selectedStudentIdList;
    QList<SelectStudentData>nowSelectedStudentIdList;
private:
    explicit CatchNumberService(QObject *parent = nullptr);
signals:
};
#endif // CATCHNUMBERSERVICE_H
