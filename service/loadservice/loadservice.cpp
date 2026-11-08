#include "loadservice.h"
#include "xlsxdocument.h"
#include "xlsxcellrange.h"
#include "studentservice/studentservice.h"
#include "fileservice/fileservice.h"

using namespace QXlsx;

LoadService::LoadService(QObject *parent)
    : BasicService{parent}
{
    serviceName = tr("Load Service");
    if(!instance){
        instance = this;
        qDebug()<<"["<<serviceName<<"]"<<tr("service started");
    }
}

LoadService::~LoadService(){
    instance = nullptr;
    qDebug()<<"["<<serviceName<<"]"<<tr("service closed");
}

LoadService * LoadService::getInstance(QObject * parent){
    if(instance){
        return instance;
    }
    return new LoadService(parent);
}

LoadService * LoadService::instance = nullptr;


void LoadService::afterInitService(){

}

void LoadService::beforeCloseService(){
    qDebug()<<"["<<serviceName<<"]"<<tr("service closing");
}

void LoadService::cleanWaitingData()
{
    loadClass.clear();
    loadStudentList.clear();
}

void LoadService::loadExcel(QString className,QString path)
{
    int row,col;
    int num;
    QXlsx::Document xlsx(path);
    std::shared_ptr<QXlsx::Cell>cell ;
    std::shared_ptr<QXlsx::Cell>cellTitile ;

    cleanWaitingData();
    loadClass.setClassName(className);

    qDebug()<<"["<<serviceName<<"]"<<tr("load excel:")<<path;
    row = xlsx.dimension().lastRow();
    col  = xlsx.dimension().lastColumn();
    if(row<0 || col<0){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to load excel:")<<path;
        return;
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("row:")<<row<<";"<<tr("col:")<<col;
    num = 0;
    for(int i = 2; i<=row; i++){
        StudentClass student;
        for(int j = 1; j<=col; j++){
            cellTitile = xlsx.cellAt( 1,j);
            cell = xlsx.cellAt( i,j);
            if(!cell){
                continue;
            }
            qDebug()<<"["<<serviceName<<"]("<<j<<","<<i<<"):"<<cell->value();
            if(cellTitile->value().toString() == "学号" || cellTitile->value().toString() == "编号" || cellTitile->value().toString() == "ID"){
                student.setStudentShowId(cell->value().toInt());
            }else if(cellTitile->value().toString() == "姓名"){
                student.setStudentName(cell->value().toString());
            }else if(cellTitile->value().toString() == "性别"){
                if(cell->value().toString() == "男"){
                    student.setStudentGender(StudentClass::GENDER_STATUS_MALE);
                }else{
                    student.setStudentGender(StudentClass::GENDER_STATUS_FEMALE);
                }
            }else if(cellTitile->value().toString() == "优先级"){
                student.setSelectLevel(cell->value().toInt());
            }
        }
        if(!student.getStudentName().isEmpty()){
            loadStudentList.append(student);
        }
        num++;
    }
    if(num){
        //待保存class数据的id一旦置为0就意味着生效
        loadClass.setClassId(0);
    }
    qDebug()<<"["<<serviceName<<"]"<<loadStudentList.size()<<" "<<tr("students has been loaded");
}

void LoadService::deleteClass(QString className)
{
    qDebug()<<"["<<serviceName<<"]"<<tr("start delete class:")<<className;
    int classId = StudentService::getInstance()->getClassIdByName(className);
    if(classId<0){
        qDebug()<<"["<<serviceName<<"]"<<tr("no class has been find");
        return;
    }
    StudentService::getInstance()->deleteClass(classId);
}

void LoadService::saveClass(QString className)
{
    qDebug()<<"["<<serviceName<<"]"<<tr("start save class:")<<className;
    int classId = StudentService::getInstance()->getClassIdByName(className);
    if(classId<0){
        qDebug()<<"["<<serviceName<<"]"<<tr("start add class:")<<className;
    }else{
        qDebug()<<"["<<serviceName<<"]"<<tr("start edit class:")<<className;
    }
    if(loadClass.getClassId()<0){
        qDebug()<<"["<<serviceName<<"]"<<tr(" no class data has been loaded");
        return;
    }
    loadClass.setClassName(className);
    if(classId<0){
        StudentService::getInstance()->addClass(loadClass,loadStudentList);
    }else{
        StudentService::getInstance()->editClass(classId,loadClass,loadStudentList);
    }
    cleanWaitingData();
    FileService::getInstance()->saveData();
}
