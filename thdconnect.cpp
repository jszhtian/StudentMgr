#include "thdconnect.h"

thdconnect::thdconnect(QObject* par):QThread(par)
{
    sql=NULL;
}

thdconnect::~thdconnect()
{
    sql=NULL;
}

void thdconnect::setdb(SQLBase *db)
{
    if (db!=NULL){
        sql=db;
    }

}

void thdconnect::run()
{
    if(sql!=NULL){
        try{
            int res=sql->connect();
            emit result(res);
        }catch (exception& e){
            cout<<"Error:"<<e.what()<<endl;
        }

    }
    else
    {
        emit result(false);
    }

}
