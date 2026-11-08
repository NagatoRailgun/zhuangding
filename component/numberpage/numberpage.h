#ifndef NUMBERPAGE_H
#define NUMBERPAGE_H

#include "basicpage/basicpage.h"

namespace Ui {
class NumberPage;
}

class NumberPage : public BasicPage
{
    Q_OBJECT
public:
    explicit NumberPage(QWidget *parent = nullptr);
    ~NumberPage();
private:
    Ui::NumberPage *ui;
private:
    void initService() override;
    void connectSignal() override;
};

#endif // NUMBERPAGE_H
