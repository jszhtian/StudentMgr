#include "lecturemapdialog.h"
#include "ui_lecturemapdialog.h"

LectureMapDialog::LectureMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LectureMapDialog)
{
    ui->setupUi(this);
    qDebug()<<"LectureMapDialog create";
    wcout<<"LectureMapDialog create"<<endl;
}

LectureMapDialog::~LectureMapDialog()
{
    delete ui;
    qDebug()<<"ConnectDialog destory";
    wcout<<"ConnectDialog destory"<<endl;
}

void LectureMapDialog::setUni(QString setName)
{
    Uni=setName;
}

void LectureMapDialog::initDB(shared_ptr<SQLBase> setdb)
{
    db=setdb;
}

void LectureMapDialog::setLectUID(QString UID)
{
    lectUID=UID;
}

void LectureMapDialog::prepare()
{
    if(!lectUID.isEmpty()&&db.get()!=NULL)
    {
        on_RefreshButton_clicked();
    }
}

void LectureMapDialog::on_AddBut_clicked()
{
    lectureselectDialog* dlg=new lectureselectDialog(this);
    QString tarUni;
    QString UID;
    QString name;
    if(Uni=="UDE")tarUni="ZZU";
    if(Uni=="ZZU")tarUni="UDE";
    dlg->SetUni(tarUni);
    dlg->initDB(db);
    dlg->prepare();
    if(dlg->Rejected==dlg->exec())
    {
        QMessageBox::information(NULL,"Info","No Selection!");
    }
    else
    {
        UID=dlg->getSelectUID();
        name=dlg->getSelectName();
        auto it=ui->maplist->findItems(name,Qt::MatchExactly);
        if(it.size()==0)
        {
            if(Uni=="UDE")
            {
                SQLFactory factory;
                auto add=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("insertlecturemap"));
                auto input=shared_ptr<queryexchange>(new queryexchange);
                auto inputlist=new QStringList;
                input->Type="insertlecturemap";
                inputlist->append("UDE");
                inputlist->append(lectUID);
                inputlist->append(UID);
                input->ExchangeData=inputlist;
                add->inputdata(input);
                add->setdb(db->getdb());
                auto res=add->exec();
                if(!res)
                {
                    std::wcout<<"Error happens in add map operation!"<<endl;
                    qDebug()<<"Error happens in add map operation!";
                    QMessageBox::critical(NULL,"Error","SQL command execute failed!");
                }
                else
                {
                    QMessageBox::information(NULL,"Info","Operation finish!");
                }
            }
            if(Uni=="ZZU")
            {
                SQLFactory factory;
                auto add=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("insertlecturemap"));
                auto input=shared_ptr<queryexchange>(new queryexchange);
                auto inputlist=new QStringList;
                input->Type="insertlecturemap";
                inputlist->append("ZZU");
                inputlist->append(lectUID);
                inputlist->append(UID);
                input->ExchangeData=inputlist;
                add->inputdata(input);
                add->setdb(db->getdb());
                auto res=add->exec();
                if(!res)
                {
                    std::wcout<<"Error happens in add map operation!"<<endl;
                    qDebug()<<"Error happens in add map operation!";
                    QMessageBox::critical(NULL,"Error","SQL command execute failed!");
                }
                else
                {
                    QMessageBox::information(NULL,"Info","Operation finish!");
                }
            }
        }
        else
        {
            wcout<<"Map list has the item"<<endl;
            QMessageBox::information(NULL,"Info","This lecture is in the list");
        }
    }
    delete dlg;

}

void LectureMapDialog::on_RefreshButton_clicked()
{
    ui->maplist->clear();
    if(Uni=="UDE")
    {
        SQLFactory factory;
        auto listlecturemap=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("listlecturemap"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        input->Type="ListLectureMap";
        inputlist->append("UDE");
        inputlist->append(lectUID);
        input->ExchangeData=inputlist;
        listlecturemap->inputdata(input);
        listlecturemap->setdb(db->getdb());
        auto res=listlecturemap->exec();
        if (res)
        {
            auto output=shared_ptr<queryexchange>(new queryexchange);
            auto outputlist=new QStringList;
            output->ExchangeData=outputlist;
            listlecturemap->outputdata(output);
            int capsize=output->ExchangeData->size();

            for(int i=0;i<capsize;i++)
            {
                ui->maplist->addItem(output->ExchangeData->at(i));
            }
        }
        else
        {
            QMessageBox::critical(NULL,"Error","SQL command execute failed!");
        }
    }
    if(Uni=="ZZU")
    {
        SQLFactory factory;
        auto listlecturemap=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("listlecturemap"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        input->Type="ListLectureMap";
        inputlist->append("ZZU");
        inputlist->append(lectUID);
        input->ExchangeData=inputlist;
        listlecturemap->inputdata(input);
        listlecturemap->setdb(db->getdb());
        auto res=listlecturemap->exec();
        if (res)
        {
            auto output=shared_ptr<queryexchange>(new queryexchange);
            auto outputlist=new QStringList;
            output->ExchangeData=outputlist;
            listlecturemap->outputdata(output);
            int capsize=output->ExchangeData->size();

            for(int i=0;i<capsize;i++)
            {
                ui->maplist->addItem(output->ExchangeData->at(i));
            }
        }
        else
        {
            QMessageBox::critical(NULL,"Error","SQL command execute failed!");
        }
    }
    QString tarUni;
    if(Uni=="UDE")tarUni="ZZU";
    if(Uni=="ZZU")tarUni="UDE";
    lectureMap.clear();
    if(tarUni=="ZZU")
    {
        SQLFactory factory;
        auto listUIDZZU=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("listlectureuid"));
        auto inputZZU=shared_ptr<queryexchange>(new queryexchange);
        auto inputlistZZU=new QStringList;
        inputZZU->Type="listlectureuid";
        inputlistZZU->append("ZZU");
        inputZZU->ExchangeData=inputlistZZU;
        listUIDZZU->inputdata(inputZZU);
        listUIDZZU->setdb(db->getdb());
        auto res=listUIDZZU->exec();
        if (res)
        {
            auto outputZZU=shared_ptr<queryexchange>(new queryexchange);
            auto outputlistZZU=new QStringList;
            outputZZU->ExchangeData=outputlistZZU;
            listUIDZZU->outputdata(outputZZU);
            
            for(int itr=0;itr<outputZZU->ExchangeData->size();++itr)
            {
                QString tmp=outputZZU->ExchangeData->at(itr);
                istringstream sin(tmp.toStdString());
                QStringList attrs;
                QString UID;
                QString LectName;
                string attr;
                while(getline(sin,attr,','))
                {
                    attrs.append(QString::fromStdString(attr));
                }
                UID=attrs.at(0);
                LectName=attrs.at(1);
                lectureMap.insert(pair<string,string>(LectName.toStdString(),UID.toStdString()));
            }
        }
    }
    if(tarUni=="UDE")
    {
        SQLFactory factory;
        auto listUIDUDE=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("listlectureuid"));
        auto inputUDE=shared_ptr<queryexchange>(new queryexchange);
        auto inputlistUDE=new QStringList;
        inputUDE->Type="listlectureuid";
        inputlistUDE->append("UDE");
        inputUDE->ExchangeData=inputlistUDE;
        listUIDUDE->inputdata(inputUDE);
        listUIDUDE->setdb(db->getdb());
        auto res2=listUIDUDE->exec();
        if (res2)
        {
            auto outputUDE=shared_ptr<queryexchange>(new queryexchange);
            auto outputlistUDE=new QStringList;
            outputUDE->ExchangeData=outputlistUDE;
            listUIDUDE->outputdata(outputUDE);
            
            for(int itr=0;itr<outputUDE->ExchangeData->size();++itr)
            {
                QString tmp=outputUDE->ExchangeData->at(itr);
                istringstream sin(tmp.toStdString());
                QStringList attrs;
                QString UID;
                QString LectName;
                string attr;
                while(getline(sin,attr,','))
                {
                    attrs.append(QString::fromStdString(attr));
                }
                if(attrs.size()!=2)
                {
                    wcout<<"updateLectureUIDmap:Not match number of parameters!";
                    qDebug()<<"updateLectureUIDmap:Not match number of parameters!";
                }
                UID=attrs.at(0);
                LectName=attrs.at(1);
                lectureMap.insert(pair<string,string>(LectName.toStdString(),UID.toStdString()));
            }
        }
    }

}

void LectureMapDialog::on_delBut_clicked()
{
    bool focus=ui->maplist->isItemSelected(ui->maplist->currentItem());
    if(focus)
    {
        QString selLect=ui->maplist->currentItem()->text();
        string key=selLect.toStdString();
        QString UID;
        auto itr=lectureMap.find(key);
        if(itr==lectureMap.end())
        {
            wcout<<"Can not find pair in LecturMap!"<<endl;
            qDebug()<<"Can not find pair in LecturMap!";
        }
        else
        {
            UID=QString::fromStdString(itr->second);
        }
        if(!UID.isEmpty())
        {
            if(Uni=="UDE")
            {
                SQLFactory factory;
                auto del=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("deletelecturemap"));
                auto input=shared_ptr<queryexchange>(new queryexchange);
                auto inputlist=new QStringList;
                input->Type="deletelecturemap";
                inputlist->append("UDE");
                inputlist->append(lectUID);
                inputlist->append(UID);
                input->ExchangeData=inputlist;
                del->inputdata(input);
                del->setdb(db->getdb());
                auto res=del->exec();
                if(!res)
                {
                    std::wcout<<"Error happens in delete map operation!"<<endl;
                    qDebug()<<"Error happens in delete map operation!";
                    QMessageBox::critical(NULL,"Error","SQL command execute failed!");
                }
                else
                {
                    QMessageBox::information(NULL,"Info","Operation finish!");
                }
            }
            if(Uni=="ZZU")
            {
                SQLFactory factory;
                auto del=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("deletelecturemap"));
                auto input=shared_ptr<queryexchange>(new queryexchange);
                auto inputlist=new QStringList;
                input->Type="deletelecturemap";
                inputlist->append("ZZU");
                inputlist->append(lectUID);
                inputlist->append(UID);
                input->ExchangeData=inputlist;
                del->inputdata(input);
                del->setdb(db->getdb());
                auto res=del->exec();
                if(!res)
                {
                    std::wcout<<"Error happens in delete map operation!"<<endl;
                    qDebug()<<"Error happens in delete map operation!";
                    QMessageBox::critical(NULL,"Error","SQL command execute failed!");
                }
                else
                {
                    QMessageBox::information(NULL,"Info","Operation finish!");
                }
            }

        }
        else
        {
            std::wcout<<"Get UUID Fail!"<<endl;
            qDebug()<<"Get UUID Fail!";
            QMessageBox::critical(NULL,"Error","Get UUID Fail!");
        }
    }
    else
    {
        QMessageBox::critical(NULL,"Error","No Selection!");
        qDebug()<<"No Selection!";
        wcout<<"No Selection!"<<endl;
    }

}
