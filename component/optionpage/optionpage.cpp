#include "optionpage.h"
#include "ui_optionpage.h"

OptionPage::OptionPage(QWidget *parent):
    BasicPage(parent),
    ui(new Ui::OptionPage)
{
    ui->setupUi(this);
    initService();
    connectSignal();
}

OptionPage::~OptionPage()
{
    delete ui;
}

void OptionPage::initService()
{

}

void OptionPage::connectSignal()
{

}
