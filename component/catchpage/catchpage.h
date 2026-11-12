#ifndef CATCHPAGE_H
#define CATCHPAGE_H

#include <QTimer>
#include "basicpage/basicpage.h"
#include "studentservice/studentservice.h"
#include "catchservice/catchservice.h"
#include "optionservice/optionservice.h"
#include "catchnamewidget.h"

namespace Ui {
class CatchPage;
}

class CatchPage : public BasicPage
{
    Q_OBJECT
public:
    explicit CatchPage(QWidget *parent = nullptr);
    ~CatchPage();
private:
    Ui::CatchPage *ui;
    StudentService * serviceStudent = nullptr;
    CatchService * serviceCatch = nullptr;
    OptionService * serviceOption = nullptr;
    QTimer timer;
    int showNum;
    int selectedStudentId = -1;
    int selectedStudentPos = -1;
    QList<CatchNameWidget *> nameList;
private:
    void initService() override;
    void connectSignal() override;
    void loadStudentName();
 private slots:
    void signalNowClassChangeSlot(int nowClassId);
    void signalCatchStudentSlot(int pos,int studentId);
    void signalCatchStudentAddSlot(int studentId);
    void showNameSlot();
    void showOptionSlot();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_pressed();
    void on_pushButton_3_released();
    void on_pushButton_4_clicked();
};

#endif // CATCHPAGE_H
