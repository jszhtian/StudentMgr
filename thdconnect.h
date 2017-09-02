#ifndef THDCONNECT_H
#define THDCONNECT_H
#include "sqlbase.h"
#include "common.h"
//inherit from Qthread
class thdconnect : public QThread
{
    //Statement this class is a Q_Object
    Q_OBJECT
signals:
    //define the signal for information exchange
    void result(bool res);
public:
    thdconnect(QObject* par);
    ~thdconnect();
    void setdb(SQLBase* db);
    //realize the virtual function in the QThread
    void run();
private:
    SQLBase* sql=NULL;
};
#endif // THDCONNECT_H
