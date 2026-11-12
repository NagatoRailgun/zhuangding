#ifndef CATCHNAMEWIDGET_H
#define CATCHNAMEWIDGET_H

#include "basicbuttonwidget/basicbuttonwidget.h"

namespace Ui {
class CatchNameWidget;
}

class CatchNameWidget : public BasicButtonWidget
{
    Q_OBJECT
public:
    explicit CatchNameWidget(QWidget *parent = nullptr);
    ~CatchNameWidget();
    void setName(QString name);
    void setChance(int chance);
    void setColor(bool isYellow);
private:
    Ui::CatchNameWidget *ui;
private:
    void leftMousePress(QMouseEvent * e) override;
    void rightMousePress(QMouseEvent * e) override;
};
#endif // CATCHNAMEWIDGET_H
