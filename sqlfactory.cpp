#include "sqlfactory.h"



bool listlecture::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type!="ListLecture")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Query.prepare("select [LectureUUID],[LectureName],[Type],[Module],[CreditinZZU],[Teachinghours] from [ZZU-DB].[dbo].[LectureinZZU]");
        Uni="ZZU";
        return true;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Query.prepare("select [LectureUUID],[LectureName],[Module],[Semester],[EACTSCredit],[Teachinghours] from [ZZU-DB].[dbo].[LectureinUDE]");
        Uni="DUE";
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

inline void listlecture::setdb(QSqlDatabase *setdb)
{
    db=setdb;
}

bool listlecture::exec()
{
    QProgressDialog progressDlg;
    progressDlg.setWindowModality(Qt::WindowModal);
    progressDlg.setMinimum(0);
    progressDlg.setMaximum(0);
    progressDlg.setLabelText("Listing...");
    progressDlg.setCancelButton(0);
    progressDlg.setWindowFlags(progressDlg.windowFlags()&~Qt::WindowCloseButtonHint);
    progressDlg.show();
    //change to multi thread method
    auto m_thread=new thdSQLExec();
    //connect thread signal->mainwindow slot
    m_thread->setDatebase(db);
    m_thread->setquery(&Query);
    m_thread->start();
    //m_thread->wait();
    while(!m_thread->isFinished())
    {
        qApp->processEvents();
    }
    progressDlg.close();
    return m_thread->getresult();
    //disconnect signal/slot connect
}
