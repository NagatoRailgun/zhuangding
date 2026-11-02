#ifndef BASICSERVICE_H
#define BASICSERVICE_H

#include <QObject>
#include <QDebug>

class BasicService : public QObject
{
    Q_OBJECT
public:
    explicit BasicService(QObject *parent = nullptr);
    virtual void afterInitService() = 0;
    virtual void beforeCloseService() = 0;
public:
    QString serviceName;
signals:

};

#endif // BASICSERVICE_H
