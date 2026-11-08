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
    int getClassIdByName(QString className);
    QList<int> getAllClassId();
    ClassClass getClassData(int classId);
    QList<int> getNowStudentId(bool(*check)(StudentClass) = nullptr);
    QList<QString> getNowClassStudentName();
    QString getStudentName(int studentId);
    int getStudentShowId(int studentId);
    int getFreeClassId();
    int getFreeStudentId();
    void addClass(ClassClass newClass,QList<StudentClass>newStudent);
    void editClass(int classId,ClassClass newClass,QList<StudentClass>newStudent);
    void deleteClass(int classId);
    void editClassName(int classId,QString className);
    QString getAllDataToJson();
    bool checkClassEmpty();
    void countSelect(int studentId);
    StudentClass getStudentDataById(int studentId);
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
    void signalClassChange();
};

#endif // STUDENTSERVICE_H
