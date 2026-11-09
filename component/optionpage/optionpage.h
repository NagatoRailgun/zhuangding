#ifndef OPTIONPAGE_H
#define OPTIONPAGE_H

#include "basicpage/basicpage.h"
#include "studentservice/studentservice.h"
#include "optionservice/optionservice.h"

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
    StudentService * serviceStudent = nullptr;
    OptionService * serviceOption = nullptr;
private:
    void initService() override;
    void connectSignal() override;
private slots:
    void loadClassComboBoxSlot();
    void loadOptionSlot();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // OPTIONPAGE_H
