#ifndef BASICBUTTONWIDGET_H
#define BASICBUTTONWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>

class BasicButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BasicButtonWidget(QWidget *parent = nullptr);
    virtual void leftMousePress(QMouseEvent * e);
    virtual void rightMousePress(QMouseEvent * e);
private:
    void paintEvent(QPaintEvent * e) override;
    void mousePressEvent(QMouseEvent * e) override;
    void mouseReleaseEvent(QMouseEvent * e) override;
    void mouseMoveEvent(QMouseEvent * e) override;
signals:
    void signalLeftPress(QMouseEvent * e);
    void signalRightPress(QMouseEvent * e);
    void signalMouseRelease(QMouseEvent * e);
};

#endif // BASICBUTTONWIDGET_H
