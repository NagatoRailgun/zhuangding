#include "basicpage.h"

BasicPage::BasicPage(QWidget *parent)
    : QWidget{parent}
{

}

void BasicPage::paintEvent(QPaintEvent * e){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
