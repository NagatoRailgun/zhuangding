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
    for(int i = 0;i<classList.count();i++){
        classList[i].setSelected(false);
    }
    for(int i = 0;i<classList.count();i++){
        if(classList[i].getClassId() == id){
            nowClassId = id;
            classList[i].setSelected(true);
            qDebug()<<"["<<serviceName<<"]"<<tr("set now class id:")<<nowClassId<<","<<tr("name:")<<classList[i].getClassName();
            emit signalNowClassChange(nowClassId);
            return 0;
        }
    }
    if(classList.count()){
        nowClassId = classList[0].getClassId();
        classList[0].setSelected(true);
        qDebug()<<"["<<serviceName<<"]"<<tr("set now class id:")<<nowClassId<<","<<tr("empty class");
        emit signalNowClassChange(nowClassId);
        return 0;
    }
    return 1;
}

const int StudentService::getNowClassId()
{
    return nowClassId;
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

const int StudentService::getNowStudentNum()
{
    for(int i = 0;i<classList.count();i++){
        if(classList[i].getClassId() == nowClassId){
            return classList[i].getStudentNum();
        }
    }
    return 0;
}

QList<int> StudentService::getNowStudentId()
{
    QList<int>list;
    for(int i = 0;i<classList.count();i++){
        if(classList[i].getClassId() == nowClassId){
            return classList[i].getStudentIds();
        }
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
    int nflag = 0;
    while(nId<2000){
        nflag = 0;
        for(int i = 0;i<studentList.count();i++){
            if(studentList[i].getStudentId() == nId){
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

void StudentService::setNewClass(ClassClass newClass,QList<StudentClass>newStudent)
{
    int pos = classList.count();
    classList.push_back(newClass);
    for(int i = 0;i<newStudent.count();i++){
        studentList.push_back(newStudent[i]);
    }
    classList[pos].setStudentListPoint(&studentList);
    setNowClassId(newClass.getClassId());
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
        studentItem.setSelectedDateime(QDateTime::fromString(obj["selectedDatetime"].toString()));
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
