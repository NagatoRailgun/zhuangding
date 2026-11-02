#ifndef STUDENTSERVICE_H
#define STUDENTSERVICE_H

#include <QList>
#include "classclass/classclass.h"
#include "studentclass/studentclass.h"
#include "basicservice/basicservice.h"

class StudentService : public BasicService
{
Q_OBJECT
public:
    ~StudentService();
    static StudentService *  getInstance(QObject * parent  = nullptr);
    void afterInitService() override;
    void beforeCloseService() override;
    int setNowClassId(int id);
    const int getNowClassId();
    const int getNowStudentNum();
    const QString getNowClassName();
    QList<int> getNowStudentId();
    QList<QString> getNowClassStudentName();
    QString getStudentName(int studentId);
    int getStudentShowId(int studentId);
    int getFreeClassId();
    int getFreeStudentId();
    void setNewClass(ClassClass newClass,QList<StudentClass>newStudent);
    QString getAllDataToJson();
    void countSelect(int studentId);
private:
    static StudentService * instance;
    QList<ClassClass> classList;
    QList<StudentClass>studentList;
    int nowClassId = -1;
private:
    explicit StudentService(QObject *parent = nullptr);
    void loadFileData();
    void loadTestClass();
    void loadTestStudent();
signals:
    void signalNowClassChange(int nowClassId);
};

#endif // STUDENTSERVICE_H
