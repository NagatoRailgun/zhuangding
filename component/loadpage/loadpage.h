#ifndef LOADPAGE_H
#define LOADPAGE_H

#include "basicpage/basicpage.h"
#include "studentservice/studentservice.h"
#include "loadservice/loadservice.h"

namespace Ui {
class LoadPage;
}

class LoadPage : public BasicPage
{
    Q_OBJECT
public:
    explicit LoadPage(QWidget *parent = nullptr);
    ~LoadPage();
private:
    Ui::LoadPage *ui;
    StudentService * serviceStudent = nullptr;
    LoadService * serviceLoad = nullptr;
private:
    void initService() override;
    void connectSignal() override;
private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_lineEdit_textEdited(const QString &arg1);
};

#endif // LOADPAGE_H
