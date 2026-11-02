#ifndef OPTIONPAGE_H
#define OPTIONPAGE_H

#include "basicpage/basicpage.h"

namespace Ui {
class OptionPage;
}

class OptionPage : public BasicPage
{
    Q_OBJECT
public:
    explicit OptionPage(QWidget *parent = nullptr);
    ~OptionPage();
private:
    Ui::OptionPage *ui;
private:
    void initService() override;
    void connectSignal() override;
};

#endif // OPTIONPAGE_H
