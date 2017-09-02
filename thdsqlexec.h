#ifndef THDSQLEXEC_H
#define THDSQLEXEC_H
#include <QThread>
#include <QtSql>
#include "common.h"

class thdSQLExec : public QThread
{
    Q_OBJECT
signals:
    //define the signal for information exchange
    void result(bool res);
public:
    thdSQLExec();
    ~thdSQLExec();
    void setquery(QSqlQuery* setquery);
    void setTransaction(bool value);
    void setDatebase(QSqlDatabase* setdb);
private:
    QSqlDatabase* db=NULL;
    QSqlQuery* query=NULL;
    bool transaction=true;
};

#endif // THDSQLEXEC_H
