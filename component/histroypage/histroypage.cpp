#include "histroypage.h"
#include "ui_histroypage.h"

HistroyPage::HistroyPage(QWidget *parent):
    BasicPage(parent),
    ui(new Ui::HistroyPage)
{
    ui->setupUi(this);
    initService();
    connectSignal();
}

HistroyPage::~HistroyPage()
{
    delete ui;
}

void HistroyPage::initService()
{
}

void HistroyPage::connectSignal()
{

}
