#include "majorselectdialog.h"
#include "ui_majorselectdialog.h"

MajorSelectDialog::MajorSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MajorSelectDialog)
{
    ui->setupUi(this);
}

MajorSelectDialog::~MajorSelectDialog()
{
    delete ui;
}

QString MajorSelectDialog::getSelectName()
{
    return ui->MajorcomboBox->currentText();
}

QString MajorSelectDialog::getSelectUID()
{
    string key=ui->MajorcomboBox->currentText().toStdString();
    auto itr=MajorMap.find(key);
    if(itr==MajorMap.end())
    {
        wcout<<"Can not find pair in LecturMap!"<<endl;
        qDebug()<<"Can not find pair in LecturMap!";
        return NULL;
    }
    else
    {
        return QString::fromStdString(itr->second);
    }
}

void MajorSelectDialog::prepare()
{
    if(!Uni.isEmpty()&&db.get()!=NULL)
    {
        on_REFButton_clicked();
    }
}

void MajorSelectDialog::SetUni(QString setuni)
{
    Uni=setuni;
}

void MajorSelectDialog::initDB(shared_ptr<SQLBase> setdb)
{
    db=setdb;
}

void MajorSelectDialog::on_REFButton_clicked()
{
    MajorMap.clear();
    if(Uni=="ZZU")
    {
        SQLFactory factory;
        auto listUIDZZU=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("listmajoruid"));
        auto inputZZU=shared_ptr<queryexchange>(new queryexchange);
        auto inputlistZZU=new QStringList;
        inputZZU->Type="listmajoruid";
        inputlistZZU->append("ZZU");
        inputZZU->ExchangeData=inputlistZZU;
        listUIDZZU->inputdata(inputZZU);
        listUIDZZU->setdb(db->getdb());
        auto res1=listUIDZZU->exec();
        if (res1)
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
                QString MajorName;
                string attr;
                while(getline(sin,attr,','))
                {
                    attrs.append(QString::fromStdString(attr));
                }
                UID=attrs.at(0);
                MajorName=attrs.at(1);
                ui->MajorcomboBox->addItem(MajorName);
                MajorMap.insert(pair<string,string>(MajorName.toStdString(),UID.toStdString()));
            }
        }

    }
    if(Uni=="UDE")
    {
        SQLFactory factory;
        auto listUIDUDE=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("listmajoruid"));
        auto inputUDE=shared_ptr<queryexchange>(new queryexchange);
        auto inputlistUDE=new QStringList;
        inputUDE->Type="listmajoruid";
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
                QString MajorName;
                string attr;
                while(getline(sin,attr,','))
                {
                    attrs.append(QString::fromStdString(attr));
                }
                UID=attrs.at(0);
                MajorName=attrs.at(1);
                ui->MajorcomboBox->addItem(MajorName);
                MajorMap.insert(pair<string,string>(MajorName.toStdString(),UID.toStdString()));
            }
        }
    }
}
