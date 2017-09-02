#include "thdconnect.h"

void thdconnect::setdb(shared_ptr<SQLBase> db)
{
    if (db.get()!=NULL){
        sql=db;
    }

}

void thdconnect::run()
{
    if(sql.get()!=NULL){
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
