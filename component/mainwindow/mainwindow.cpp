#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "studentservice/studentservice.h"
#include "catchservice/catchservice.h"
#include "loadservice/loadservice.h"
#include "fileservice/fileservice.h"
#include "histroyservice/histroyservice.h"

#include "catchpage/catchpage.h"
#include "loadpage/loadpage.h"
#include "optionpage/optionpage.h"
#include "histroypage/histroypage.h"
#include "numberpage/numberpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    initService();
    ui->setupUi(this);
    connectSignal();
    ui->pushButton->click();
    loadClassDataSlot();
}

MainWindow::~MainWindow()
{
    for(int i = 0;i<serviceList.length();i++){
        serviceList[i]->beforeCloseService();
    }
    delete ui;
    for(int i = 0;i<serviceList.length();i++){
        delete serviceList[i];
    }
    serviceList.clear();
}

void MainWindow::initService()
{
    serviceList.append(StudentService::getInstance());
    serviceList.append(CatchService::getInstance());  
    serviceList.append(LoadService::getInstance());
    serviceList.append(FileService::getInstance());
    serviceList.append(HistroyService::getInstance());
    for(int i = 0;i<serviceList.length();i++){
        serviceList[i]->afterInitService();
    }
}

void MainWindow::initCatchPage()
{
    if(leftPage){
        ui->widget->layout()->removeWidget(leftPage);
    }
    delete leftPage;
    leftPage = new CatchPage(ui->widget);
    ui->widget->layout()->addWidget(leftPage);
    leftPage->show();
}

void MainWindow::initLoadPage()
{
    if(leftPage){
        ui->widget->layout()->removeWidget(leftPage);
    }
    delete leftPage;
    leftPage = new LoadPage(ui->widget);
    ui->widget->layout()->addWidget(leftPage);
    leftPage->show();
}

void MainWindow::initOptionPage()
{
    if(leftPage){
        ui->widget->layout()->removeWidget(leftPage);
    }
    delete leftPage;
    leftPage = new OptionPage(ui->widget);
    ui->widget->layout()->addWidget(leftPage);
    leftPage->show();
}

void MainWindow::initHistroyPage()
{
    if(leftPage){
        ui->widget->layout()->removeWidget(leftPage);
    }
    delete leftPage;
    leftPage = new HistroyPage(ui->widget);
    ui->widget->layout()->addWidget(leftPage);
    leftPage->show();
}

void MainWindow::initNumberPage()
{
    if(leftPage){
        ui->widget->layout()->removeWidget(leftPage);
    }
    delete leftPage;
    leftPage = new NumberPage(ui->widget);
    ui->widget->layout()->addWidget(leftPage);
    leftPage->show();
}

void MainWindow::connectSignal()
{
    connect(StudentService::getInstance(),SIGNAL(signalNowClassChange(int)),this,SLOT(loadClassDataSlot()));
    connect(ui->widget_3,SIGNAL(signalLeftPress(QMouseEvent *)),this,SLOT(startMovePageSlot(QMouseEvent *)));
    connect(ui->widget_4,SIGNAL(signalLeftPress(QMouseEvent *)),this,SLOT(startMovePageSlot(QMouseEvent *)));
    connect(ui->widget_3,SIGNAL(signalMouseRelease(QMouseEvent *)),this,SLOT(stopMovePageSlot(QMouseEvent *)));
    connect(ui->widget_4,SIGNAL(signalMouseRelease(QMouseEvent *)),this,SLOT(stopMovePageSlot(QMouseEvent *)));
}

void MainWindow::loadClassDataSlot()
{
    ui->label->setText(StudentService::getInstance()->getNowClassName());
    ui->label_2->setText("("+QString::number(StudentService::getInstance()->getNowStudentNum())+tr(" Num")+")");
}

void MainWindow::on_pushButton_clicked()
{
    initCatchPage();
}


void MainWindow::on_pushButton_2_clicked()
{
    initLoadPage();
}


void MainWindow::on_pushButton_3_clicked()
{
    initOptionPage();
}


void MainWindow::on_pushButton_6_clicked()
{
    initHistroyPage();
}

void MainWindow::on_pushButton_7_clicked()
{
    initNumberPage();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->showMinimized();
}


void MainWindow::on_pushButton_5_clicked()
{
    QApplication::quit();
}

void MainWindow::startMovePageSlot(QMouseEvent * e)
{
    movingFlag = true;
    mouseOffset = e->globalPosition() - this->pos();
}

void MainWindow::stopMovePageSlot(QMouseEvent * e)
{
    movingFlag = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent * e)
{
    if(!movingFlag){
        return;
    }
    QPointF newPoint = e->globalPosition() - mouseOffset;
    this->move(newPoint.toPoint());
}
