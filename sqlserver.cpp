#include "sqlserver.h"

SQLServer::~SQLServer()
{
    db.close();
}

bool SQLServer::connect()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC3");
    db.setHostName(ServerAddress);
    //create odbc dsn
    QString dsn=QString::fromLocal8Bit("Driver={ODBC Driver 13 for SQL Server};");
    //set connection model to TCP Remote model
    dsn.append(QString::fromLocal8Bit("Server=tcp:"));
    dsn.append(ServerAddress);
    dsn.append(QString::fromLocal8Bit(";"));
    dsn.append(QString::fromLocal8Bit("Database=ZZU-DB;"));
    dsn.append(QString::fromLocal8Bit("Uid="));
    dsn.append(UserName);
    dsn.append(QString::fromLocal8Bit(";"));
    dsn.append(QString::fromLocal8Bit("Pwd="));
    dsn.append(Password);
    dsn.append(QString::fromLocal8Bit(";"));
    //Set Encrypt Flags
    dsn.append(QString::fromLocal8Bit("Encrypt=yes;"));
    //enable columnencryption support
    dsn.append(QString::fromLocal8Bit("ColumnEncryption=Enabled;"));
    //ignore Certificate error
    dsn.append(QString::fromLocal8Bit("TrustServerCertificate=yes;"));
    db.setDatabaseName(dsn);
    db.setUserName(UserName);
    db.setPassword(Password);
    //try to establish odbc connect

    if(!db.open())
    {
       cout<<"Database Error"<<endl;
       cout<<db.lastError().text().toStdString()<<endl;
       qDebug()<<db.lastError().text();
       return false;
    }
    else
    {
        return true;
    }
}

bool SQLServer::disconnect()
{
    try{
        db.close();
        return true;
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
        return false;
    }

}

QSqlDatabase SQLServer::getdb()
{
    return db;
}

