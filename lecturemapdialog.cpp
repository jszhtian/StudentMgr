#include "lecturemapdialog.h"
#include "ui_lecturemapdialog.h"

LectureMapDialog::LectureMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LectureMapDialog)
{
    ui->setupUi(this);
}

LectureMapDialog::~LectureMapDialog()
{
    delete ui;
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

void LectureMapDialog::on_AddBut_clicked()
{
    lectureselectDialog* dlg=new lectureselectDialog(this);
    dlg->SetUni(Uni);
    dlg->initDB(db);
    if(dlg->Rejected==dlg->exec())
    {
        QMessageBox::information(NULL,"Info","No Selection!");
    }
    else
    {
        QString name=dlg->getSelectName();
    }
    delete dlg;
    QList it=ui->maplist->findItems(name,Qt::MatchExactly);
    if(it.size()==0)
    {

    }
    else
    {
        wcout<<"Map list has the item"<<endl;
        QMessageBox::information(null,"Info","This lecture is in the list");
    }
}

void LectureMapDialog::on_RefreshButton_clicked()
{
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
}
