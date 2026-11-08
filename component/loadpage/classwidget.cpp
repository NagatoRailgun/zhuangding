#include "classwidget.h"
#include "ui_classwidget.h"

ClassWidget::ClassWidget(QWidget *parent) :
    BasicButtonWidget(parent),
    ui(new Ui::ClassWidget)
{
    ui->setupUi(this);
}

ClassWidget::~ClassWidget()
{
    delete ui;
}

void ClassWidget::leftMousePress(QMouseEvent * e)
{
    setSelected();
    emit clicksignal(classData.getClassId());
}

void ClassWidget::rightMousePress(QMouseEvent * e)
{

}

void ClassWidget::loadClassData(ClassClass data)
{
    QString name = data.getClassName();
    classData = data;
    ui->label_2->setText(name);
    ui->label->setText(name.left(2));
    setUnselected();
}

bool ClassWidget::checkId(int classId)
{
    if(classId != classData.getClassId()){
        return false;
    }
    return true;
}

void ClassWidget::setSelected()
{
    ui->widget->setStyleSheet(
        "QWidget{"
          "border-radius: 8px;"
          "padding: 4px 4px;"
          "text-align: center;"
          "text-decoration: none;"
          "margin: 4px 2px;"
          "background-color: #6A5ACD;"
          "color: white;"
          "border: 1px solid #6A5ACD;"
      "}");
}

void ClassWidget::setUnselected()
{
    if(classData.getSelected()){
        ui->widget->setStyleSheet(
            "QWidget{"
              "border-radius: 8px;"
              "padding: 4px 4px;"
              "text-align: center;"
              "text-decoration: none;"
              "margin: 4px 2px;"
              "background-color: white;"
              "color: #6A5ACD;"
              "border: 1px solid white;"
          "}"
          "QWidget:hover {"
              "border: 1px solid #6A5ACD;"
          "}");
    }else{
        ui->widget->setStyleSheet(
            "QWidget{"
              "border-radius: 8px;"
              "padding: 4px 4px;"
              "text-align: center;"
              "text-decoration: none;"
              "margin: 4px 2px;"
              "background-color: white;"
              "color: black;"
              "border: 1px solid white;"
          "}"
          "QWidget:hover {"
              "border: 1px solid #6A5ACD;"
          "}");
    }
}
