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
private:
    Ui::ClassWidget *ui;
    ClassClass classData;
private:
    void leftMousePress(QMouseEvent * e) override;
    void rightMousePress(QMouseEvent * e) override;
signals:
    void clicksignal(int classId);
};

#endif // CLASSWIDGET_H
