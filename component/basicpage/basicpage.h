#ifndef BASICPAGE_H
#define BASICPAGE_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

class BasicPage : public QWidget
{
    Q_OBJECT
public:
    explicit BasicPage(QWidget *parent = nullptr);
    virtual void initService() = 0;
    virtual void connectSignal() = 0;
private:
    void paintEvent(QPaintEvent * e) override;
};

#endif // BASICPAGE_H
