#ifndef CATCHSERVICE_H
#define CATCHSERVICE_H

#include "basicservice/basicservice.h"

class CatchService : public BasicService
{
    Q_OBJECT
public:
    typedef struct {
        int studentId;
        QString name;
        int chance;
    }SelectStudentData;
public:
    ~CatchService();
    static CatchService *  getInstance(QObject * parent  = nullptr);
    void afterInitService() override;
    void beforeCloseService() override;
    void cleanWaitingData();
    void catch1Time();//单次可重复抽取
    void catch1TimeRepeatless();//单次不可重复抽取
    void catch10Times();//十连抽取
    void catchMoreStart();//批量抽取开始
    void catchMoreEnd();//批量抽取结束
    void addSelectStudentToList(int pos);
    QList<SelectStudentData> getSelectedStudentList();
private:
    static CatchService * instance;
    int  moreCatchflag = 0;
    QList<SelectStudentData>selectedStudentIdList;
    QList<SelectStudentData>nowSelectedStudentIdList;
    QList<int>studentIdPool;//多次抽取池
    QList<int>studentIdPool2;//单次不可重复抽取专用池
private:
    explicit CatchService(QObject *parent = nullptr);
    QList<int> makeStudentIdPool();//做成学生id抽取池
    SelectStudentData makeCatchStudentData(int studentId,QList<int>idPool);
    int countChance(int studentId,QList<int>idPool);
signals:
    void signalCatchStudent(int pos,int studentId);
    void signalCatchStudentAdd(int studentId);
};

#endif // CATCHSERVICE_H
