#include<QRandomGenerator>
#include "catchpage.h"
#include "ui_catchpage.h"
#include "optionclass/optionclass.h"

CatchPage::CatchPage(QWidget *parent):
    BasicPage(parent),
    ui(new Ui::CatchPage)
{
    ui->setupUi(this);
    initService();
    connectSignal();
    signalNowClassChangeSlot(serviceStudent->getNowClassId());
    signalCatchStudentAddSlot(-1);
    showOptionSlot();
}

CatchPage::~CatchPage()
{
    delete ui;
}

void CatchPage::initService(){
    serviceCatch = CatchService::getInstance();
    serviceStudent = StudentService::getInstance();
    serviceOption = OptionService::getInstance();
}

void CatchPage::connectSignal(){
    connect(serviceStudent,SIGNAL(signalNowClassChange(int)),this,SLOT(signalNowClassChangeSlot(int)));
    connect(serviceCatch,SIGNAL(signalCatchStudent(int,int)),this,SLOT(signalCatchStudentSlot(int,int)));
    connect(serviceCatch,SIGNAL(signalCatchStudentAdd(int)),this,SLOT(signalCatchStudentAddSlot(int)));
    connect(serviceOption,SIGNAL(signalOptionChange()),this,SLOT(showOptionSlot()));
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
    for(int i = 0;i<nameList.count();i++){
        delete nameList[i];
        nameList.removeAt(i);
        i--;
    }
    for(int i = data.count()-1; i>=0; i--){
        CatchNameWidget * nameWidget = new CatchNameWidget(ui->widget_6);
        ui->widget_6->layout()->addWidget(nameWidget);
        nameWidget->setName(data[i].name);
        nameWidget->setChance(data[i].chance);
        nameList.push_back(nameWidget);
    }
    for(int i = 0;i<nameList.count();i++){
        if(i == 0){
            nameList[i]->setColor(true);
        }else{
            nameList[i]->setColor(false);
        }
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

void CatchPage::showOptionSlot()
{
    OptionClass options = serviceOption->getOption();
    if(options.getCountPriority() == OptionClass::PRIORITY_TYPE_ABLE){
        ui->label_6->setText(tr("Count Priority:Able"));
    }else if(options.getCountPriority() == OptionClass::PRIORITY_TYPE_DISABLE){
        ui->label_6->setText(tr("Count Priority:Disable"));
    }
    if(options.getLevelPriority() == OptionClass::PRIORITY_TYPE_ABLE){
        ui->label_15->setText(tr("Level Priority:Able"));
    }else if(options.getLevelPriority() == OptionClass::PRIORITY_TYPE_DISABLE){
        ui->label_15->setText(tr("Level Priority:Disable"));
    }
    if(options.getInheritRepeat() == OptionClass::INHERITREPEAT_TYPETYPE_ABLE){
        ui->label_7->setText(tr("Selected Count: Inherit"));
    }else if(options.getInheritRepeat() == OptionClass::INHERITREPEAT_TYPE_TYPE_DISABLE){
        ui->label_7->setText(tr("Selected Count: Abandon"));
    }
    if(options.getGender() == OptionClass::GENDER_TYPE_ALL){
        ui->label_8->setText(tr("Gender:All"));
    }else if(options.getGender() == OptionClass::GENDER_TYPE_MALE){
        ui->label_8->setText(tr("Gender:Male"));
    }else if(options.getGender() == OptionClass::GENDER_TYPE_FEMALE){
        ui->label_8->setText(tr("Gender:Female"));
    }
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

