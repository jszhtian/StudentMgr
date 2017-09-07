#ifndef SQLCOMMANDBASE_H
#define SQLCOMMANDBASE_H
#include "common.h"
#include "structdef.h"
#include "sqlbase.h"
#include "thdsqlexec.h"
#include "myprodlg.h"
class SQLCommandBase{
public:
    virtual ~SQLCommandBase(){}
    virtual bool inputdata(shared_ptr<queryexchange> input)=0;
    virtual bool outputdata(shared_ptr<queryexchange> output)=0;
    virtual bool exec()
    {
        MyProdlg dlg;
        //change to multi thread method
        auto m_thread=new thdSQLExec();
        m_thread->setDatebase(&db);
        m_thread->setquery(&Query);
        m_thread->start();
        //m_thread->wait();
        while(!m_thread->isFinished())
        {
            qApp->processEvents();
        }
        dlg.close();
        return m_thread->getresult();
    }
    virtual void setdb(QSqlDatabase setdb){db=setdb;}
protected:
    QSqlDatabase db;
    QSqlQuery Query;
    QString Uni;
};
#endif // SQLCOMMANDBASE_H
