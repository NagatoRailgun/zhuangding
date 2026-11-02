#ifndef HISTROYPAGE_H
#define HISTROYPAGE_H

#include "basicpage/basicpage.h"

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
private:
    void initService() override;
    void connectSignal() override;
};

#endif // HISTROYPAGE_H
