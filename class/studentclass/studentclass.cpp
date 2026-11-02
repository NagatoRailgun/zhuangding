#include "studentclass.h"

StudentClass::StudentClass()
{
    setStudentId(0);
    setStudentShowId(1);
    setClassId(0);
    setStudentGender(GENDER_STATUS_MALE);
    setSelectLevel(1);
    setSelectedTimes(0);
}

void StudentClass::setStudentId(int id)
{
    studentId = id;
}

void StudentClass::setStudentShowId(int id)
{
    studentShowId = id;
}

void StudentClass::setClassId(int id)
{
    classId = id;
}

void StudentClass::setStudentName(QString name)
{
    studentName = name;
}

void StudentClass::setStudentGender(GENDER_STATUS gender)
{
    studentGender = gender;
}

void StudentClass::setStudentGender(int gender){
    if(!gender){
        studentGender = GENDER_STATUS_MALE;
    }else{
        studentGender = GENDER_STATUS_FEMALE;
    }
}

void StudentClass::setSelectedDateime(QDateTime time)
{
    selectedDatetime = time;
}

void StudentClass::setSelectLevel(int level)
{
    selectLevel = level;
}

void StudentClass::setSelectedTimes(int times)
{
    selectedTimes = times;
}

const int StudentClass::getStudentId()
{
    return studentId;
}

const int StudentClass::getStudentShowId()
{
    return studentShowId;
}

const int StudentClass::getClassId()
{
    return classId;
}

const QString StudentClass::getStudentName()
{
    return studentName;
}

const StudentClass::GENDER_STATUS StudentClass::getStudentGender()
{
    return studentGender;
}

const int StudentClass::getSelectedTimes()
{
    return selectedTimes;
}

const QDateTime StudentClass::getSelectedDateTime()
{
    return selectedDatetime;
}

const int StudentClass::getSelectLevel()
{
    return selectLevel;
}

