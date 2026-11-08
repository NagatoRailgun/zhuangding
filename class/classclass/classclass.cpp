#include "classclass.h"

ClassClass::ClassClass()
{
    clear();
}

void ClassClass::clear()
{
    setClassId(-1);
    setClassName("");
    setSelected(false);
    studentIdList.clear();
    studentListPoint = nullptr;
}

void ClassClass::setClassId( int id)
{
    classId = id;
}

void ClassClass::setClassName( QString name )
{
    className = name;
}

const int ClassClass::getClassId()
{
    return classId;
}

const QString ClassClass::getClassName()
{
    return className;
}

const int ClassClass::getStudentNum()
{
    return studentIdList.count();
}

QList<QString> ClassClass::getStudentNames()
{
    QList<QString>list;
    for(int i = 0; i<studentListPoint->count(); i++){
        for(int j = 0; j<studentIdList.count(); j++){
            if(studentIdList[j] == (*studentListPoint)[i].getStudentId()){
                list.push_back((*studentListPoint)[i].getStudentName());
                break;
            }
        }
    }
    return list;
}

QList<int> ClassClass::getStudentIds()
{
    return studentIdList;
}

QString ClassClass::getStudentName(int studentId)
{
    for(int i = 0; i<studentListPoint->count(); i++){
        if((*studentListPoint)[i].getStudentId() == studentId){
            return (*studentListPoint)[i].getStudentName();
        }
    }
    return "";
}

void ClassClass::setStudentListPoint(QList<StudentClass> * point)
{
    studentListPoint = point;
    for (int i = 0;  i< studentListPoint->count(); i++) {
        if((*studentListPoint)[i].getClassId()==classId){
            addStudent((*studentListPoint)[i].getStudentId());
        }
    }
}

void ClassClass::setSelected(bool isSelected)
{
    selected = isSelected;
}

const int ClassClass::getSelected()
{
    return selected;
}

void ClassClass::printfStudents()
{
    QString name;
    qDebug()<<className<<":";
    for(int i = 0 ;i<studentIdList.count();i++){
        for(int j = 0;  j< studentListPoint->count(); j++){
            if((*studentListPoint)[j].getStudentId() == studentIdList[i]){
                name = (*studentListPoint)[j].getStudentName();
                qDebug()<<name;
                break;
            }
        }
        if(i<studentIdList.count()-1){
            qDebug()<<",";
        }
    }
}

int ClassClass::addStudent(int studentId)
{
    for(int i = 0;i<studentIdList.count();i++){
        if(studentIdList[i] == studentId){
            return 1;
        }
    }
    studentIdList.push_back(studentId);
    return 0;
}
