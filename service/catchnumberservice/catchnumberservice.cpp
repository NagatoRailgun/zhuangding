#include "catchnumberservice.h"

CatchNumberService::CatchNumberService(QObject *parent)
    : BasicService{parent}
{
    serviceName = tr("Catch Number Service");
    if(!instance){
        instance = this;
        qDebug()<<"["<<serviceName<<"]"<<tr("service started");
    }
}

CatchNumberService::~CatchNumberService(){
    instance = nullptr;
    qDebug()<<"["<<serviceName<<"]"<<tr("service closed");
}

CatchNumberService * CatchNumberService::getInstance(QObject * parent){
    if(instance){
        return instance;
    }
    return new CatchNumberService(parent);
}

CatchNumberService * CatchNumberService::instance = nullptr;

void CatchNumberService::initBasicData()
{

}

void CatchNumberService::afterInitService()
{

}

void CatchNumberService::beforeCloseService(){
    qDebug()<<"["<<serviceName<<"]"<<tr("service closing");
}

int CatchNumberService::getLastCatchStudentId()
{
    if(selectedStudentIdList.count()>0){
        return selectedStudentIdList[selectedStudentIdList.count()-1].studentId;
    }
    return -1;
}
