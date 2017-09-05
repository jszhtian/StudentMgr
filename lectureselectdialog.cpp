#include "lectureselectdialog.h"
#include "ui_lectureselectdialog.h"

lectureselectDialog::lectureselectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lectureselectDialog)
{
    ui->setupUi(this);
}

lectureselectDialog::~lectureselectDialog()
{
    delete ui;
}

void lectureselectDialog::SetUni(QString SetName)
{
    Uni=SetName;
}

QString lectureselectDialog::getSelectName()
{
    return ui->LecSel->currentText();
}

void lectureselectDialog::initDB(shared_ptr<SQLBase> setdb)
{
    db=setdb;
}

void lectureselectDialog::on_pushButton_clicked()
{
    if(Uni=="ZZU")
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
                    ui->LecSel->addItem(LectName);
                }
            }
    }
    if(Uni=="UDE")
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
                    ui->LecSel->addItem(LectName);
                }
            }
    }
}
