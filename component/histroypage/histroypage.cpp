#include <QStandardItemModel>
#include "histroypage.h"
#include "ui_histroypage.h"

HistroyPage::HistroyPage(QWidget *parent):
    BasicPage(parent),
    ui(new Ui::HistroyPage)
{
    ui->setupUi(this);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->horizontalHeader()->setHighlightSections(false);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    initService();
    connectSignal();
    ui->pushButton_10->click();
}

HistroyPage::~HistroyPage()
{
    delete ui;
}

void HistroyPage::initService()
{
    serviceHistroy = HistroyService::getInstance();
    serviceCatch = CatchService::getInstance();
}

void HistroyPage::connectSignal()
{

}

void HistroyPage::showStudentData(QList<StudentClass> students)
{
    double persent;
    QString gender;
    QStandardItemModel * model = new QStandardItemModel(0,6,this);
    // 设置表头
    model->setHorizontalHeaderLabels({tr("ID"),tr("Name"),tr("Gender"),tr("Priority"),tr("Selected Count"),tr("Next Probability"),tr("Last Selected")});
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    for(int i = 0;i<students.count();i++){
        QList<QStandardItem*> row;
        if(students[i].getStudentGender() == StudentClass::GENDER_STATUS_MALE){
            gender = tr("Male");
        }else{
            gender = tr("Female");
        }
        persent = (double)serviceCatch->getCatchProbability(students[i].getStudentId())/100.00;
        row<<new QStandardItem(QString::number(students[i].getStudentShowId()))
              <<new QStandardItem(students[i].getStudentName())
              <<new QStandardItem(gender)
              <<new QStandardItem(QString::number(students[i].getSelectLevel()))
              <<new QStandardItem(QString::number(students[i].getSelectedTimes()))
              <<new QStandardItem(QString::number(persent,'f',2)+"%")
              <<new QStandardItem(students[i].getSelectedDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        model->appendRow(row);
    }
}

void HistroyPage::on_pushButton_10_clicked()
{
    QList<StudentClass>data = serviceHistroy->getHistroyData(HistroyService::DATA_TYPE_ALL);
    showStudentData(data);
}


void HistroyPage::on_pushButton_11_clicked()
{
    QList<StudentClass>data = serviceHistroy->getHistroyData(HistroyService::DATA_TYPE_MALE);
    showStudentData(data);
}


void HistroyPage::on_pushButton_12_clicked()
{
    QList<StudentClass>data = serviceHistroy->getHistroyData(HistroyService::DATA_TYPE_FEMALE);
    showStudentData(data);
}


void HistroyPage::on_pushButton_13_clicked()
{
    QList<StudentClass>data = serviceHistroy->getHistroyData(HistroyService::DATA_TYPE_SELECTED);
    showStudentData(data);
}


void HistroyPage::on_pushButton_14_clicked()
{
    QList<StudentClass>data = serviceHistroy->getHistroyData(HistroyService::DATA_TYPE_UNSELECTED);
    showStudentData(data);
}

