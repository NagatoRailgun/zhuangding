#ifndef HISTROYSERVICE_H
#define HISTROYSERVICE_H

#include "basicservice/basicservice.h"
#include "studentclass/studentclass.h"

class HistroyService : public BasicService
{
    Q_OBJECT
public:
    typedef enum{
        DATA_TYPE_ALL,//全部
        DATA_TYPE_MALE,//男生
        DATA_TYPE_FEMALE, //女生
        DATA_TYPE_SELECTED,//选中的
        DATA_TYPE_UNSELECTED,//未选中的
    }DATA_TYPE;
public:
    ~HistroyService();
    static HistroyService *  getInstance(QObject * parent  = nullptr);
    void afterInitService() override;
    void beforeCloseService() override;
    QList<StudentClass> getHistroyData(DATA_TYPE type);
private:
    static HistroyService * instance;
private:
    explicit HistroyService(QObject *parent = nullptr);
signals:
};
#endif // HISTROYSERVICE_H
