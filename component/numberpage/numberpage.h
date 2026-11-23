#ifndef NUMBERPAGE_H
#define NUMBERPAGE_H

#include "basicpage/basicpage.h"
#include "studentservice/studentservice.h"
#include "catchnumberservice/catchnumberservice.h"

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
    StudentService * serviceStudent = nullptr;
    CatchNumberService * serviceCatchNumber = nullptr;
    int selectedStudentId = -1;
    int selectedStudentPos = -1;
private:
    void initService() override;
    void connectSignal() override;
    void loadStudentNumber();
private slots:
    void signalNowClassChangeSlot(int classId);
};

#endif // NUMBERPAGE_H
