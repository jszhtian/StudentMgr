#include "thdsqlexec.h"



thdSQLExec::~thdSQLExec()
{
    db=NULL;
    query=NULL;
    transaction=true;
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
