#ifndef CLASSWIDGET_H
#define CLASSWIDGET_H

#include "basicbuttonwidget/basicbuttonwidget.h"
#include "classclass/classclass.h"

namespace Ui {
class ClassWidget;
}

class ClassWidget : public BasicButtonWidget
{
    Q_OBJECT
public:
    explicit ClassWidget(QWidget *parent = nullptr);
    ~ClassWidget();
    void loadClassData(ClassClass data);
    void setUnselected();
    void setSelected();
    bool checkId(int classId);
    bool checkSelected();
    int getClassId();
private:
    Ui::ClassWidget *ui;
    ClassClass classData;
    bool selectFlag;
private:
    void leftMousePress(QMouseEvent * e) override;
    void rightMousePress(QMouseEvent * e) override;
signals:
    void clicksignal(int classId);
};

#endif // CLASSWIDGET_H
