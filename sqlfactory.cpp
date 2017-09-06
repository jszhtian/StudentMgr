#include "sqlfactory.h"

inline bool insertSecurityCheck(QString Str)
{
    return !(Str.contains(";")||Str.contains(",")||Str.contains("}")||Str.contains(")")||Str.contains("]"));
}

bool listlecture::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="listlecture")
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
    if(COMname.toLower()=="listmajor")
    {
        return new listmajor;
    }
    if(COMname.toLower()=="listmajoruid")
    {
        return new listmajoruid;
    }
    if(COMname.toLower()=="insertmajor")
    {
        return new insertmajor;
    }
    if(COMname.toLower()=="deletemajor")
    {
        return new deletemajor;
    }
    if(COMname.toLower()=="updatemajor")
    {
        return new updatemajor;
    }
    if(COMname.toLower()=="listlectureselect")
    {
        return new listLectureSelect;
    }
    if(COMname.toLower()=="insertlectureselect")
    {
        return new insertlectureselect;
    }
    if(COMname.toLower()=="deletelectureselect")
    {
        return new deletelectureselect;
    }
    if(COMname.toLower()=="liststudent")
    {
        return new liststudent;
    }
    if(COMname.toLower()=="insertstudent")
    {
        return new insertstudent;
    }
    if(COMname.toLower()=="deletestudent")
    {
        return new deletestudent;
    }
    if(COMname.toLower()=="updatestudent")
    {
        return new updatestudent;
    }
    return NULL;
}



bool listlectureuid::inputdata(shared_ptr<queryexchange> input)
{
    if (input->Type.toLower()!="listlectureuid")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        Query.prepare("select [LectureUUID],[LectureName] from [ZZU-DB].[dbo].[LectureinUDE]");
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        Query.prepare("select [LectureUUID],[LectureName] from [ZZU-DB].[dbo].[LectureinZZU]");
        return true;
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
        return true;
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
        return true;
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
    if (input->Type.toLower()!="insertlecture")
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
        return true;

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
        return true;

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
    if (input->Type.toLower()!="deletelecture")
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
        return true;
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
        return true;
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
    if (input->Type.toLower()!="updatelecture")
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
        return true;

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
        return true;

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
    if (input->Type.toLower()!="listlecturemap")
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
        return true;
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
        return true;
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
        return true;
    }
    if(Uni=="UDE")
    {
        output->Type="UDELecture";
        while(Query.next())
        {
            QString result=Query.value(0).toString().simplified();
            output->ExchangeData->append(result);
        }
        return true;
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
    if (input->Type.toLower()!="insertlecturemap")
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
        return true;
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
        return true;
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
    if (input->Type.toLower()!="deletelecturemap")
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
        return true;
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
        return true;
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
    if (input->Type.toLower()!="listmajor")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        Query.prepare("SELECT [MajorUUID] ,[MajorName] ,[Supervisor] FROM [dbo].[MajorinUDE]");
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        Query.prepare("SELECT [MajorUUID],[MajorName],[Supervisor],[MajorinUDE] FROM [dbo].[MajorinZZU]");
        return true;
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
            return true;
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
            return true;
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
    if (input->Type.toLower()!="listmajoruid")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        Query.prepare("select [MajorUUID],[MajorName] from [ZZU-DB].[dbo].[MajorinUDE]");
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        Query.prepare("select [MajorUUID],[MajorName] from [ZZU-DB].[dbo].[MajorinZZU]");
        return true;
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
        return true;
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
        return true;
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

bool insertmajor::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="insertmajor")
    {
        return false;
    }

    if(input->ExchangeData->at(0)=="UDE")
    {
        if(input->ExchangeData->size()!=3)
        {
            qDebug()<<"Wrong Parameter";
            wcout<<"Wrong Parameter"<<endl;
            return false;
        }
        QString name=input->ExchangeData->at(1);
        QString supervisor=input->ExchangeData->at(2);
        Query.prepare("INSERT INTO [dbo].[MajorinUDE]([MajorName],[Supervisor])VALUES(:name,:supervisor)");
        Query.bindValue(0,name);
        Query.bindValue(1,supervisor);
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        if(input->ExchangeData->size()!=4)
        {
            qDebug()<<"Wrong Parameter";
            wcout<<"Wrong Parameter"<<endl;
            return false;
        }
        QString name=input->ExchangeData->at(1);
        QString supervisor=input->ExchangeData->at(2);
        QString UID=input->ExchangeData->at(3);
        Query.prepare("INSERT INTO [dbo].[MajorinZZU]([MajorName],[Supervisor],[MajorinUDE])VALUES(:name,:supervisor,:UID)");
        Query.bindValue(0,name);
        Query.bindValue(1,supervisor);
        Query.bindValue(2,UID);
        return true;
    }
    return false;
}

bool insertmajor::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void insertmajor::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool insertmajor::exec()
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

bool deletemajor::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="deletemajor")
    {
        return false;
    }
    if(input->ExchangeData->size()!=2)
    {
        qDebug()<<"Wrong Parameter";
        wcout<<"Wrong Parameter"<<endl;
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        QString UID=input->ExchangeData->at(1);
        Query.prepare("DELETE FROM [dbo].[MajorinUDE] WHERE MajorUUID=:UID");
        Query.bindValue(0,UID);
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        QString UID=input->ExchangeData->at(1);
        Query.prepare("DELETE FROM [dbo].[MajorinZZU] WHERE MajorUUID=:UID");
        Query.bindValue(0,UID);
        return true;
    }
    return false;
}

bool deletemajor::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void deletemajor::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool deletemajor::exec()
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

bool updatemajor::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="updatemajor")
    {
        return false;
    }

    if(input->ExchangeData->at(0)=="UDE")
    {
        if(input->ExchangeData->size()!=4)
        {
            qDebug()<<"Wrong Parameter";
            wcout<<"Wrong Parameter"<<endl;
            return false;
        }
        QString UID=input->ExchangeData->at(1);
        QString name=input->ExchangeData->at(2);
        QString supervisor=input->ExchangeData->at(3);
        Query.prepare("UPDATE [dbo].[MajorinUDE] SET [MajorName] = :name,[Supervisor] = :visor WHERE [MajorUUID]=:UID");
        Query.bindValue(0,name);
        Query.bindValue(1,supervisor);
        Query.bindValue(2,UID);
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        if(input->ExchangeData->size()!=5)
        {
            qDebug()<<"Wrong Parameter";
            wcout<<"Wrong Parameter"<<endl;
            return false;
        }
        QString UID=input->ExchangeData->at(1);
        QString name=input->ExchangeData->at(2);
        QString supervisor=input->ExchangeData->at(3);
        QString UDEUID=input->ExchangeData->at(4);
        Query.prepare("UPDATE [dbo].[MajorinZZU]  SET [MajorName] = :name,[Supervisor] = :visor,[MajorinUDE] = :UDEUID WHERE [MajorUUID] = :uid");
        Query.bindValue(0,name);
        Query.bindValue(1,supervisor);
        Query.bindValue(2,UDEUID);
        Query.bindValue(3,UID);
        return true;
    }
    return false;
}

bool updatemajor::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void updatemajor::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool updatemajor::exec()
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

bool listLectureSelect::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="listlectureselect")
    {
        return false;
    }
    if(input->ExchangeData->size()!=2)
    {
        qDebug()<<"Wrong Parameter";
        wcout<<"Wrong Parameter"<<endl;
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        QString UID=input->ExchangeData->at(1);
        Query.prepare("SELECT [LectureName]  FROM [dbo].[UDELectureSelect],[dbo].[LectureinUDE]  where [UDELectureSelect].LectureUUID=[LectureinUDE].LectureUUID and [MajorUUID]=:UID");
        Query.bindValue(0,UID);
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        QString UID=input->ExchangeData->at(1);
        Query.prepare("SELECT [LectureName]  FROM [dbo].[ZZULectureSelect],[dbo].[LectureinZZU]  where [ZZULectureSelect].LectureUUID=LectureinZZU.LectureUUID and MajorUUID=:UID");
        Query.bindValue(0,UID);
        return true;
    }
    return false;
}

bool listLectureSelect::outputdata(shared_ptr<queryexchange> output)
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
        return true;
    }
    if(Uni=="UDE")
    {
        output->Type="UDELecture";
        while(Query.next())
        {
            QString result=Query.value(0).toString().simplified();
            output->ExchangeData->append(result);
        }
        return true;
    }
    return false;
}

void listLectureSelect::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool listLectureSelect::exec()
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

bool insertlectureselect::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="insertlectureselect")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        QString Major=input->ExchangeData->at(1);
        QString Lecture=input->ExchangeData->at(2);
        Query.prepare("INSERT INTO [dbo].[UDELectureSelect] ([MajorUUID],[LectureUUID]) VALUES (:major,:lecture)");
        Query.bindValue(0,Major);
        Query.bindValue(1,Lecture);
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        QString Major=input->ExchangeData->at(1);
        QString Lecture=input->ExchangeData->at(2);
        Query.prepare("INSERT INTO [dbo].[ZZULectureSelect] ([MajorUUID],[LectureUUID]) VALUES (:major,:lecture)");
        Query.bindValue(0,Major);
        Query.bindValue(1,Lecture);
        return true;
    }
    return false;
}

bool insertlectureselect::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void insertlectureselect::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool insertlectureselect::exec()
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

bool deletelectureselect::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="deletelectureselect")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        QString Major=input->ExchangeData->at(1);
        QString Lecture=input->ExchangeData->at(2);
        Query.prepare("DELETE FROM [dbo].[UDELectureSelect] WHERE MajorUUID=:major and LectureUUID=:lecture");
        Query.bindValue(0,Major);
        Query.bindValue(1,Lecture);
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        QString Major=input->ExchangeData->at(1);
        QString Lecture=input->ExchangeData->at(2);
        Query.prepare("DELETE FROM [dbo].[ZZULectureSelect] WHERE MajorUUID=:major and LectureUUID=:lecture");
        Query.bindValue(0,Major);
        Query.bindValue(1,Lecture);
        return true;
    }
    return false;
}

bool deletelectureselect::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void deletelectureselect::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool deletelectureselect::exec()
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

bool liststudent::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="liststudent")
    {
        return false;
    }
    else
    {
        Query.prepare("SELECT [StudentUUID],[StudentID],[Name],[Birthday],[IDNumber],[Class],[Gender],[Grade],[StudO],MajorinZZU.MajorName,MajorinUDE.MajorName FROM [dbo].[Student],[dbo].[MajorinUDE],[dbo].MajorinZZU  WHERE Student.MajorUUID=MajorinZZU.MajorUUID and MajorinZZU.MajorinUDE=MajorinUDE.MajorUUID");
        return true;
    }
}

bool liststudent::outputdata(shared_ptr<queryexchange> output)
{
    while(Query.next())
    {
        QString result=Query.value(0).toString().simplified()+",";
        result+=Query.value(1).toString().simplified()+",";
        result+=Query.value(2).toString().simplified()+",";
        result+=Query.value(3).toString().simplified()+",";
        result+=Query.value(4).toString().simplified()+",";
        result+=Query.value(5).toString().simplified()+",";
        result+=Query.value(6).toString().simplified()+",";
        result+=Query.value(7).toString().simplified()+",";
        result+=Query.value(8).toString().simplified()+",";
        result+=Query.value(9).toString().simplified()+",";
        result+=Query.value(10).toString().simplified();
        output->ExchangeData->append(result);
    }
    return true;
}

void liststudent::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool liststudent::exec()
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

bool insertstudent::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="insertstudent")
    {
        return false;
    }
    else
    {
        if(input->ExchangeData->size()!=9)
        {
            qDebug()<<"Wrong Parameter";
            wcout<<"Wrong Parameter"<<endl;
            return false;
        }
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
        }
        QString StdID=input->ExchangeData->at(0);
        QString name=input->ExchangeData->at(1);
        QString birthday=input->ExchangeData->at(2);
        QString IDnum=input->ExchangeData->at(3);
        QString Class=input->ExchangeData->at(4);
        QString Gender=input->ExchangeData->at(5);
        QString grade=input->ExchangeData->at(6);
        QString studo=input->ExchangeData->at(7);
        QString MajorUUID=input->ExchangeData->at(8);
        Query.prepare("INSERT INTO [dbo].[Student]([StudentID],[Name],[Birthday],[IDNumber],[Class],[Gender],[Grade],[StudO],[MajorUUID]) VALUES (:StdID,:name,:birth,:idnum,:class,:gender,:grader,:studO,:majorinZZU)");
        Query.bindValue(0,StdID);
        Query.bindValue(1,name);
        Query.bindValue(2,birthday);
        Query.bindValue(3,IDnum);
        Query.bindValue(4,Class);
        Query.bindValue(5,Gender);
        Query.bindValue(6,grade);
        Query.bindValue(7,studo);
        Query.bindValue(8,MajorUUID);
        return true;
    }
}

bool insertstudent::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void insertstudent::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool insertstudent::exec()
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

bool deletestudent::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="deletestudent")
    {
        return false;
    }
    else
    {
        QString UID=input->ExchangeData->at(0);
        Query.prepare("DELETE FROM [dbo].[Student] WHERE StudentUUID=:uid");
        Query.bindValue(0,UID);
        return true;
    }
}

bool deletestudent::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void deletestudent::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool deletestudent::exec()
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

bool updatestudent::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="updatestudent")
    {
        return false;
    }
    else
    {
        if(input->ExchangeData->size()!=10)
        {
            qDebug()<<"Wrong Parameter";
            wcout<<"Wrong Parameter"<<endl;
            return false;
        }
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
        }
        QString stdUUID=input->ExchangeData->at(0);
        QString StdID=input->ExchangeData->at(1);
        QString name=input->ExchangeData->at(2);
        QString birthday=input->ExchangeData->at(3);
        QString IDnum=input->ExchangeData->at(4);
        QString Class=input->ExchangeData->at(5);
        QString Gender=input->ExchangeData->at(6);
        QString grade=input->ExchangeData->at(7);
        QString studo=input->ExchangeData->at(8);
        QString MajorUUID=input->ExchangeData->at(9);
        Query.prepare("UPDATE [dbo].[Student] SET [StudentID] = :stdID ,[Name] = :name,[Birthday] = :birth,[IDNumber] = :idnum,[Class] = :class ,[Gender] = :gender ,[Grade] = :grade ,[StudO] = :studo ,[MajorUUID] = :major WHERE [StudentUUID] =:uid");
        Query.bindValue(0,StdID);
        Query.bindValue(1,name);
        Query.bindValue(2,birthday);
        Query.bindValue(3,IDnum);
        Query.bindValue(4,Class);
        Query.bindValue(5,Gender);
        Query.bindValue(6,grade);
        Query.bindValue(7,studo);
        Query.bindValue(8,MajorUUID);
        Query.bindValue(9,stdUUID);
        return true;
    }
}

bool updatestudent::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}

void updatestudent::setdb(QSqlDatabase setdb)
{
    db=setdb;
}

bool updatestudent::exec()
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
