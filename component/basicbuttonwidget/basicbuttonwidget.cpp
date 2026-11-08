#include "basicbuttonwidget.h"
#include "qstyle.h"

BasicButtonWidget::BasicButtonWidget(QWidget *parent)
    : QWidget{parent}
{

}

void BasicButtonWidget::paintEvent(QPaintEvent * e){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(e);
}

void BasicButtonWidget::mousePressEvent(QMouseEvent * e)
{
    if(e->button() == Qt::LeftButton){
        leftMousePress(e);
        e->accept();
        return;
    }else if(e->button() == Qt::RightButton){
        rightMousePress(e);
        e->accept();
        return;
    }
    QWidget::mousePressEvent(e);
}

void BasicButtonWidget::leftMousePress(QMouseEvent * e)
{
    emit signalLeftPress(e);
}

void BasicButtonWidget::rightMousePress(QMouseEvent * e)
{
    emit signalRightPress(e);
}

void BasicButtonWidget::mouseReleaseEvent(QMouseEvent * e)
{
    emit signalMouseRelease(e);
    QWidget::mouseReleaseEvent(e);
}

void BasicButtonWidget::mouseMoveEvent(QMouseEvent * e)
{
    QWidget::mouseMoveEvent(e);
}
