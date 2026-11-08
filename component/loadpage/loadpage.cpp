#include <QFileDialog>
#include <QGridLayout>
#include "loadpage.h"
#include "ui_loadpage.h"
#include "classclass/classclass.h"
#include "basicbuttonwidget/basicbuttonwidget.h"

LoadPage::LoadPage(QWidget *parent):
    BasicPage(parent),
    ui(new Ui::LoadPage)
{
    ui->setupUi(this);
    initService();
    connectSignal();
    loadClassSlot();
    nowSelectedClassId = -1;
}

LoadPage::~LoadPage()
{
    delete ui;
}

void LoadPage::initService(){
    serviceStudent = StudentService::getInstance();
    serviceLoad = LoadService::getInstance();
}

void LoadPage::connectSignal(){
    connect(serviceStudent,SIGNAL(signalClassChange()),this,SLOT(loadClassSlot()));
    connect(ui->widget_10,&BasicButtonWidget::signalLeftPress,this,[=](QMouseEvent * e){
        for(int i = 0;i<classBottonList.count();i++){
            classBottonList[i]->setUnselected();
            nowSelectedClassId = -1;
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
        }
    });
}

void LoadPage::on_pushButton_3_clicked()
{
    QString filePath;
    QString fileName;

    filePath = QFileDialog::getOpenFileName(this,tr("Select Excel"),"","(*.xls);(*.xlsx)");
    if (!filePath.isEmpty()) {
        ui->lineEdit_2->setText(filePath);
        fileName = QFileInfo(filePath).baseName();
        ui->lineEdit->setText(fileName);
        serviceLoad->loadExcel(ui->lineEdit->text(),ui->lineEdit_2->text());
    }
}

void LoadPage::loadClassSlot()
{
    int row,col,colNum = 6;
    QGridLayout * layout = (QGridLayout *)ui->widget->layout();
    QList<int> classIds = serviceStudent->getAllClassId();
    for(int i = 0;i<classBottonList.count();i++){
        layout->removeWidget(classBottonList[i]);
        delete classBottonList[i];
    }
    classBottonList.clear();
    row = 0,col = 0;
    for(int i = 0;i<classIds.count();i++){
        ClassClass classData = serviceStudent->getClassData(classIds[i]);
        ClassWidget * classItem = new ClassWidget(ui->widget);
        classItem->loadClassData(classData);
        connect(classItem,&ClassWidget::clicksignal,this,[=](int classId){
            ClassClass selectedClassData = serviceStudent->getClassData(classId);
            nowSelectedClassId = classId;
            for(int i = 0;i<classBottonList.count();i++){
                if(!classBottonList[i]->checkId(classId)){
                    classBottonList[i]->setUnselected();
                }
            }
            ui->lineEdit->setText(selectedClassData.getClassName());
            ui->lineEdit_2->setText("");
        });
        layout->addWidget(classItem,row,col,Qt::AlignLeft);
        layout->setSizeConstraint(QLayout::SetFixedSize);
        classBottonList.push_back(classItem);
        if(col<colNum){
            col++;
        }else{
            row++;
            col = 0;
        }
    }
}

void LoadPage::on_pushButton_2_clicked()
{
    serviceLoad->deleteClass(ui->lineEdit->text());
}


void LoadPage::on_pushButton_4_clicked()
{
    int selectClassId = -1;
    for(int i = 0;i<classBottonList.count();i++){
        if(classBottonList[i]->checkSelected()){
            selectClassId = classBottonList[i]->getClassId();
        }
    }
    if(selectClassId<0){
        serviceLoad->saveClass(ui->lineEdit->text());
    }else{
        serviceLoad->editClassName(selectClassId,ui->lineEdit->text());
    }
}


void LoadPage::on_lineEdit_textEdited(const QString &)
{
    serviceLoad->loadExcel(ui->lineEdit->text(),ui->lineEdit_2->text());
}

