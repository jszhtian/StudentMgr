#ifndef SQLSERVER_H
#define SQLSERVER_H
#include "sqlbase.h"
#include <common.h>

class SQLServer:public SQLBase
{
public:
    SQLServer(QString Addr,QString USN,QString PWD)
    {
        ServerAddress=Addr;
        UserName=USN;
        Password=PWD;
    }
    ~SQLServer();
    bool connect();
    bool disconnect();
    QSqlDatabase getdb();
private:
    QSqlDatabase db;
    QString dsn;
    QString ServerAddress;
    QString UserName;
    QString Password;
};

#endif // SQLSERVER_H
