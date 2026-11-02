#include<QRandomGenerator>
#include "catchpage.h"
#include "ui_catchpage.h"

CatchPage::CatchPage(QWidget *parent):
    BasicPage(parent),
    ui(new Ui::CatchPage)
{
    ui->setupUi(this);
    initService();
    connectSignal();
    signalNowClassChangeSlot(serviceStudent->getNowClassId());
    signalCatchStudentAddSlot(-1);
}

CatchPage::~CatchPage()
{
    delete ui;
}

void CatchPage::initService(){
    serviceCatch = CatchService::getInstance();
    serviceStudent = StudentService::getInstance();
}

void CatchPage::connectSignal(){
    connect(serviceStudent,SIGNAL(signalNowClassChange(int)),this,SLOT(signalNowClassChangeSlot(int)));
    connect(serviceCatch,SIGNAL(signalCatchStudent(int,int)),this,SLOT(signalCatchStudentSlot(int,int)));
    connect(serviceCatch,SIGNAL(signalCatchStudentAdd(int)),this,SLOT(signalCatchStudentAddSlot(int)));
    connect(&timer,SIGNAL(timeout()),this,SLOT(showNameSlot()));
}

void CatchPage::signalNowClassChangeSlot(int nowClassId)
{
    if(nowClassId<0){
        return;
    }
    loadStudentName();
}

void CatchPage::signalCatchStudentSlot(int pos,int studentId)
{
    showNum = 0;
    selectedStudentPos = pos;
    selectedStudentId = studentId;
    if(pos){
        timer.start(1000);
    }else{
        timer.start(20);
    }
}

void CatchPage::signalCatchStudentAddSlot(int)
{
    QString text;
    QList<CatchService::SelectStudentData> data = serviceCatch->getSelectedStudentList();
    ui->listWidget->clear();
    for(int i = 0; i<data.count(); i++){
        text = QString::number(data[i].num) +"."+data[i].name;
        ui->listWidget->addItem(text);
    }
}

void CatchPage::showNameSlot()
{
    int rnum;
    int nStudentNum;
    nStudentNum = StudentService::getInstance()->getNowStudentNum();
    QList<int>studentIdPool = StudentService::getInstance()->getNowStudentId();
    if(selectedStudentPos){
        timer.setInterval(20);
    }
    showNum++;
    if(showNum>20){
        timer.stop();
        ui->label_5->setText(tr("No.")+QString::number(serviceStudent->getStudentShowId(selectedStudentId))+tr(" "));
        ui->label_2->setText(serviceStudent->getStudentName(selectedStudentId));
        serviceCatch->addSelectStudentToList(selectedStudentPos);
        return;
    }
    rnum = QRandomGenerator::global()->bounded(0,nStudentNum);
    ui->label_5->setText(tr("No.")+QString::number(serviceStudent->getStudentShowId(studentIdPool[rnum]))+tr(" "));
    ui->label_2->setText(serviceStudent->getStudentName(studentIdPool[rnum]));
}

void CatchPage::loadStudentName()
{
    ui->label_2->setText(tr("Nobody"));
}

void CatchPage::on_pushButton_clicked()
{
    serviceCatch->catch1Time();
}

void CatchPage::on_pushButton_2_clicked()
{
    serviceCatch->catch10Times();
}

void CatchPage::on_pushButton_3_pressed()
{
    serviceCatch->catchMoreStart();
}

void CatchPage::on_pushButton_3_released()
{
    serviceCatch->catchMoreEnd();
}

void CatchPage::on_pushButton_4_clicked()
{
    serviceCatch->catch1TimeRepeatless();
}

