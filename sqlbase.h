#ifndef SQLBASE_H
#define SQLBASE_H
#include <QString>
#include <QtSql>
//SQL ODBC abstract Class, application through abstract Class to execute SQL Command, and the SQL Server Class inherit from this abstract Class
class SQLBase
{
public:
    SQLBase(){}
    virtual ~SQLBase(){}
    virtual bool connect()=0;
    virtual bool disconnect()=0;
    virtual QSqlDatabase getdb()=0;
};

#endif // SQLBASE_H
