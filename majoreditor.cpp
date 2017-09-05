#include "majoreditor.h"
#include "ui_majoreditor.h"

MajorEditor::MajorEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MajorEditor)
{
    TableModel=new QStandardItemModel();
    ui->setupUi(this);
    InitViewModel();
}

MajorEditor::~MajorEditor()
{
    delete ui;
}

void MajorEditor::initDB(shared_ptr<SQLBase> setdb)
{
    db=setdb;
}

void MajorEditor::InitViewModel()
{
    QString Unisel=ui->UniSelect->currentText();
    TableModel->clear();
    if(Unisel=="University ZhengZhou")
    {
        TableModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("LectureUUID")));
        TableModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("LectureName")));
        TableModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("Type")));
        TableModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("Module")));
        TableModel->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("Credit")));
        TableModel->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("Teachinghours")));
    }
    if(Unisel=="University Duisburg-Essen")
    {
        TableModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("LectureUUID")));
        TableModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("LectureName")));
        TableModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("Semester")));
        TableModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("Module")));
        TableModel->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("Credit")));
        TableModel->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("Teachinghours")));
    }
}

void MajorEditor::GetList()
{
    QString Uni=ui->Unibox->currentText();
    if(Uni=="University ZhengZhou")
    {

    }
    if(Uni=="University Duisburg-Essen")
    {

    }
    GetUIDMap();
}

void MajorEditor::GetUIDMap()
{
    UDEMajor.clear();
    ZZUMajor.clear();
    //For ZZU
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
            ui->LecSel->addItem(MajorName);
            ZZUMajor.insert(pair<string,string>(MajorName.toStdString(),UID.toStdString()));
        }
    }

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
            ui->LecSel->addItem(MajorName);
            UDEMajor.insert(pair<string,string>(MajorName.toStdString(),UID.toStdString()));
        }
    }
}

void MajorEditor::on_Unibox_activated(const QString &arg1)
{
    if(arg1=="University ZhengZhou")
    {
        ui->MapEdit->setEnabled(true);
    }
    if(arg1=="University Duisburg-Essen")
    {
        ui->MapEdit->setEnabled(false);
    }
}
