#ifndef THDCONNECT_H
#define THDCONNECT_H
#include "sqlbase.h"
#include "common.h"
#include <QThread>
//inherit from Qthread
class thdconnect : public QThread
{
    //Statement this class is a Q_Object
    Q_OBJECT
signals:
    //define the signal for information exchange
    void result(bool res);
public:
    void setdb(shared_ptr<SQLBase> db);
    //realize the virtual function in the QThread

private:
    shared_ptr<SQLBase> sql;
protected:
    void run();
};
#endif // THDCONNECT_H
