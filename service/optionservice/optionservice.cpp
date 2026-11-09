#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "optionservice.h"
#include "fileservice/fileservice.h"

OptionService::OptionService(QObject *parent)
    : BasicService{parent}
{
    serviceName = tr("Option Service");
    if(!instance){
        instance = this;
        qDebug()<<"["<<serviceName<<"]"<<tr("service started");
    }
}

OptionService::~OptionService(){
    instance = nullptr;
    qDebug()<<"["<<serviceName<<"]"<<tr("service closed");
}

OptionService * OptionService::getInstance(QObject * parent){
    if(instance){
        return instance;
    }
    return new OptionService(parent);
}

OptionService * OptionService::instance = nullptr;


void OptionService::afterInitService()
{
    if(FileService::getInstance()->checkOptionFile()){
        qDebug()<<"["<<serviceName<<"]"<<tr("save data existed");
        loadFileData();
        return;
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("save data not exist");
    initOption();
}

void OptionService::beforeCloseService()
{
    qDebug()<<"["<<serviceName<<"]"<<tr("service closing");
}

void OptionService::initOption()
{
    options.setPriority(OptionClass::PRIORITY_TYPE_RANDOM);
    options.setInheritRepeat(OptionClass::INHERITREPEAT_TYPETYPE_ABLE);
    options.setGender(OptionClass::GENDER_TYPE_ALL);
}

void OptionService::setOption(OptionClass opt)
{
    options = opt;
    qDebug()<<"["<<serviceName<<"]"<<tr("start save option");
    FileService::getInstance()->saveOption();
}

OptionClass OptionService::getOption()
{
    return options;
}

QString OptionService::getAllDataToJson()
{
    QJsonDocument ret;
    QJsonObject data;
    data.insert("priority",options.getPriority());
    data.insert("inheritRepeat",options.getInheritRepeat());
    data.insert("gender",options.getGender());
    ret.setObject(data);
    return QString::fromUtf8(ret.toJson(QJsonDocument::Compact));
}

void OptionService::loadFileData()
{
    QJsonObject dataObj;
    QJsonDocument dt = QJsonDocument::fromJson(FileService::getInstance()->loadOption());
    if(!dt.isObject()){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to load json data");
        return;
    }
    dataObj = dt.object();
    options.setPriority(dataObj["priority"].toInt());
    options.setInheritRepeat(dataObj["inheritRepeat"].toInt());
    options.setGender(dataObj["gender"].toInt());
    emit signalOptionChange();
}
