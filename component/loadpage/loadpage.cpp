#include <QFileDialog>
#include "loadpage.h"
#include "ui_loadpage.h"

LoadPage::LoadPage(QWidget *parent):
    BasicPage(parent),
    ui(new Ui::LoadPage)
{
    ui->setupUi(this);
    initService();
    connectSignal();
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

void LoadPage::on_pushButton_2_clicked()
{

}


void LoadPage::on_pushButton_4_clicked()
{
    serviceLoad->saveNewClass();
}


void LoadPage::on_lineEdit_textEdited(const QString &)
{
    serviceLoad->loadExcel(ui->lineEdit->text(),ui->lineEdit_2->text());
}

