#include<QRandomGenerator>
#include "catchservice.h"
#include "studentservice/studentservice.h"

CatchService::CatchService(QObject *parent)
    : BasicService{parent}
{
    serviceName = tr("Catch Service");
    if(!instance){
        instance = this;
        qDebug()<<"["<<serviceName<<"]"<<tr("service started");
    }
}

CatchService::~CatchService(){
    instance = nullptr;
    qDebug()<<"["<<serviceName<<"]"<<tr("service closed");
}

CatchService * CatchService::getInstance(QObject * parent){
    if(instance){
        return instance;
    }
    return new CatchService(parent);
}

CatchService * CatchService::instance = nullptr;


void CatchService::afterInitService()
{
    cleanWaitingData();
}

void CatchService::beforeCloseService(){
    qDebug()<<"["<<serviceName<<"]"<<tr("service closing");
}

void CatchService::cleanWaitingData()
{
    qDebug()<<"["<<serviceName<<"]"<<tr("clean waiting data");
    moreCatchflag = 0;
    selectedStudentIdList.clear();
    nowSelectedStudentIdList.clear();

    studentIdPool.clear();
    studentIdPool2.clear();
}

void CatchService::catch1Time()
{
    int rnum;
    int nStudentNum;

    moreCatchflag = 0;
    nowSelectedStudentIdList.clear();
    nStudentNum = StudentService::getInstance()->getNowStudentNum();
    studentIdPool = makeStudentIdPool();
    if(!nStudentNum){
        qDebug()<<"["<<serviceName<<"]"<<tr("no student");
        return;
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("1 time catch started");
    rnum = QRandomGenerator::global()->bounded(0,studentIdPool.count());
    qDebug()<<"["<<serviceName<<"]"<<tr("now student total:")<<nStudentNum;
    qDebug()<<"["<<serviceName<<"]"<<tr("make random number:")<<rnum;
    SelectStudentData catchData = makeCatchStudentData(studentIdPool[rnum],studentIdPool);
    nowSelectedStudentIdList.push_back(catchData);
    StudentService::getInstance()->countSelect(studentIdPool[rnum]);//抽中统计更新

    emit signalCatchStudent(0,nowSelectedStudentIdList[0].studentId);
}

void CatchService::catch1TimeRepeatless()
{
    int rnum;
    int nStudentNum;

    moreCatchflag = 0;
    nowSelectedStudentIdList.clear();
    nStudentNum = StudentService::getInstance()->getNowStudentNum();
    if(!nStudentNum){
        qDebug()<<"["<<serviceName<<"]"<<tr("no student");
        return;
    }
    if(!studentIdPool2.count()){
        //抽光就重新补充
        studentIdPool2 = makeStudentIdPool();
    }
    if(!studentIdPool2.count()){
        qDebug()<<"["<<serviceName<<"]"<<tr("no student");
        return;
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("1 time repeatless catch started");
    rnum = QRandomGenerator::global()->bounded(0,studentIdPool2.count());
    qDebug()<<"["<<serviceName<<"]"<<tr("now student total:")<<nStudentNum;
    qDebug()<<"["<<serviceName<<"]"<<tr("make random number:")<<rnum;
    SelectStudentData catchData = makeCatchStudentData(studentIdPool2[rnum],studentIdPool2);
    nowSelectedStudentIdList.push_back(catchData);
    StudentService::getInstance()->countSelect(studentIdPool2[rnum]);//抽中统计更新
    //抽到一个就把id池里的id丢掉
    studentIdPool2.remove(rnum);
    emit signalCatchStudent(0,nowSelectedStudentIdList[0].studentId);
}

void CatchService::catch10Times()
{
    int rnum;
    int nStudentNum;

    moreCatchflag = 0;
    nowSelectedStudentIdList.clear();
    nStudentNum = StudentService::getInstance()->getNowStudentNum();
    studentIdPool = makeStudentIdPool();
    if(!studentIdPool.count()){
        qDebug()<<"["<<serviceName<<"]"<<tr("no student");
        return;
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("10 times catch started");
    for(int i = 0; i<10; i++){
        rnum = QRandomGenerator::global()->bounded(0,studentIdPool.count());
        qDebug()<<"["<<serviceName<<"]"<<tr("now student total:")<<nStudentNum;
        qDebug()<<"["<<serviceName<<"]"<<tr("make ")<<(i+1)<<tr(" time random number:")<<rnum;
        SelectStudentData catchData = makeCatchStudentData(studentIdPool[rnum],studentIdPool);
        nowSelectedStudentIdList.push_back(catchData);
        StudentService::getInstance()->countSelect(studentIdPool[rnum]);//抽中统计更新
        //抽到一个就把id池里的id丢掉
        studentIdPool.remove(rnum);
    }
    emit signalCatchStudent(0,nowSelectedStudentIdList[0].studentId);
}

void CatchService::catchMoreStart()
{
    int rnum;
    int nStudentNum;

    nStudentNum = StudentService::getInstance()->getNowStudentNum();
    if(!nStudentNum){
        qDebug()<<"["<<serviceName<<"]"<<tr("no student");
        return;
    }
    if(!moreCatchflag){
        studentIdPool = makeStudentIdPool();
        nowSelectedStudentIdList.clear();
        moreCatchflag = 1;
        qDebug()<<"["<<serviceName<<"]"<<tr("more catch started");
    }
    if(!studentIdPool.count()){
        catchMoreEnd();
        return;
    }
    rnum = QRandomGenerator::global()->bounded(0,studentIdPool.count());
    qDebug()<<"["<<serviceName<<"]"<<tr("now student total:")<<nStudentNum;
    qDebug()<<"["<<serviceName<<"]"<<tr("make")<<nowSelectedStudentIdList.count()+1<<tr("time random number:")<<rnum;
    SelectStudentData catchData = makeCatchStudentData(studentIdPool[rnum],studentIdPool);
    nowSelectedStudentIdList.push_back(catchData);
    StudentService::getInstance()->countSelect(studentIdPool[rnum]);//抽中统计更新
    //抽到一个就把id池里的id丢掉
    studentIdPool.remove(rnum);

    emit signalCatchStudent(nowSelectedStudentIdList.count()-1,nowSelectedStudentIdList[nowSelectedStudentIdList.count()-1].studentId);
}

void CatchService::catchMoreEnd()
{
    if(moreCatchflag){
        nowSelectedStudentIdList.clear();
        qDebug()<<"["<<serviceName<<"]"<<tr("more catch ended");
        moreCatchflag = 0;
    }
}

void CatchService::addSelectStudentToList(int pos)
{
    int nStudentNum;
    if(pos<0 || pos>=nowSelectedStudentIdList.count()){
        qDebug()<<"["<<serviceName<<"]"<<tr("pos overflow:")<<pos;
        return;
    }
    if(!moreCatchflag){
        //普通抓取时
        qDebug()<<"["<<serviceName<<"]"<<tr("catch students add:")<<nowSelectedStudentIdList[pos].studentId;
        selectedStudentIdList.push_back(nowSelectedStudentIdList[pos]);
        emit signalCatchStudentAdd(nowSelectedStudentIdList[pos].studentId);
        if(pos < nowSelectedStudentIdList.count()-1){
            emit signalCatchStudent(pos+1,nowSelectedStudentIdList[pos+1].studentId);
        }
    }else{
        //持续抓取时
        nStudentNum = StudentService::getInstance()->getNowStudentNum();
        qDebug()<<"["<<serviceName<<"]"<<tr("catch students add:")<<nowSelectedStudentIdList[pos].studentId;
        selectedStudentIdList.push_back(nowSelectedStudentIdList[pos]);
        emit signalCatchStudentAdd(nowSelectedStudentIdList[pos].studentId);
        if(pos < nStudentNum){
            catchMoreStart();
        }
    }
}

QList<int> CatchService::makeStudentIdPool()
{
    QList<int> pool = StudentService::getInstance()->getNowStudentId();
    return pool;
}

QList<CatchService::SelectStudentData> CatchService::getSelectedStudentList()
{
    return selectedStudentIdList;
}

CatchService::SelectStudentData CatchService::makeCatchStudentData(int studentId,QList<int>idPool)
{
    SelectStudentData data;
    data.studentId = studentId;
    data.name = StudentService::getInstance()->getStudentName(studentId);
    data.chance = countChance(studentId,idPool);
    return data;
}

int CatchService::countChance(int studentId,QList<int>idPool)
{
    int count = 0;
    for(int i = 0;i<idPool.count();i++){
        if(idPool[i] == studentId ){
            count++;
        }
    }
    if(idPool.count()){
        count = count*10000/idPool.count();
    }else{
        count = 0;
    }
    return count;
}
