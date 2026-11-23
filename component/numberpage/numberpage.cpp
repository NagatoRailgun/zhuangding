#include "numberpage.h"
#include "ui_numberpage.h"

NumberPage::NumberPage(QWidget *parent):
    BasicPage(parent),
    ui(new Ui::NumberPage)
{
    ui->setupUi(this);
    initService();
    connectSignal();
    signalNowClassChangeSlot(serviceStudent->getNowClassId());
}

NumberPage::~NumberPage()
{
    delete ui;
}

void NumberPage::initService()
{
    serviceStudent = StudentService::getInstance();
    serviceCatchNumber = CatchNumberService::getInstance();
}

void NumberPage::connectSignal()
{

}

void NumberPage::signalNowClassChangeSlot(int classId)
{
    if(classId<0){
        return;
    }
    loadStudentNumber();
}

void NumberPage::loadStudentNumber()
{
    int studentId = serviceCatchNumber->getLastCatchStudentId();
    if(studentId<0){
        ui->label_2->setText(tr("Nobody"));
    }else{
        selectedStudentId = studentId;
        ui->label_5->setText(tr("No.")+QString::number(serviceStudent->getStudentShowId(selectedStudentId))+tr(" "));
        ui->label_2->setText(serviceStudent->getStudentName(selectedStudentId));
    }
}
