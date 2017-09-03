#include "sqlfactory.h"



bool listlecture::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type!="ListLecture")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Query.prepare("select [LectureUUID],[LectureName],[Type],[Module],[CreditinUDE],[Teachinghours] from [ZZU-DB].[dbo].[LectureinZZU]");
        Uni="ZZU";
        return true;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Query.prepare("select [LectureUUID],[LectureName],[Semester],[Module],[EACTSCredit],[Teachinghours] from [ZZU-DB].[dbo].[LectureinUDE]");
        Uni="UDE";
        return true;
    }
    return false;
}

bool listlecture::outputdata(shared_ptr<queryexchange> output)
{
    if(Uni.isEmpty())
    {
        return false;
    }
    else
    {
        if(Uni=="ZZU")
        {
            output->Type="ZZULecture";
            while(Query.next())
            {
                QString result=Query.value(0).toString().simplified()+",";
                result+=Query.value(1).toString().simplified()+",";
                result+=Query.value(2).toString().simplified()+",";
                result+=Query.value(3).toString().simplified()+",";
                result+=Query.value(4).toString().simplified()+",";
                result+=Query.value(5).toString().simplified();
                output->ExchangeData->append(result);
            }
        }
        if(Uni=="UDE")
        {
            output->Type="UDELecture";
            while(Query.next())
            {
                QString result=Query.value(0).toString().simplified()+",";
                result+=Query.value(1).toString().simplified()+",";
                result+=Query.value(2).toString().simplified()+",";
                result+=Query.value(3).toString().simplified()+",";
                result+=Query.value(4).toString().simplified()+",";
                result+=Query.value(5).toString().simplified();
                output->ExchangeData->append(result);
            }
        }
        return false;
    }
}

inline void listlecture::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool listlecture::exec()
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

SQLCommandBase *SQLFactory::CreateSQLCommand(QString COMname)
{
    if(COMname.toLower()=="listlecture")
    {
        return new listlecture;
    }
    return NULL;
}
