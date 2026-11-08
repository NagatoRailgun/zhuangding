#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "studentservice.h"
#include "fileservice/fileservice.h"

StudentService::StudentService(QObject *parent)
    : BasicService{parent}
{
    serviceName = tr("Student Service");
    if(!instance){
        instance = this;
        qDebug()<<"["<<serviceName<<"]"<<tr("service started");
    }
}

StudentService::~StudentService(){
    instance = nullptr;
    qDebug()<<"["<<serviceName<<"]"<<tr("service closed");
}

StudentService * StudentService::getInstance(QObject * parent){
    if(instance){
        return instance;
    }
    return new StudentService(parent);
}

StudentService * StudentService::instance = nullptr;


void StudentService::afterInitService(){
    if(FileService::getInstance()->checkSaveFile()){
        qDebug()<<"["<<serviceName<<"]"<<tr("save data existed");
        loadFileData();
        return;
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("save data not exist");
    loadTestClass();
    loadTestStudent();
    setNowClassId(0);
}

void StudentService::beforeCloseService(){
    qDebug()<<"["<<serviceName<<"]"<<tr("service closing");
}

int StudentService::setNowClassId(int id)
{
    int exitFlag = 0;
    for(int i = 0;i<classList.count();i++){
        classList[i].setSelected(false);
    }
    for(int i = 0;i<classList.count();i++){
        if(classList[i].getClassId() == id){
            nowClassId = id;
            classList[i].setSelected(true);
            qDebug()<<"["<<serviceName<<"]"<<tr("set now class id:")<<nowClassId<<","<<tr("name:")<<classList[i].getClassName();
            emit signalNowClassChange(nowClassId);
            exitFlag = 1;
        }else{
            classList[i].setSelected(false);
        }
    }
    if(exitFlag){
        return 0;
    }
    if(classList.count()){
        nowClassId = classList[0].getClassId();
        classList[0].setSelected(true);
        qDebug()<<"["<<serviceName<<"]"<<tr("set now class id:")<<nowClassId<<","<<tr("empty class");
        emit signalNowClassChange(nowClassId);
        return 0;
    }
    nowClassId = -1;
    emit signalNowClassChange(nowClassId);
    return 1;
}

const int StudentService::getNowClassId()
{
    return nowClassId;
}

QList<int> StudentService::getAllClassId()
{
    QList<int> ids;
    for(int i = 0;i<classList.count();i++){
        ids.push_back(classList[i].getClassId());
    }
    return ids;
}

ClassClass StudentService::getClassData(int classId)
{
    ClassClass data;
    for(int i = 0;i<classList.count();i++){
        if(classList[i].getClassId() == classId){
            data = classList[i];
            return data;
        }
    }
    return data;
}

const QString StudentService::getNowClassName()
{
    for(int i = 0;i<classList.count();i++){
        if(classList[i].getClassId() == nowClassId){
            return classList[i].getClassName();
        }
    }
    return tr("Unselected");
}

int StudentService::getClassIdByName(QString className)
{
    int id = -1;
    for(int i = 0;i<classList.count();i++){
        if(classList[i].getClassName() == className){
            return classList[i].getClassId();
        }
    }
    return id;
}

const int StudentService::getNowStudentNum()
{
    for(int i = 0;i<classList.count();i++){
        if(classList[i].getClassId() == nowClassId){
            return classList[i].getStudentNum();
        }
    }
    return 0;
}

QList<int> StudentService::getNowStudentId(bool(*check)(StudentClass))
{
    QList<int>list;
    for(int i = 0;i<studentList.count();i++){
        if(studentList[i].getClassId() != nowClassId){
            continue;
        }
        if(check){
            if(!check(studentList[i])){
                continue;
            }
        }
        list.push_back(studentList[i].getStudentId());
    }
    return list;
}

int StudentService::getFreeClassId()
{
    int nId = 0;
    int nflag = 0;
    while(nId<2000){
        nflag = 0;
        for(int i = 0;i<classList.count();i++){
            if(classList[i].getClassId() == nId){
                nflag = 1;
                break;
            }
        }
        if(!nflag){
            return nId;
        }
        nId++;
    }
    return -1;
}

int StudentService::getFreeStudentId()
{
    int nId = 0;
    int exitFlag = 0;
    while(nId<5000){
        exitFlag = 0;
        for(int i = 0;i<studentList.count();i++){
            if(studentList[i].getStudentId() == nId){
                exitFlag = 1;
                break;
            }
        }
        if(!exitFlag){
            return nId;
        }
        nId++;
    }
    return -1;
}

QList<QString> StudentService::getNowClassStudentName()
{
    QList<QString>list;
    for(int i = 0;i<classList.count();i++){
        if(classList[i].getClassId() == nowClassId){
            return classList[i].getStudentNames();
        }
    }
    return list;
}

QString StudentService::getStudentName(int studentId)
{
    for(int i = 0;i<studentList.count();i++){
        if(studentList[i].getStudentId() == studentId){
            return studentList[i].getStudentName();
        }
    }
    return "";
}

int StudentService::getStudentShowId(int studentId)
{
    for(int i = 0;i<studentList.count();i++){
        if(studentList[i].getStudentId() == studentId){
            return studentList[i].getStudentShowId();
        }
    }
    return -1;
}

void StudentService::addClass(ClassClass newClass,QList<StudentClass>newStudent)
{
    int classId = getFreeClassId();
    int studentId = getFreeStudentId();
    int pos = classList.count();
    qDebug()<<"["<<serviceName<<"]"<<tr("add class:")<<newClass.getClassName()<<","<<tr("id:")<<classId;
    newClass.setClassId(classId);
    newClass.setClassName(newClass.getClassName());
    classList.push_back(newClass);
    for(int i = 0;i<newStudent.count();i++){
        newStudent[i].setStudentId(studentId + i);
        newStudent[i].setClassId(classId);
        studentList.push_back(newStudent[i]);
    }
    classList[pos].setStudentListPoint(&studentList);
    setNowClassId(newClass.getClassId());
    emit signalClassChange();
}

void StudentService::editClass(int classId,ClassClass newClass,QList<StudentClass>newStudent)
{
    qDebug()<<"["<<serviceName<<"]"<<tr("edit class id:")<<classId;
    deleteClass(classId);
    addClass(newClass,newStudent);
    setNowClassId(nowClassId);
    emit signalClassChange();
}

void StudentService::deleteClass(int classId)
{
    bool existFlag;
    ClassClass data;
    int count;
    qDebug()<<"["<<serviceName<<"]"<<tr("delete class id:")<<classId;
    existFlag = false;
    for(int i = 0;i<classList.count();i++){
        if(classList[i].getClassId() == classId){
            data = classList[i];
            classList.remove(i);
            existFlag = true;
            i--;
            break;
        }
    }
    if(!existFlag){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to find class by id:")<<classId;
        return;
    }
    count = 0;
    for(int i = 0;i<studentList.count();i++){
        if(studentList[i].getClassId() == classId){
            studentList.remove(i);
            i--;
            count++;
        }
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("delete class:")<<data.getClassName()<<","<<tr("with ")<<count<<tr(" students");
    if(nowClassId == classId){
        setNowClassId(0);
    }
    emit signalClassChange();
}

bool StudentService::checkClassEmpty()
{
    if(classList.count()){
        return false;
    }
    return true;
}

QString StudentService::getAllDataToJson()
{
    QJsonDocument ret;
    QJsonObject data;
    QJsonArray classArray;
    QJsonArray studentArray;
    for (int i = 0; i < classList.count(); ++i) {
        QJsonObject classItem;
        classItem.insert("classId",classList[i].getClassId());
        classItem.insert("selected",classList[i].getSelected());
        classItem.insert("className",classList[i].getClassName());
        classArray.append(classItem);
    }
    data.insert("class",classArray);
    for (int i = 0; i < studentList.count(); ++i) {
        QJsonObject studentItem;
        studentItem.insert("studentId",studentList[i].getStudentId());
        studentItem.insert("studentShowId",studentList[i].getStudentShowId());
        studentItem.insert("classId",studentList[i].getClassId());
        studentItem.insert("selectedTimes",studentList[i].getSelectedTimes());
        studentItem.insert("selectLevel",studentList[i].getSelectLevel());
        studentItem.insert("studentGender",studentList[i].getStudentGender());
        studentItem.insert("studentName",studentList[i].getStudentName());
        studentItem.insert("selectedDatetime",studentList[i].getSelectedDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        studentArray.append(studentItem);
    }
    data.insert("student",studentArray);
    ret.setObject(data);
    return QString::fromUtf8(ret.toJson(QJsonDocument::Compact));
}

void StudentService::loadFileData()
{
    QJsonObject dataObj;
    QJsonArray classArray;
    QJsonArray studentArray;
    QJsonDocument dt = QJsonDocument::fromJson(FileService::getInstance()->loadData());
    if(!dt.isObject()){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to load json data");
        return;
    }
    dataObj = dt.object();
    if(!dataObj["class"].isArray()){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to load class json data");
        return;
    }
    classArray = dataObj["class"].toArray();
    for(int i = 0;i<classArray.count();i++){
        if(!classArray[i].isObject()){
            continue;
        }
        QJsonObject obj = classArray[i].toObject();
        ClassClass classItem;
        classItem.setClassId(obj["classId"].toInt());
        classItem.setSelected(obj["selected"].toInt());
        classItem.setClassName(obj["className"].toString());
        classList.push_back(classItem);
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("load ")<<classList.count()<<tr(" class from json data");
    if(!dataObj["student"].isArray()){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to load student json data");
        return;
    }
    studentArray = dataObj["student"].toArray();
    for(int i = 0;i<studentArray.count();i++){
        if(!studentArray[i].isObject()){
            continue;
        }
        QJsonObject obj = studentArray[i].toObject();
        StudentClass studentItem;
        studentItem.setStudentId(obj["studentId"].toInt());
        studentItem.setStudentShowId(obj["studentShowId"].toInt());
        studentItem.setClassId(obj["classId"].toInt());
        studentItem.setSelectedTimes(obj["selectedTimes"].toInt());
        studentItem.setSelectLevel(obj["selectLevel"].toInt());
        studentItem.setStudentGender(obj["studentGender"].toInt());
        studentItem.setStudentName(obj["studentName"].toString());
        studentItem.setSelectedDateime(QDateTime::fromString(obj["selectedDatetime"].toString(),"yyyy-MM-dd hh:mm:ss"));
        studentList.push_back(studentItem);
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("load ")<<studentList.count()<<tr(" student from json data");
    for(int i = 0;i<classList.count();i++){
        classList[i].setStudentListPoint(&studentList);
    }
    for(int i = 0;i<classList.count();i++){
        if(classList[i].getSelected()){
            setNowClassId(classList[i].getClassId());
            return;
        }
    }
    if(classList.count()){
        setNowClassId(classList[0].getClassId());
    }
}

void StudentService::countSelect(int studentId)
{
    for (int i = 0; i < studentList.count(); ++i) {
        if(studentList[i].getStudentId() == studentId){
            studentList[i].setSelectedTimes(studentList[i].getSelectedTimes()+1);
            studentList[i].setSelectedDateime(QDateTime::currentDateTime());
            break;
        }
    }
}

StudentClass StudentService::getStudentDataById(int studentId)
{
    StudentClass data;
    for (int i = 0; i < studentList.count(); ++i) {
        if(studentList[i].getStudentId() == studentId){
            return studentList[i];
        }
    }
    return data;
}

void StudentService::loadTestClass()
{
    ClassClass class1;
    class1.setClassId(getFreeClassId());
    class1.setClassName("Test Class");
    class1.setSelected(true);
    classList.push_back(class1);
}

void StudentService::loadTestStudent()
{
    StudentClass student1,student2,student3,student4,student5,student6,student7,student8,student9,student10,student11,student12;
    student1.setStudentId(getFreeStudentId());
    student1.setClassId(classList[0].getClassId());
    student1.setStudentName("赵匡胤");
    studentList.push_back(student1);

    student2.setStudentId(getFreeStudentId());
    student2.setClassId(classList[0].getClassId());
    student2.setStudentName("钱俶");
    studentList.push_back(student2);

    student3.setStudentId(getFreeStudentId());
    student3.setClassId(classList[0].getClassId());
    student3.setStudentName("孙权");
    studentList.push_back(student3);

    student4.setStudentId(getFreeStudentId());
    student4.setClassId(classList[0].getClassId());
    student4.setStudentName("周瑜");
    studentList.push_back(student4);

    student5.setStudentId(getFreeStudentId());
    student5.setClassId(classList[0].getClassId());
    student5.setStudentName("李商隐");
    student5.setStudentGender(StudentClass::GENDER_STATUS_FEMALE);
    studentList.push_back(student5);

    student6.setStudentId(getFreeStudentId());
    student6.setClassId(classList[0].getClassId());
    student6.setStudentName("吴道子");
    studentList.push_back(student6);

    student7.setStudentId(getFreeStudentId());
    student7.setClassId(classList[0].getClassId());
    student7.setStudentName("郑板桥");
    studentList.push_back(student7);

    student8.setStudentId(getFreeStudentId());
    student8.setClassId(classList[0].getClassId());
    student8.setStudentName("王昭君");
    student8.setStudentGender(StudentClass::GENDER_STATUS_FEMALE);
    studentList.push_back(student8);

    student9.setStudentId(getFreeStudentId());
    student9.setClassId(classList[0].getClassId());
    student9.setStudentName("冯锡范");
    studentList.push_back(student9);

    student10.setStudentId(getFreeStudentId());
    student10.setClassId(classList[0].getClassId());
    student10.setStudentName("陈霸先");
    studentList.push_back(student10);

    student11.setStudentId(getFreeStudentId());
    student11.setClassId(classList[0].getClassId());
    student11.setStudentName("谢道韫");
    student11.setStudentGender(StudentClass::GENDER_STATUS_FEMALE);
    studentList.push_back(student11);

    student12.setStudentId(getFreeStudentId());
    student12.setClassId(classList[0].getClassId());
    student12.setStudentName("李清照");
    student12.setStudentGender(StudentClass::GENDER_STATUS_FEMALE);
    studentList.push_back(student12);

    classList[0].setStudentListPoint(&studentList);
}
