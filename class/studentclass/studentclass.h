#ifndef STUDENTCLASS_H
#define STUDENTCLASS_H

#include<QString>
#include<QDateTime>

class StudentClass
{
public:
    typedef enum{
        GENDER_STATUS_MALE,         //男生
        GENDER_STATUS_FEMALE,       //女生
    }GENDER_STATUS;
public:
    StudentClass();
    void setStudentId(int id);
    void setStudentShowId(int id);
    void setClassId(int id);
    void setStudentName(QString name);
    void setStudentGender(GENDER_STATUS gender);
    void setStudentGender(int gender);
    void setSelectedDateime(QDateTime time);
    void setSelectedTimes(int times);
    void setSelectLevel(int level);
    const int getStudentId();
    const int getStudentShowId();
    const int getClassId();
    const QString getStudentName();
    const GENDER_STATUS getStudentGender();
    const int getSelectedTimes();
    const QDateTime getSelectedDateTime();
    const int getSelectLevel();
private:
    int studentId;//系统id
    int studentShowId;//学号
    int classId;//班级系统id
    int selectedTimes;//累计选中次数
    int selectLevel;//优先级
    QString studentName;//姓名
    GENDER_STATUS studentGender;//性别
    QDateTime selectedDatetime;//上次被选时间
};

#endif // STUDENTCLASS_H
