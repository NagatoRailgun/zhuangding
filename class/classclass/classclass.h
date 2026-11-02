#ifndef CLASSCLASS_H
#define CLASSCLASS_H

#include <QString>
#include "studentclass/studentclass.h"

class ClassClass
{  
public:
    ClassClass();
    void setClassId( int id);
    void setClassName( QString name );
    void setStudentListPoint(QList<StudentClass> * point);
    void setSelected(bool isSelected);
    const int getClassId();
    const QString getClassName();
    QList<QString> getStudentNames();
    QList<int> getStudentIds();
    QString getStudentName(int studentId);
    const int getStudentNum();
    const int getSelected();
private:
    int classId;
    bool selected;
    QString className;
    QList<int> studentIdList;
    QList<StudentClass> * studentListPoint = nullptr;
private:
    int  addStudent(int studentId);
    void printfStudents();
};

#endif // CLASSCLASS_H
