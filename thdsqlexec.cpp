#include "thdsqlexec.h"



thdSQLExec::~thdSQLExec()
{
    db=NULL;
    query=NULL;
}

void thdSQLExec::setquery(QSqlQuery *setquery)
{
    if(setquery!=NULL)
    {
        query=setquery;
    }

}

void thdSQLExec::setTransaction(bool value)
{
    transaction=value;
}

void thdSQLExec::setDatebase(QSqlDatabase *setdb)
{
    if(setdb!=NULL)
    {
        db=setdb;
    }
}

void thdSQLExec::resetStatus()
{
    isReset=true;
    execresult=false;
}

bool thdSQLExec::getresult()
{
    return execresult;
}

void thdSQLExec::run()
{
    isReset=false;
    if(query!=NULL&&db!=NULL)
    {
        if(transaction)
        {
            db->transaction();
            bool res=query->exec();
            if(!query->isActive()||res==false)
            {
                db->rollback();
                qDebug()<<db->lastError().text();
                std::wcout<<db->lastError().text().toStdWString()<<endl;
                execresult=false;
            }
            else
            {
                db->commit();
                execresult=true;
            }
        }
        else
        {
            bool res=query->exec();
            if(!query->isActive()||res==false)
            {
                qDebug()<<db->lastError().text();
                std::wcout<<db->lastError().text().toStdWString()<<endl;
                execresult=false;
            }
            else
            {
                execresult=true;
            }
        }
    }
    else
    {
        execresult=false;
    }
}
