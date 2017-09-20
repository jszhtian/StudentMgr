#include "sqlfactory.h"

inline bool insertSecurityCheck(QString Str)
{
    return !(Str.contains(";")||Str.contains(",")||Str.contains("}")||Str.contains(")")||Str.contains("]"));
}



SQLCommandBase *SQLFactory::CreateSQLCommand(QString COMname)
{
    if(COMname.toLower()=="listlecture")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new listlecture;
    }
    if(COMname.toLower()=="listlectureuid")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new listlectureuid;
    }
    if(COMname.toLower()=="insertlecture")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new insertlecture;
    }
    if(COMname.toLower()=="insertlecturemap")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new insertlecturemap;
    }
    if(COMname.toLower()=="deletelecture")
    {
        return new deletelecture;
    }
    if(COMname.toLower()=="deletelecturemap")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new deletelecturemap;
    }
    if(COMname.toLower()=="updatelecture")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new updatelecture;
    }
    if(COMname.toLower()=="listlecturemap")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new listLectureMap;
    }
    if(COMname.toLower()=="listmajor")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new listmajor;
    }
    if(COMname.toLower()=="listmajoruid")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new listmajoruid;
    }
    if(COMname.toLower()=="insertmajor")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new insertmajor;
    }
    if(COMname.toLower()=="deletemajor")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new deletemajor;
    }
    if(COMname.toLower()=="updatemajor")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new updatemajor;
    }
    if(COMname.toLower()=="listlectureselect")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new listLectureSelect;
    }
    if(COMname.toLower()=="insertlectureselect")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new insertlectureselect;
    }
    if(COMname.toLower()=="deletelectureselect")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new deletelectureselect;
    }
    if(COMname.toLower()=="liststudent")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new liststudent;
    }
    if(COMname.toLower()=="insertstudent")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new insertstudent;
    }
    if(COMname.toLower()=="deletestudent")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new deletestudent;
    }
    if(COMname.toLower()=="updatestudent")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new updatestudent;
    }
    if(COMname.toLower()=="listexam")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new listexam;
    }
    if(COMname.toLower()=="updateexam")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new updateexam;
    }
    if(COMname.toLower()=="deleteexam")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new deleteexam;
    }
    if(COMname.toLower()=="insertexam")
    {
        qDebug()<<"Call Function "<<COMname;
        wcout<<"Call Function "<<COMname.toStdWString()<<endl;
        return new insertexam;
    }
    return NULL;
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
                QString result;
                for(int i=0;i<6;i++)
                {
                    result+=Query.value(i).toString().simplified()+",";
                }
                output->ExchangeData->append(result);
            }
            return true;
        }
        if(Uni=="UDE")
        {
            output->Type="UDELecture";
            while(Query.next())
            {
                QString result;
                for(int i=0;i<6;i++)
                {
                    result+=Query.value(i).toString().simplified()+",";
                }
                output->ExchangeData->append(result);
            }
            return true;
        }
        return false;
    }
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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


bool deletelecture::inputdata(shared_ptr<queryexchange> input)
{
    if (input->Type.toLower()!="deletelecture")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";

        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
        }
        Query.prepare("DELETE FROM [dbo].[LectureinUDE] where [LectureUUID]=:UID");
        QString tmp=input->ExchangeData->at(1);
        Query.bindValue(0,tmp);
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";

        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
        }
        Query.prepare("DELETE FROM [dbo].[LectureinZZU] where [LectureUUID]=:UID");
        QString tmp=input->ExchangeData->at(1);
        Query.bindValue(0,tmp);
        return true;
    }
    return false;
}

bool deletelecture::outputdata(shared_ptr<queryexchange> output)
{
    return true;
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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
                QString result;
                for(int i=0;i<4;i++)
                {
                    result+=Query.value(i).toString().simplified()+",";
                }
                output->ExchangeData->append(result);
            }
            return true;
        }
        if(Uni=="UDE")
        {
            output->Type="UDEMajor";
            while(Query.next())
            {
                QString result;
                for(int i=0;i<3;i++)
                {
                    result+=Query.value(i).toString().simplified()+",";
                }
                output->ExchangeData->append(result);
            }
            return true;
        }
        return false;
    }
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
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
    for(int i=0;i<input->ExchangeData->size();++i)
    {
        if(!(insertSecurityCheck(input->ExchangeData->at(i))))
        {
            cout<<"Illegal character detected!"<<endl;
            qDebug()<<"Illegal character detected!";
            return false;
        }
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



bool insertlectureselect::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="insertlectureselect")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
        }
        QString Major=input->ExchangeData->at(1);
        QString Lecture=input->ExchangeData->at(2);
        Query.prepare("INSERT INTO [dbo].[UDELectureSelect] ([MajorUUID],[LectureUUID]) VALUES (:major,:lecture)");
        Query.bindValue(0,Major);
        Query.bindValue(1,Lecture);
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
        }
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
        QString result;
        for(int i=0;i<11;i++)
        {
            result+=Query.value(i).toString().simplified()+",";
        }
        output->ExchangeData->append(result);
    }
    return true;
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



bool listexam::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="listexam")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        Query.prepare("SELECT [ExamUUID] ,[Name],Student.StudentID ,[LectureName]  ,[Examscore] ,[Examnote] ,[UDEExam].Semester ,[Examdatestamp] FROM [dbo].[UDEExam], [dbo].LectureinUDE,[dbo].Student where [UDEExam].StudentUUID=Student.StudentUUID and [UDEExam].LectureUUID=LectureinUDE.LectureUUID");
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        //Query.prepare("SELECT [ExamUUID] ,Student.Name,Student.StudentID ,LectureinZZU.LectureName ,LectureinUDE.LectureName ,LectureinZZU.Type,[Examscore] ,[Examnote],[ZZUExam].[Semester],[Examdatestamp] FROM [dbo].[ZZUExam],[dbo].LectureinZZU,[dbo].LectureinUDE,dbo.LectureMap,dbo.Student where ZZUExam.LectureUUID=LectureinZZU.LectureUUID and LectureMap.UDELectureUUID=LectureinUDE.LectureUUID and LectureMap.ZZULectureUUID=LectureinZZU.LectureUUID and ZZUExam.StudentUUID=Student.StudentUUID");
        Query.prepare("SELECT [ExamUUID] ,Student.Name,Student.StudentID ,LectureinZZU.LectureName ,LectureinUDE.LectureName ,LectureinZZU.Type,[Examscore] ,[Examnote],[ZZUExam].[Semester],[Examdatestamp] FROM ZZUExam left join Student on (ZZUExam.StudentUUID=Student.StudentUUID) left join LectureinZZU on (ZZUExam.LectureUUID=LectureinZZU.LectureUUID) left join LectureMap on (LectureMap.ZZULectureUUID=ZZUExam.LectureUUID) left join LectureinUDE on (LectureMap.UDELectureUUID=LectureinUDE.LectureUUID)");
        return true;
    }
    if(input->ExchangeData->at(0)=="SelectExam")
    {
        Uni="SelExam";
        Query.prepare("SELECT [ExamUUID],[Student].[name],Student.StudentID,[Examscore],[type],[Examdatestamp] FROM [dbo].[SelectionExam],[dbo].[Student] where [SelectionExam].StudentUUID=Student.StudentUUID");
        return true;
    }
    return false;
}

bool listexam::outputdata(shared_ptr<queryexchange> output)
{
    if(Uni.isEmpty())
    {
        return false;
    }
    if(Uni=="UDE")
    {
        output->Type="UDEExam";
        while(Query.next())
        {
            QString result=Query.value(0).toString().simplified()+",";
            result+=Query.value(1).toString().simplified()+",";
            result+=Query.value(2).toString().simplified()+",";
            result+=Query.value(3).toString().simplified()+",";
            result+=Query.value(4).toString().simplified()+",";
            result+=Query.value(5).toString().simplified()+",";
            result+=Query.value(6).toString().simplified()+",";
            result+=Query.value(7).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            output->ExchangeData->append(result);
        }
        return true;
    }
    if(Uni=="ZZU")
    {
        output->Type="ZZUExam";
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
            result+=Query.value(9).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            output->ExchangeData->append(result);
        }
        return true;
    }
    if(Uni=="SelExam")
    {
        output->Type="SelExam";
        while(Query.next())
        {
            QString result=Query.value(0).toString().simplified()+",";
            result+=Query.value(1).toString().simplified()+",";
            result+=Query.value(2).toString().simplified()+",";
            result+=Query.value(3).toString().simplified()+",";
            result+=Query.value(4).toString().simplified()+",";
            result+=Query.value(5).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            output->ExchangeData->append(result);
        }
        return true;
    }
    return false;
}


bool insertexam::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="insertexam")
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
        }
        Query.prepare("INSERT INTO [dbo].[UDEExam]([StudentUUID] ,[LectureUUID],[Examscore],[Examnote],[Semester],[Examdatestamp]) VALUES (:UID,:LID,:Score,:Note,:semester,:date)");
        Query.bindValue(0,input->ExchangeData->at(1));
        Query.bindValue(1,input->ExchangeData->at(2));
        Query.bindValue(2,input->ExchangeData->at(3).toDouble());
        Query.bindValue(3,input->ExchangeData->at(4).toDouble());
        Query.bindValue(4,input->ExchangeData->at(5).toInt());
        Query.bindValue(5,QDateTime::fromString(input->ExchangeData->at(6),"yyyy-MM-dd hh:mm:ss"));
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
        for(int i=0;i<input->ExchangeData->size();++i)
        {
            if(!(insertSecurityCheck(input->ExchangeData->at(i))))
            {
                cout<<"Illegal character detected!"<<endl;
                qDebug()<<"Illegal character detected!";
                return false;
            }
        }
        Query.prepare("INSERT INTO [dbo].[ZZUExam]([StudentUUID],[LectureUUID],[Examscore] ,[Examnote] ,[Semester],[Examdatestamp]) VALUES( :UID,:LID ,:score,:note,:semester ,:date)");
        Query.bindValue(0,input->ExchangeData->at(1));
        Query.bindValue(1,input->ExchangeData->at(2));
        Query.bindValue(2,input->ExchangeData->at(3).toDouble());
        Query.bindValue(3,input->ExchangeData->at(4).toDouble());
        Query.bindValue(4,input->ExchangeData->at(5).toInt());
        Query.bindValue(5,QDateTime::fromString(input->ExchangeData->at(6),"yyyy-MM-dd hh:mm:ss"));
        return true;
    }
    if(input->ExchangeData->at(0)=="SelectExam")
    {
        Uni="SelExam";
        if(input->ExchangeData->size()!=5)
        {
            wcout<<"insertlecture:Not match number of parameters!";
            qDebug()<<"insertlecture:Not match number of parameters!";
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
        Query.prepare("INSERT INTO [dbo].[SelectionExam]([StudentUUID] ,[Examscore],[type],[Examdatestamp])VALUES (:UID,:score,:type,:data)");
        Query.bindValue(0,input->ExchangeData->at(1));
        Query.bindValue(1,input->ExchangeData->at(2).toDouble());
        Query.bindValue(2,input->ExchangeData->at(3));
        Query.bindValue(3,QDateTime::fromString(input->ExchangeData->at(4),"yyyy-MM-dd hh:mm:ss"));
        return true;
    }
    return false;
}

bool insertexam::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}


bool deleteexam::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="deleteexam")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        QString UID=input->ExchangeData->at(1);
        Query.prepare("DELETE FROM [dbo].[UDEExam] WHERE ExamUUID=:UID");
        Query.bindValue(0,UID);
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        QString UID=input->ExchangeData->at(1);
        Query.prepare("DELETE FROM [dbo].[ZZUExam] WHERE ExamUUID=:UID");
        Query.bindValue(0,UID);
        return true;
    }
    if(input->ExchangeData->at(0)=="SelectExam")
    {
        Uni="SelExam";
        QString UID=input->ExchangeData->at(1);
        Query.prepare("DELETE FROM [dbo].[SelectionExam] WHERE ExamUUID=:UID");
        Query.bindValue(0,UID);
        return true;
    }
    return false;
}

bool deleteexam::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}


bool updateexam::inputdata(shared_ptr<queryexchange> input)
{
    if(input->Type.toLower()!="updateexam")
    {
        return false;
    }
    if(input->ExchangeData->at(0)=="UDE")
    {
        Uni="UDE";
        if(input->ExchangeData->size()!=8)
        {
            wcout<<"insertlecture:Not match number of parameters!";
            qDebug()<<"insertlecture:Not match number of parameters!";
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
        Query.prepare("UPDATE [dbo].[UDEExam] SET [StudentUUID] = :uid,[LectureUUID] = :lid,[Examscore] = :score,[Examnote] = :note,[Semester] =:semester ,[Examdatestamp] =:date WHERE [ExamUUID] = :examid");
        Query.bindValue(0,input->ExchangeData->at(2));
        Query.bindValue(1,input->ExchangeData->at(3));
        Query.bindValue(2,input->ExchangeData->at(4).toDouble());
        Query.bindValue(3,input->ExchangeData->at(5).toDouble());
        Query.bindValue(4,input->ExchangeData->at(6).toInt());
        Query.bindValue(5,QDateTime::fromString(input->ExchangeData->at(7),"yyyy-MM-dd hh:mm:ss"));
        Query.bindValue(6,input->ExchangeData->at(1));
        return true;
    }
    if(input->ExchangeData->at(0)=="ZZU")
    {
        Uni="ZZU";
        if(input->ExchangeData->size()!=8)
        {
            wcout<<"insertlecture:Not match number of parameters!";
            qDebug()<<"insertlecture:Not match number of parameters!";
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
        Query.prepare("UPDATE [dbo].[ZZUExam] SET [StudentUUID] = :uid,[LectureUUID] = :lid,[Examscore] = :score,[Examnote] = :note,[Semester] =:semester ,[Examdatestamp] =:date WHERE [ExamUUID] = :examid");
        Query.bindValue(0,input->ExchangeData->at(2));
        Query.bindValue(1,input->ExchangeData->at(3));
        Query.bindValue(2,input->ExchangeData->at(4).toDouble());
        Query.bindValue(3,input->ExchangeData->at(5).toDouble());
        Query.bindValue(4,input->ExchangeData->at(6).toInt());
        Query.bindValue(5,QDateTime::fromString(input->ExchangeData->at(7),"yyyy-MM-dd hh:mm:ss"));
        Query.bindValue(6,input->ExchangeData->at(1));
        return true;
    }
    if(input->ExchangeData->at(0)=="SelectExam")
    {
        Uni="SelExam";
        if(input->ExchangeData->size()!=6)
        {
            wcout<<"insertlecture:Not match number of parameters!";
            qDebug()<<"insertlecture:Not match number of parameters!";
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
        Query.prepare("UPDATE [dbo].[SelectionExam] SET [StudentUUID] = :UID,[Examscore] = :LID,[type] = :type,[Examdatestamp] = :date WHERE [ExamUUID] = :examID");
        Query.bindValue(0,input->ExchangeData->at(2));
        Query.bindValue(1,input->ExchangeData->at(3).toDouble());
        Query.bindValue(2,input->ExchangeData->at(4));
        Query.bindValue(3,QDateTime::fromString(input->ExchangeData->at(5),"yyyy-MM-dd hh:mm:ss"));
        Query.bindValue(4,input->ExchangeData->at(1));
        return true;
    }
    return false;
}

bool updateexam::outputdata(shared_ptr<queryexchange> output)
{
    return true;
}


