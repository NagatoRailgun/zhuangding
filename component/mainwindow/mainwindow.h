#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointF>
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
private:
    void initService();
    void connectSignal();
    void initCatchPage();
    void initLoadPage();
    void initOptionPage();
    void initHistroyPage();
    void initNumberPage();
    void mouseMoveEvent(QMouseEvent * e) override;
private:
    Ui::MainWindow *ui;
    QList<BasicService *>serviceList;
    BasicPage * leftPage = nullptr;
    bool movingFlag;
    QPointF mouseOffset;
private slots:
        void loadClassDataSlot();
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void on_pushButton_3_clicked();
        void on_pushButton_6_clicked();
        void on_pushButton_4_clicked();
        void on_pushButton_5_clicked();
        void on_pushButton_7_clicked();
        void startMovePageSlot(QMouseEvent * e);
        void stopMovePageSlot(QMouseEvent * e);
};
#endif // MAINWINDOW_H
