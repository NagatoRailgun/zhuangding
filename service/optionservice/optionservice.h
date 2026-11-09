#ifndef OPTIONSERVICE_H
#define OPTIONSERVICE_H

#include "basicservice/basicservice.h"
#include "optionclass/optionclass.h"

class OptionService : public BasicService
{
    Q_OBJECT
public:
    ~OptionService();
    static OptionService *  getInstance(QObject * parent  = nullptr);
    void afterInitService() override;
    void beforeCloseService() override;
    void initOption();
    void setOption(OptionClass opt);
    OptionClass getOption();
    QString getAllDataToJson();
private:
    static OptionService * instance;
    OptionClass options;
private:
    explicit OptionService(QObject *parent = nullptr);
    void loadFileData();
signals:
    void signalOptionChange();
};
#endif // OPTIONSERVICE_H
