#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include "fileservice.h"
#include "studentservice/studentservice.h"
#include "optionservice/optionservice.h"

FileService::FileService(QObject *parent)
    : BasicService{parent}
{
    serviceName = tr("File Service");
    if(!instance){
        instance = this;
        qDebug()<<"["<<serviceName<<"]"<<tr("service started");
    }
}

FileService::~FileService(){
    instance = nullptr;
    qDebug()<<"["<<serviceName<<"]"<<tr("service closed");
}

FileService * FileService::getInstance(QObject * parent){
    if(instance){
        return instance;
    }
    return new FileService(parent);
}

FileService * FileService::instance = nullptr;


void FileService::afterInitService()
{

}

void FileService::beforeCloseService(){
    qDebug()<<"["<<serviceName<<"]"<<tr("service closing");
    saveData();//保存统计数据
    saveOption();//保存设置数据
}

void FileService::saveData()
{
    QString data = StudentService::getInstance()->getAllDataToJson();
    saveDataToFile(data,"appdata",StudentService::getInstance()->checkClassEmpty());
}

void FileService::saveOption()
{
    QString data = OptionService::getInstance()->getAllDataToJson();
    saveDataToFile(data,"optiondata",false);
}

void FileService::saveDataToFile(QString dataJsonString,QString fileName,bool isEmpty)
{
    QDir folder;
    QString folderPath;
    qint64 size;
    qDebug()<<"["<<serviceName<<"]"<<tr("start saving");
    folderPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/zhuangding";
    if(!folder.mkpath(folderPath)){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to create folder:")<<folderPath;
        return;
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("create folder:")<<folderPath;
    QFile file(folderPath+"/"+fileName+".json");
    if(isEmpty){
        //空数据时删除缓存文件
        if(file.exists()){
            file.remove();
            qDebug()<<"["<<serviceName<<"]"<<tr("remove file:")<<file.filesystemFileName();
        }
        return;
    }
    if(!file.open(QIODevice::WriteOnly)){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to open file:")<<file.filesystemFileName();
        return;
    }
    size = file.write(dataJsonString.toUtf8());
    qDebug()<<"["<<serviceName<<"]"<<tr("write")<<size<<"bit"<<tr(" to file");
    file.close();
    qDebug()<<"["<<serviceName<<"]"<<tr("end save");
}

QByteArray FileService::loadData()
{
    return loadDataFromFile("appdata");
}

QByteArray FileService::loadOption()
{
    return loadDataFromFile("optiondata");
}

QByteArray FileService::loadDataFromFile(QString fileName){
    QByteArray data;
    QString filePath;
    filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/zhuangding/"+fileName+".json";
    QFile file(filePath);
    data = "";
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"["<<serviceName<<"]"<<tr("fail to open file:")<<file.fileName();
        return data;
    }
    while(!file.atEnd()){
        data.append(file.readLine());
    }
    qDebug()<<"["<<serviceName<<"]"<<tr("read ")<<data.size()<<"bit "<<tr("from file:")<<file.fileName();
    file.close();
    return data;
}

bool FileService::checkDataFile()
{
    return checkFileExsit("appdata");
}

bool FileService::checkOptionFile()
{
    return checkFileExsit("optiondata");
}

bool FileService::checkFileExsit(QString fileName)
{
    QString filePath;
    filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/zhuangding/"+fileName+".json";
    QFile file(filePath);
    if(file.exists()){
        return true;
    }
    return false;
}
