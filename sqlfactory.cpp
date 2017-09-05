#include "sqlfactory.h"

inline bool insertSecurityCheck(QString Str)
{
    return !(Str.contains(";")||Str.contains(",")||Str.contains("}")||Str.contains(")")||Str.contains("]"));
}

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
    if(COMname.toLower()=="listlectureuid")
    {
        return new listlectureuid;
    }
    if(COMname.toLower()=="insertlecture")
    {
        return new insertlecture;
    }
    if(COMname.toLower()=="insertlecturemap")
    {
        return new insertlecturemap;
    }
    if(COMname.toLower()=="deletelecture")
    {
        return new deletelecture;
    }
    if(COMname.toLower()=="deletelecturemap")
    {
        return new deletelecturemap;
    }
    if(COMname.toLower()=="updatelecture")
    {
        return new updatelecture;
    }
    if(COMname.toLower()=="listlecturemap")
    {
        return new listLectureMap;
    }
    return NULL;
}



bool listlectureuid::inputdata(shared_ptr<queryexchange> input)
{
    if (input->Type!="listlectureuid")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        Query.prepare("select [LectureUUID],[LectureName] from [ZZU-DB].[dbo].[LectureinUDE]");
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        Query.prepare("select [LectureUUID],[LectureName] from [ZZU-DB].[dbo].[LectureinZZU]");
    }
    return false;
}

bool listlectureuid::outputdata(shared_ptr<queryexchange> output)
{
    if(Uni.isEmpty())
    {
        return false;
    }
    if(Uni=="ZZU")
    {
        output->Type="ZZULecture";
        while(Query.next())
        {
            QString result=Query.value(0).toString().simplified()+",";
            result+=Query.value(1).toString().simplified();
            output->ExchangeData->append(result);
        }
    }
    if(Uni=="UDE")
    {
        output->Type="UDELecture";
        while(Query.next())
        {
            QString result=Query.value(0).toString().simplified()+",";
            result+=Query.value(1).toString().simplified();
            output->ExchangeData->append(result);
        }
    }
    return false;
}

void listlectureuid::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool listlectureuid::exec()
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

bool insertlecture::inputdata(shared_ptr<queryexchange> input)
{
    if (input->Type!="insertlecture")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        if(input->ExchangeData->size()!=6)
        {
            wcout<<"insertlecture:Not match number of parameters!";
            qDebug()<<"insertlecture:Not match number of parameters!";
        }
        QString LectureName=input->ExchangeData->at(1);
        QString Semester=input->ExchangeData->at(2);
        QString Module=input->ExchangeData->at(3);
        QString EACTSCredit=input->ExchangeData->at(4);
        QString Teachinghours=input->ExchangeData->at(5);
        if(!insertSecurityCheck(LectureName))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Semester))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Module))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(EACTSCredit))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Teachinghours))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.prepare("INSERT INTO [dbo].[LectureinUDE]([LectureName],[Module],[Semester],[EACTSCredit],[Teachinghours])VALUES(:LectureName,:Module,:Semester,:EACTSCredit,:Teachinghours)");
        Query.bindValue(0,LectureName);
        Query.bindValue(1,Module.toInt());
        Query.bindValue(2,Semester.toInt());
        Query.bindValue(3,EACTSCredit.toDouble());
        Query.bindValue(4,Teachinghours.toInt());

    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        if(input->ExchangeData->size()!=6)
        {
            wcout<<"insertlecture:Not match number of parameters!";
            qDebug()<<"insertlecture:Not match number of parameters!";
        }
        QString LectureName=input->ExchangeData->at(1);
        QString Type=input->ExchangeData->at(2);
        QString Module=input->ExchangeData->at(3);
        QString CreditinUDE=input->ExchangeData->at(4);
        QString Teachinghours=input->ExchangeData->at(5);
        if(!insertSecurityCheck(LectureName))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Type))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Module))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(CreditinUDE))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Teachinghours))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.prepare("INSERT INTO [dbo].[LectureinZZU]([LectureName],[Module],[Type],[CreditinUDE],[Teachinghours])VALUES(:LectureName,:Module,:Type,:CreditinUDE,:Teachinghours)");
        Query.bindValue(0,LectureName);
        Query.bindValue(1,Module.toInt());
        Query.bindValue(2,Type);
        Query.bindValue(3,CreditinUDE.toDouble());
        Query.bindValue(4,Teachinghours.toInt());

    }
    return false;
}

bool insertlecture::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void insertlecture::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool insertlecture::exec()
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

bool deletelecture::inputdata(shared_ptr<queryexchange> input)
{
    if (input->Type!="deletelecture")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        Query.prepare("DELETE FROM [dbo].[LectureinUDE] where [LectureUUID]=:UID");
        QString tmp=input->ExchangeData->at(1);
        if(!insertSecurityCheck(tmp))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.bindValue(0,tmp);
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        Query.prepare("DELETE FROM [dbo].[LectureinZZU] where [LectureUUID]=:UID");
        QString tmp=input->ExchangeData->at(1);
        if(!insertSecurityCheck(tmp))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.bindValue(0,tmp);
    }
    return false;
}

bool deletelecture::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void deletelecture::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool deletelecture::exec()
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

bool updatelecture::inputdata(shared_ptr<queryexchange> input)
{
    if (input->Type!="updatelecture")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        if(input->ExchangeData->size()!=7)
        {
            wcout<<"insertlecture:Not match number of parameters!";
            qDebug()<<"insertlecture:Not match number of parameters!";
        }
        QString LectureName=input->ExchangeData->at(1);
        QString Semester=input->ExchangeData->at(2);
        QString Module=input->ExchangeData->at(3);
        QString EACTSCredit=input->ExchangeData->at(4);
        QString Teachinghours=input->ExchangeData->at(5);
        QString UID=input->ExchangeData->at(6);
        if(!insertSecurityCheck(LectureName))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Semester))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Module))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(EACTSCredit))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Teachinghours))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(UID))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.prepare("UPDATE [dbo].[LectureinUDE] SET [LectureName] = :Name,[Module] = :Module,[Semester] = :semester ,[EACTSCredit] = :credit,[Teachinghours] = :hours WHERE [LectureUUID]=:UID");
        Query.bindValue(0,LectureName);
        Query.bindValue(1,Module.toInt());
        Query.bindValue(2,Semester.toInt());
        Query.bindValue(3,EACTSCredit.toDouble());
        Query.bindValue(4,Teachinghours.toInt());
        Query.bindValue(5,UID);

    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        if(input->ExchangeData->size()!=7)
        {
            wcout<<"insertlecture:Not match number of parameters!";
            qDebug()<<"insertlecture:Not match number of parameters!";
        }
        QString LectureName=input->ExchangeData->at(1);
        QString Type=input->ExchangeData->at(2);
        QString Module=input->ExchangeData->at(3);
        QString CreditinUDE=input->ExchangeData->at(4);
        QString Teachinghours=input->ExchangeData->at(5);
        QString UID=input->ExchangeData->at(6);
        if(!insertSecurityCheck(LectureName))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Type))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Module))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(CreditinUDE))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(Teachinghours))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(UID))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.prepare("UPDATE [dbo].[LectureinZZU]   SET [LectureName] = :Name,[Type] = :type,[Module] = :module,[CreditinUDE] = :credit,[Teachinghours] = :hour WHERE [LectureUUID]=:UID");
        Query.bindValue(0,LectureName);
        Query.bindValue(1,Type);
        Query.bindValue(2,Module.toInt());
        Query.bindValue(3,CreditinUDE.toDouble());
        Query.bindValue(4,Teachinghours.toInt());
        Query.bindValue(5,UID);

    }
    return false;
}

bool updatelecture::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void updatelecture::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool updatelecture::exec()
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


bool listLectureMap::inputdata(shared_ptr<queryexchange> input)
{
    if (input->Type!="ListLectureMap")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        QString UID=input->ExchangeData->at(1);
        if(!insertSecurityCheck(UID))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.prepare("SELECT LectureinZZU.LectureName FROM [dbo].[LectureMap],[dbo].LectureinUDE,[dbo].LectureinZZU where ZZULectureUUID=LectureinZZU.LectureUUID and UDELectureUUID=LectureinUDE.LectureUUID and UDELectureUUID=:UID");
        Query.bindValue(0,UID);
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        QString UID=input->ExchangeData->at(1);
        if(!insertSecurityCheck(UID))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.prepare("SELECT LectureinUDE.LectureName FROM [dbo].[LectureMap],[dbo].LectureinUDE,[dbo].LectureinZZU where ZZULectureUUID=LectureinZZU.LectureUUID and UDELectureUUID=LectureinUDE.LectureUUID and ZZULectureUUID=:UID");
        Query.bindValue(0,UID);
    }
    return false;

}

bool listLectureMap::outputdata(shared_ptr<queryexchange> output)
{
    if(Uni.isEmpty())
    {
        return false;
    }
    if(Uni=="ZZU")
    {
        output->Type="ZZULecture";
        while(Query.next())
        {
            QString result=Query.value(0).toString().simplified();
            output->ExchangeData->append(result);
        }
    }
    if(Uni=="UDE")
    {
        output->Type="UDELecture";
        while(Query.next())
        {
            QString result=Query.value(0).toString().simplified();
            output->ExchangeData->append(result);
        }
    }
    return false;
}

void listLectureMap::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool listLectureMap::exec()
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

bool insertlecturemap::inputdata(shared_ptr<queryexchange> input)
{
    if (input->Type!="insertlecturemap")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        QString UID1=input->ExchangeData->at(1);
        QString UID2=input->ExchangeData->at(2);
        if(!insertSecurityCheck(UID1))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(UID2))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.prepare("INSERT INTO [dbo].[LectureMap]([ZZULectureUUID],[UDELectureUUID])VALUES(:UID1,:UID2)");
        Query.bindValue(0,UID2);
        Query.bindValue(1,UID1);
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        QString UID1=input->ExchangeData->at(1);
        QString UID2=input->ExchangeData->at(2);
        if(!insertSecurityCheck(UID1))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(UID2))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.prepare("INSERT INTO [dbo].[LectureMap]([ZZULectureUUID],[UDELectureUUID])VALUES(:UID1,:UID2)");
        Query.bindValue(0,UID1);
        Query.bindValue(1,UID2);
    }
    return false;
}

bool insertlecturemap::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void insertlecturemap::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool insertlecturemap::exec()
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

bool deletelecturemap::inputdata(shared_ptr<queryexchange> input)
{
    if (input->Type!="deletelecturemap")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        QString UID1=input->ExchangeData->at(1);
        QString UID2=input->ExchangeData->at(2);
        if(!insertSecurityCheck(UID1))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(UID2))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.prepare("DELETE FROM [dbo].[LectureMap]WHERE UDELectureUUID=:UID1 and ZZULectureUUID=:UID2");
        Query.bindValue(0,UID1);
        Query.bindValue(1,UID2);
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        QString UID1=input->ExchangeData->at(1);
        QString UID2=input->ExchangeData->at(2);
        if(!insertSecurityCheck(UID1))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        if(!insertSecurityCheck(UID2))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
        Query.prepare("DELETE FROM [dbo].[LectureMap]WHERE ZZULectureUUID=:UID1 and UDELectureUUID=:UID2");
        Query.bindValue(0,UID1);
        Query.bindValue(1,UID2);
    }
    return false;
}

bool deletelecturemap::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void deletelecturemap::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool deletelecturemap::exec()
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

bool listmajor::inputdata(shared_ptr<queryexchange> input)
{
    if (input->Type!="listmajor")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        Query.prepare("SELECT [MajorUUID] ,[MajorName] ,[Supervisor] FROM [dbo].[MajorinUDE]");
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        Query.prepare("SELECT [MajorUUID],[MajorName],[Supervisor],[MajorinUDE] FROM [dbo].[MajorinZZU]");
    }
    return false;
}

bool listmajor::outputdata(shared_ptr<queryexchange> output)
{
    if(Uni.isEmpty())
        {
            return false;
        }
        else
        {
            if(Uni=="ZZU")
            {
                output->Type="ZZUMajor";
                while(Query.next())
                {
                    QString result=Query.value(0).toString().simplified()+",";
                    result+=Query.value(1).toString().simplified()+",";
                    result+=Query.value(2).toString().simplified()+",";
                    result+=Query.value(3).toString().simplified();
                    output->ExchangeData->append(result);
                }
            }
            if(Uni=="UDE")
            {
                output->Type="UDEMajor";
                while(Query.next())
                {
                    QString result=Query.value(0).toString().simplified()+",";
                    result+=Query.value(1).toString().simplified()+",";
                    result+=Query.value(2).toString().simplified();
                    output->ExchangeData->append(result);
                }
            }
            return false;
    }
}

void listmajor::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool listmajor::exec()
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

bool listmajoruid::inputdata(shared_ptr<queryexchange> input)
{
    if (input->Type!="listmajoruid")
        {
            return false;
        }
        if(input->ExchangeData->at(0)=="UDE")
        {
            Uni="UDE";
            Query.prepare("select [MajorUUID],[MajorName] from [ZZU-DB].[dbo].[MajorinUDE]");
        }
        if(input->ExchangeData->at(0)=="ZZU")
        {
            Uni="ZZU";
            Query.prepare("select [MajorUUID],[MajorName] from [ZZU-DB].[dbo].[MajorinZZU]");
        }
        return false;
}

bool listmajoruid::outputdata(shared_ptr<queryexchange> output)
{
    if(Uni.isEmpty())
        {
            return false;
        }
        if(Uni=="ZZU")
        {
            output->Type="ZZUMajor";
            while(Query.next())
            {
                QString result=Query.value(0).toString().simplified()+",";
                result+=Query.value(1).toString().simplified();
                output->ExchangeData->append(result);
            }
        }
        if(Uni=="UDE")
        {
            output->Type="UDEMajor";
            while(Query.next())
            {
                QString result=Query.value(0).toString().simplified()+",";
                result+=Query.value(1).toString().simplified();
                output->ExchangeData->append(result);
            }
        }
        return false;
}

void listmajoruid::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool listmajoruid::exec()
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
