#include "thdconnect.h"

void thdconnect::setdb(shared_ptr<SQLBase> db)
{
    if (db.get()!=NULL){
        sql=db;
    }

}

void thdconnect::run()
{
    qDebug()<<"thdconnect thread run";
    wcout<<"thdconnect thread run"<<endl;
    auto res=sql->connect();
    emit result(res);
}
