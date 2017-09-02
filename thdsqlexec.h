#ifndef THDSQLEXEC_H
#define THDSQLEXEC_H
#include <QThread>
#include <QtSql>
#include "common.h"

class thdSQLExec : public QThread
{
    Q_OBJECT
public:
    ~thdSQLExec();
    void setquery(QSqlQuery* setquery);
    void setTransaction(bool value);
    void setDatebase(QSqlDatabase* setdb);
    void resetStatus();
    bool getresult();
    void run();
private:
    QSqlDatabase* db=NULL;
    QSqlQuery* query=NULL;
    bool transaction=true;
    bool execresult=false;
    bool isReset=false;
};

#endif // THDSQLEXEC_H
