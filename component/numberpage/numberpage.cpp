#include "numberpage.h"
#include "ui_numberpage.h"

NumberPage::NumberPage(QWidget *parent):
    BasicPage(parent),
    ui(new Ui::NumberPage)
{
    ui->setupUi(this);
    initService();
    connectSignal();
}

NumberPage::~NumberPage()
{
    delete ui;
}

void NumberPage::initService()
{

}

void NumberPage::connectSignal()
{

}
