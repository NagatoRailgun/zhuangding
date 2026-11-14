#include "optionpage.h"
#include "ui_optionpage.h"
#include "classclass/classclass.h"
#include "optionclass/optionclass.h"

OptionPage::OptionPage(QWidget *parent):
    BasicPage(parent),
    ui(new Ui::OptionPage)
{
    ui->setupUi(this);
    initService();
    connectSignal();
    loadClassComboBoxSlot();
    loadOptionSlot();
}

OptionPage::~OptionPage()
{
    delete ui;
}

void OptionPage::initService()
{
    serviceStudent = StudentService::getInstance();
    serviceOption = OptionService::getInstance();
}

void OptionPage::connectSignal()
{
    connect(serviceStudent,SIGNAL(signalClassChange()),this,SLOT(loadClassComboBoxSlot()));
    connect(serviceOption,SIGNAL(signalOptionChange()),this,SLOT(loadOptionSlot()));
}

void OptionPage::loadClassComboBoxSlot()
{
    int selectIdx = -1;
    QList<int>classIds = serviceStudent->getAllClassId();
    ui->comboBox->clear();
    for(int i = 0;i<classIds.count();i++){
        ClassClass classData = serviceStudent->getClassData(classIds[i]);
        ui->comboBox->addItem(classData.getClassName(),classData.getClassId());
        if(classData.getSelected()){
            selectIdx = i;
        }
    }
    if(selectIdx>=0){
        ui->comboBox->setCurrentIndex(selectIdx);
    }
}

void OptionPage::loadOptionSlot()
{
    OptionClass options =  serviceOption->getOption();
    if(options.getCountPriority() == OptionClass::PRIORITY_TYPE_DISABLE){
        ui->pushButton_3->click();
    }else if(options.getCountPriority() == OptionClass::PRIORITY_TYPE_ABLE){
        ui->pushButton_4->click();
    }
    if(options.getLevelPriority() == OptionClass::PRIORITY_TYPE_DISABLE){
        ui->pushButton_5->click();
    }else if(options.getLevelPriority() == OptionClass::PRIORITY_TYPE_ABLE){
        ui->pushButton_12->click();
    }
    if(options.getInheritRepeat() == OptionClass::INHERITREPEAT_TYPETYPE_ABLE){
        ui->pushButton_6->click();
    }else if(options.getInheritRepeat() == OptionClass::INHERITREPEAT_TYPE_TYPE_DISABLE){
        ui->pushButton_7->click();
    }
    if(options.getGender() == OptionClass::GENDER_TYPE_ALL){
        ui->pushButton_10->click();
    }else if(options.getGender() == OptionClass::GENDER_TYPE_MALE){
        ui->pushButton_8->click();
    }else if(options.getGender() == OptionClass::GENDER_TYPE_FEMALE){
        ui->pushButton_9->click();
    }
}

void OptionPage::on_pushButton_clicked()
{
    int nowClassId = serviceStudent->getNowClassId();
    int newClassId = ui->comboBox->currentData().toInt();
    if( newClassId!= nowClassId){
        serviceStudent->setNowClassId(newClassId);
    }
    OptionClass options;
    if(ui->pushButton_3->isChecked()){
        options.setCountPriority(OptionClass::PRIORITY_TYPE_DISABLE);
    }else if(ui->pushButton_4->isChecked()){
        options.setCountPriority(OptionClass::PRIORITY_TYPE_ABLE);
    }
    if(ui->pushButton_5->isChecked()){
        options.setLevelPriority(OptionClass::PRIORITY_TYPE_DISABLE);
    }else if(ui->pushButton_12->isChecked()){
        options.setLevelPriority(OptionClass::PRIORITY_TYPE_ABLE);
    }
    if(ui->pushButton_6->isChecked()){
        options.setInheritRepeat(OptionClass::INHERITREPEAT_TYPETYPE_ABLE);
    }else if(ui->pushButton_7->isChecked()){
        options.setInheritRepeat(OptionClass::INHERITREPEAT_TYPE_TYPE_DISABLE);
    }
    if(ui->pushButton_10->isChecked()){
        options.setGender(OptionClass::GENDER_TYPE_ALL);
    }else if(ui->pushButton_8->isChecked()){
        options.setGender(OptionClass::GENDER_TYPE_MALE);
    }else if(ui->pushButton_9->isChecked()){
        options.setGender(OptionClass::GENDER_TYPE_FEMALE);
    }
    serviceOption->setOption(options);
}

void OptionPage::on_pushButton_2_clicked()
{
    loadClassComboBoxSlot();
    loadOptionSlot();
}

