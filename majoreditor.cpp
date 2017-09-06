#include "majoreditor.h"
#include "ui_majoreditor.h"

MajorEditor::MajorEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MajorEditor)
{
    TableModel=new QStandardItemModel();
    ui->setupUi(this);
    InitViewModel();
    ui->MajorView->setModel(TableModel);
    ui->MajorView->setColumnHidden(0,true);
    QString Unisel=ui->Unibox->currentText();
    if(Unisel=="University ZhengZhou")
    {
        ui->MapEdit->setEnabled(true);
    }
    if(Unisel=="University Duisburg-Essen")
    {
        ui->MapEdit->setEnabled(false);
    }
    connect(ui->MajorView->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(slot_sortbyColumn(int)));
    qDebug()<<"MajorEditor create";
    wcout<<"MajorEditor create"<<endl;
}

MajorEditor::~MajorEditor()
{
    delete ui;
    delete TableModel;
    qDebug()<<"MajorEditor destory";
    wcout<<"MajorEditor destory"<<endl;
}

void MajorEditor::initDB(shared_ptr<SQLBase> setdb)
{
    db=setdb;
}

void MajorEditor::InitViewModel()
{
    QString Unisel=ui->Unibox->currentText();
    TableModel->clear();
    if(Unisel=="University ZhengZhou")
    {
        TableModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("MajorUUID")));
        TableModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("MajorName")));
        TableModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("Supervisor")));
        TableModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("MajorinUDE")));
    }
    if(Unisel=="University Duisburg-Essen")
    {
        TableModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("MajorUUID")));
        TableModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("MajorName")));
        TableModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("Supervisor")));
    }
}

void MajorEditor::GetList()
{
    GetUIDMap();
    QString Uni=ui->Unibox->currentText();
    SQLFactory factory;
    auto listmajor=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("listmajor"));
    auto input=shared_ptr<queryexchange>(new queryexchange);
    auto inputlist=new QStringList;
    if(Uni=="University ZhengZhou")
    {
        input->Type="listmajor";
        inputlist->append("ZZU");
        input->ExchangeData=inputlist;
    }
    if(Uni=="University Duisburg-Essen")
    {
        input->Type="listmajor";
        inputlist->append("UDE");
        input->ExchangeData=inputlist;
    }
    listmajor->inputdata(input);
    listmajor->setdb(db->getdb());
    auto res=listmajor->exec();
    if(res)
    {
        auto output=shared_ptr<queryexchange>(new queryexchange);
        auto outputlist=new QStringList;
        output->ExchangeData=outputlist;
        listmajor->outputdata(output);
        fillthemodel(output->ExchangeData);
    }

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
            UDEMajor.insert(pair<string,string>(MajorName.toStdString(),UID.toStdString()));
        }
    }
}

void MajorEditor::fillthemodel(QStringList *list)
{
    QString Unisel=ui->Unibox->currentText();
    InitViewModel();
    if(Unisel=="University ZhengZhou")
    {
        for(int itr=0;itr<list->size();++itr)
            {
                QString tmp=list->at(itr);
                istringstream sin(tmp.toStdString());
                QStringList attrs;
                string attr;
                while(getline(sin,attr,','))
                {
                    attrs.append(QString::fromStdString(attr));
                }
                QString UID=attrs.at(3);
                QString UDEName;
                for(auto it=UDEMajor.begin();it!=UDEMajor.end();++it)
                {
                    if(it->second==UID.toStdString())
                    {
                        UDEName=QString::fromStdString(it->first);
                        break;
                    }
                }
                QList<QStandardItem*> newRow;
                auto Row0=new QStandardItem(attrs.at(0));
                auto Row1=new QStandardItem(attrs.at(1));
                auto Row2=new QStandardItem(attrs.at(2));
                auto Row3=new QStandardItem(UDEName);
                newRow.append(Row0);
                newRow.append(Row1);
                newRow.append(Row2);
                newRow.append(Row3);
                TableModel->appendRow(newRow);
            }
            ui->MajorView->setColumnHidden(0,true);
            ui->MajorView->resizeColumnsToContents();
    }
    if(Unisel=="University Duisburg-Essen")
    {
        for(int itr=0;itr<list->size();++itr)
            {
                QString tmp=list->at(itr);
                istringstream sin(tmp.toStdString());
                QStringList attrs;
                string attr;
                while(getline(sin,attr,','))
                {
                    attrs.append(QString::fromStdString(attr));
                }
                QList<QStandardItem*> newRow;
                auto Row0=new QStandardItem(attrs.at(0));
                auto Row1=new QStandardItem(attrs.at(1));
                auto Row2=new QStandardItem(attrs.at(2));
                newRow.append(Row0);
                newRow.append(Row1);
                newRow.append(Row2);
                TableModel->appendRow(newRow);
            }
            ui->MajorView->setColumnHidden(0,true);
            ui->MajorView->resizeColumnsToContents();
    }
}

void MajorEditor::on_Unibox_activated(const QString &arg1)
{
    if(arg1=="University ZhengZhou")
    {
        ui->MapEdit->setEnabled(true);
        GetList();
    }
    if(arg1=="University Duisburg-Essen")
    {
        ui->MapEdit->setEnabled(false);
        GetList();
    }
}

void MajorEditor::on_pushButton_clicked()
{
    GetList();
}

void MajorEditor::slot_sortbyColumn(int column)
{
     ui->MajorView->sortByColumn(column);
}

void MajorEditor::on_MajorView_clicked(const QModelIndex &index)
{
    auto UniSel=ui->Unibox->currentText();
    if(UniSel=="University Duisburg-Essen")
    {
        ui->NameEditor->setText(TableModel->item(index.row(),1)->text());
        ui->SupervisorEdit->setText(TableModel->item(index.row(),2)->text());
    }
    if(UniSel=="University ZhengZhou")
    {
        ui->NameEditor->setText(TableModel->item(index.row(),1)->text());
        ui->SupervisorEdit->setText(TableModel->item(index.row(),2)->text());
        ui->MapEdit->setText(TableModel->item(index.row(),3)->text());
    }
}
