#include "catchnamewidget.h"
#include "ui_catchnamewidget.h"

CatchNameWidget::CatchNameWidget(QWidget *parent) :
    BasicButtonWidget(parent),
    ui(new Ui::CatchNameWidget)
{
    ui->setupUi(this);
}

CatchNameWidget::~CatchNameWidget()
{
    delete ui;
}

void CatchNameWidget::leftMousePress(QMouseEvent * e)
{

}

void CatchNameWidget::rightMousePress(QMouseEvent * e)
{

}

void CatchNameWidget::setName(QString name)
{
    ui->label->setText(name);
}

void CatchNameWidget::setChance(int chance)
{
    double num = (double)chance/100.00;
    ui->label_2->setText("["+QString::number(num,'f',2)+"%]");
}

void CatchNameWidget::setColor(bool isYellow)
{
    if(isYellow){
        ui->label_9->setStyleSheet(
            "QLabel{"
                "background-color: #ff9800;"
                "border-radius:6px;"
            "}"
        );
    }else{
        ui->label_9->setStyleSheet(
            "QLabel{"
                "background-color: #28c76f;"
                "border-radius:6px;"
            "}"
        );
    }
}
