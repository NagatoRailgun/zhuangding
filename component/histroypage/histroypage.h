#ifndef HISTROYPAGE_H
#define HISTROYPAGE_H

#include "basicpage/basicpage.h"
#include "histroyservice/histroyservice.h"

namespace Ui {
class HistroyPage;
}

class HistroyPage : public BasicPage
{
    Q_OBJECT
public:
    explicit HistroyPage(QWidget *parent = nullptr);
    ~HistroyPage();
private:
    Ui::HistroyPage *ui;
    HistroyService * serviceHistroy = nullptr;
private:
    void initService() override;
    void connectSignal() override;
    void showStudentData(QList<StudentClass>students);
private slots:
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
};

#endif // HISTROYPAGE_H
