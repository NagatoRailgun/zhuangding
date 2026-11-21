#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include<QRandomGenerator>
#include "catchservice.h"
#include "studentservice/studentservice.h"
#include "optionservice/optionservice.h"
#include "fileservice/fileservice.h"

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
    loadFileData(studentIdPool2);
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
    studentIdPool = makeStudentIdPool(false);
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
    OptionClass opt = OptionService::getInstance()->getOption();
    if(opt.getInheritRepeat()==OptionClass::INHERITREPEAT_TYPETYPE_ABLE){
        StudentService::getInstance()->countSelect(studentIdPool[rnum]);//抽中统计更新
    }
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
        studentIdPool2 = makeStudentIdPool(false);
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
    OptionClass opt = OptionService::getInstance()->getOption();
    if(opt.getInheritRepeat()==OptionClass::INHERITREPEAT_TYPETYPE_ABLE){
        StudentService::getInstance()->countSelect(studentIdPool2[rnum]);//抽中统计更新
    }
    //抽到一个就把id池里的id丢掉
    studentIdPool2 = removeIdfromPool(studentIdPool2[rnum],studentIdPool2);
    emit signalCatchStudent(0,nowSelectedStudentIdList[0].studentId);
}

void CatchService::catch10Times()
{
    int rnum;
    int nStudentNum;

    moreCatchflag = 0;
    nowSelectedStudentIdList.clear();
    nStudentNum = StudentService::getInstance()->getNowStudentNum();
    studentIdPool = makeStudentIdPool(false);
    if(!studentIdPool.count()){
        qDebug()<<"["<<serviceName<<"]"<<tr("no student");
        return;
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("10 times catch started");
    for(int i = 0; i<10 && studentIdPool.count(); i++){
        rnum = QRandomGenerator::global()->bounded(0,studentIdPool.count());
        qDebug()<<"["<<serviceName<<"]"<<tr("now student total:")<<nStudentNum;
        qDebug()<<"["<<serviceName<<"]"<<tr("make ")<<(i+1)<<tr(" time random number:")<<rnum;
        SelectStudentData catchData = makeCatchStudentData(studentIdPool[rnum],studentIdPool);
        nowSelectedStudentIdList.push_back(catchData);
        OptionClass opt = OptionService::getInstance()->getOption();
        if(opt.getInheritRepeat()==OptionClass::INHERITREPEAT_TYPETYPE_ABLE){
            StudentService::getInstance()->countSelect(studentIdPool[rnum]);//抽中统计更新
        }
        //抽到一个就把id池里的id丢掉
        studentIdPool = removeIdfromPool(studentIdPool[rnum],studentIdPool);
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
        studentIdPool = makeStudentIdPool(false);
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
    OptionClass opt = OptionService::getInstance()->getOption();
    if(opt.getInheritRepeat()==OptionClass::INHERITREPEAT_TYPETYPE_ABLE){
        StudentService::getInstance()->countSelect(studentIdPool[rnum]);//抽中统计更新
    }
    //抽到一个就把id池里的id丢掉
    studentIdPool = removeIdfromPool(studentIdPool[rnum],studentIdPool);

    emit signalCatchStudent(nowSelectedStudentIdList.count()-1,nowSelectedStudentIdList[nowSelectedStudentIdList.count()-1].studentId);
}

QList<int> CatchService::removeIdfromPool(int studentId,QList<int>idPool)
{
    for(int i = 0;i<idPool.count();i++){
        if(idPool[i] == studentId){
            idPool.removeAt(i);
            i--;
        }
    }
    return idPool;
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

QList<int> CatchService::makeStudentIdPool(bool needCatchTimesCheckFlag)
{
    OptionClass opt = OptionService::getInstance()->getOption();
    QList<int> pool = StudentService::getInstance()->getNowStudentId();
    QList<int> pool2;
    QList<CatchWeight> selectWeightList;
    QList<CatchWeight> levelWeightList;
    for(int i = 0;i<pool.count();i++){
        StudentClass data = StudentService::getInstance()->getStudentDataById(pool[i]);
        if(opt.getGender()==OptionClass::GENDER_TYPE_MALE && data.getStudentGender() != StudentClass::GENDER_STATUS_MALE){
            pool.removeAt(i);
            i--;
            continue;
        }else if(opt.getGender()==OptionClass::GENDER_TYPE_FEMALE && data.getStudentGender() != StudentClass::GENDER_STATUS_FEMALE){
            pool.removeAt(i);
            i--;
            continue;
        }
        makeWeightListMinCount(selectWeightList,data.getSelectedTimes(),data.getSelectedTimes());
        makeWeightListMinCount(levelWeightList,data.getSelectLevel(),data.getSelectedTimes());
    }
    //没有优先级设置的话直接退出
    if(!needCatchTimesCheckFlag ||
       (opt.getLevelPriority()!=OptionClass::PRIORITY_TYPE_ABLE &&
       opt.getCountPriority()!=OptionClass::PRIORITY_TYPE_ABLE)){
        return pool;
    }
    //计算权重
    for(int i = 0;i<pool.count();i++){
        StudentClass data = StudentService::getInstance()->getStudentDataById(pool[i]);
        makeWeightListWeight(selectWeightList,data.getSelectedTimes(),data.getSelectedTimes());
        makeWeightListWeight(levelWeightList,data.getSelectLevel(),data.getSelectedTimes());
    }
    //抽取次数越多被抽次数越少、优先级越高的学生抽中概率越大
    for(int i = 0;i<pool.count();i++){
        StudentClass data = StudentService::getInstance()->getStudentDataById(pool[i]);
        if(opt.getCountPriority()==OptionClass::PRIORITY_TYPE_ABLE){
            makeWeightPool(pool2,selectWeightList,data.getStudentId(),data.getSelectedTimes());
        }
        if(opt.getLevelPriority()==OptionClass::PRIORITY_TYPE_ABLE){
            makeWeightPool(pool2,levelWeightList,data.getStudentId(),data.getSelectLevel());
        }
    }
    pool = pool+pool2;
    return pool;
}

void CatchService::makeWeightPool(QList<int>&idPool,QList<CatchWeight>&list,int studentId,int keyNum)
{
    for(int i = 0;i<list.count();i++){
        if(list[i].keyNum != keyNum){
            continue;
        }
        for(int j = list[i].weight;j>0;j--){
            idPool.push_back(studentId);
        }
        break;
    }
}

void CatchService::makeWeightListMinCount(QList<CatchWeight>&list,int keyNumber,int selectTimes)
{
    int minweight = -1;
    bool existFlag = 0;
    for(int i = 0;i<list.count();i++){
        if(list[i].keyNum == keyNumber){
            existFlag = true;
            if(selectTimes<list[i].minCount){
                list[i].minCount = selectTimes;
            }
            break;
        }
    }
    if(!existFlag){
        CatchWeight weight;
        weight.weight = 0;
        weight.keyNum = keyNumber;
        weight.minCount = selectTimes;
        list.push_back(weight);
    }
}

void CatchService::makeWeightListWeight(QList<CatchWeight>&list,int keyNum,int selectTimes)
{
    for(int i = 0;i<list.count();i++){
        if(list[i].keyNum<keyNum){
            list[i].weight += selectTimes-list[i].minCount;
        }
    }
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

int CatchService::getCatchProbability(int studentId)
{
    int persent = 0;
    QList<int> pool = makeStudentIdPool(true);
    persent = countChance(studentId,pool);
    return persent;
}

QString CatchService::getAllDataToJson()
{
    QString data;
    int classId = StudentService::getInstance()->getNowClassId();
    data = updateFileData(classId,studentIdPool2);
    return data;
}

void CatchService::loadFileData(QList<int > &studentPool)
{
    QJsonArray dataArray;
    int classId = StudentService::getInstance()->getNowClassId();
    QJsonDocument dt = QJsonDocument::fromJson(FileService::getInstance()->loadCatch());
    OptionClass option = OptionService::getInstance()->getOption();
    if(!dt.isArray()){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to load json data");
        return;
    }
    if(classId<0){
        qDebug()<<"["<<serviceName<<"]"<<tr("no selected class");
        return;
    }
    dataArray = dt.array();
    for(int i = 0;i<dataArray.count();i++){
        if(!dataArray[i].isObject()){
            continue;
        }
        QJsonObject dataItem = dataArray[i].toObject();
        if(dataItem["classId"].toInt() != classId){
            continue;
        }
        if(dataItem["gender"].toInt() != option.getGender()){
            continue;
        }
        QJsonArray studentIdArray = dataItem["studentId"].toArray();
        for(int j = 0;j<studentIdArray.count();j++){
            studentPool.push_back(studentIdArray[j].toInt());
        }
    }
    for(int i = 0;i<studentPool.count();i++){
        if(StudentService::getInstance()->checkStudentExist(studentPool[i])){
            continue;
        }
        studentPool.remove(i);
        i--;
    }
}

QString CatchService::updateFileData(int classId,QList<int > &studentPool)
{
    QJsonArray ndataArray;
    QJsonDocument dt = QJsonDocument::fromJson(FileService::getInstance()->loadCatch());
    QJsonObject ndataItem;
    QJsonArray studentArray;
    OptionClass option = OptionService::getInstance()->getOption();
    bool existFlag;
    if(classId<0){
        return "";
    }
    ndataItem.insert("classId",classId);
    ndataItem.insert("gender",option.getGender());
    for(int i = 0;i<studentPool.count();i++){
        studentArray.append(studentPool[i]);
    }
    ndataItem.insert("studentId",studentArray);

    if(!dt.isArray()){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to load json data");

        ndataArray.append(ndataItem);
        dt.setArray(ndataArray);
        return QString::fromUtf8(dt.toJson(QJsonDocument::Compact));
    }
    QJsonArray dataArray = dt.array();
    existFlag = false;
    for(int i = 0;i<dataArray.count();i++){
        if(!dataArray[i].isObject()){
            continue;
        }
        QJsonObject dataItem = dataArray[i].toObject();
        if(dataItem["classId"] != StudentService::getInstance()->getNowClassId()){
            ndataArray.append(dataItem);
            continue;
        }
        existFlag = true;
        ndataArray.append(ndataItem);
    }
    if(!existFlag){
        ndataArray.append(ndataItem);
    }
    dt.setArray(ndataArray);
    return QString::fromUtf8(dt.toJson(QJsonDocument::Compact));
}

QString CatchService::deleteFileData(int classId)
{
    QJsonArray ndataArray;
    QJsonDocument dt = QJsonDocument::fromJson(FileService::getInstance()->loadCatch());
    if(!dt.isArray()){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to load json data");
        return "";
    }
    QJsonArray dataArray = dt.array();
    for(int i = 0;i<dataArray.count();i++){
        if(!dataArray[i].isObject()){
            continue;
        }
        QJsonObject dataItem = dataArray[i].toObject();
        if(dataItem["classId"] != StudentService::getInstance()->getNowClassId()){
            ndataArray.append(dataItem);
            continue;
        }
    }
    if(ndataArray.count()){
        dt.setArray(ndataArray);
        return QString::fromUtf8(dt.toJson(QJsonDocument::Compact));
    }else{
        return "";
    }
}

QString CatchService::getDeleteClassDataToJson(int classId)
{
    QString data;
    data = deleteFileData(classId);
    return data;

}
