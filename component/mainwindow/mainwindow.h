#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "basicpage/basicpage.h"
#include "basicservice/basicservice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
private:
    void initService();
    void connectSignal();
    void initCatchPage();
    void initLoadPage();
    void initOptionPage();
    void initHistroyPage();
private:
    Ui::MainWindow *ui;
    QList<BasicService *>serviceList;
    BasicPage * leftPage = nullptr;
private slots:
        void loadClassDataSlot();
};
#endif // MAINWINDOW_H
