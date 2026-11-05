#include "histroyservice.h"
#include "studentservice/studentservice.h"

HistroyService::HistroyService(QObject *parent)
    : BasicService{parent}
{
    serviceName = tr("Histroy Service");
    if(!instance){
        instance = this;
        qDebug()<<"["<<serviceName<<"]"<<tr("service started");
    }
}

HistroyService::~HistroyService(){
    instance = nullptr;
    qDebug()<<"["<<serviceName<<"]"<<tr("service closed");
}

HistroyService * HistroyService::getInstance(QObject * parent){
    if(instance){
        return instance;
    }
    return new HistroyService(parent);
}

HistroyService * HistroyService::instance = nullptr;


void HistroyService::afterInitService(){

}

void HistroyService::beforeCloseService(){
    qDebug()<<"["<<serviceName<<"]"<<tr("service closing");
}

QList<StudentClass> HistroyService::getHistroyData(DATA_TYPE type)
{
    QList<int > students;
    QList<StudentClass> data;
    if(type == DATA_TYPE_ALL){
        students = StudentService::getInstance()->getNowStudentId();
    }else if(type == DATA_TYPE_MALE){
        students = StudentService::getInstance()->getNowStudentId([](StudentClass student)->bool{
            if(student.getStudentGender() == StudentClass::GENDER_STATUS_MALE){
                return true;
            }
            return false;
        });
    }else if(type == DATA_TYPE_FEMALE){
        students = StudentService::getInstance()->getNowStudentId([](StudentClass student)->bool{
            if(student.getStudentGender() == StudentClass::GENDER_STATUS_FEMALE){
                return true;
            }
            return false;
        });
    }else if(type == DATA_TYPE_SELECTED){
        students = StudentService::getInstance()->getNowStudentId([](StudentClass student)->bool{
            if(student.getSelectedTimes()){
                return true;
            }
            return false;
        });
    }else if(type == DATA_TYPE_UNSELECTED){
        students = StudentService::getInstance()->getNowStudentId([](StudentClass student)->bool{
            if(!student.getSelectedTimes()){
                return true;
            }
            return false;
        });
    }
    for(int i = 0;i<students.count();i++){
        data.push_back(StudentService::getInstance()->getStudentDataById(students[i]));
    }
    return data;
}
