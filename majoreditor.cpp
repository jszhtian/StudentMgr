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
        ui->pushButton_2->setEnabled(true);
    }
    if(Unisel=="University Duisburg-Essen")
    {
        ui->MapEdit->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
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

    //GetLectureUIDMap();
}

void MajorEditor::GetLectureUIDMap()
{
    UDELecture.clear();
    ZZULecture.clear();
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
            ZZULecture.insert(pair<string,string>(LectName.toStdString(),UID.toStdString()));
        }
    }

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
            UDELecture.insert(pair<string,string>(LectName.toStdString(),UID.toStdString()));
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
        ui->LectureList->clear();
        ui->pushButton_2->setEnabled(true);
    }
    if(arg1=="University Duisburg-Essen")
    {
        ui->MapEdit->setEnabled(false);
        GetList();
        ui->LectureList->clear();
        ui->pushButton_2->setEnabled(false);
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
    ui->LectureList->clear();
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
    on_loadLectureButton_clicked();
}

void MajorEditor::on_InsertButton_clicked()
{
    QString Name=ui->NameEditor->text();
    QString supervisor=ui->SupervisorEdit->text();
    QString Unisel=ui->Unibox->currentText();
    bool isOk=false;
    if(Name.isEmpty())
    {
        QMessageBox::critical(NULL,"Error","No Major Name input!");
        qDebug()<<"No Major Name input!";
        wcout<<"No Major Name input!"<<endl;
        isOk=false;
    }
    else
    {
        SQLFactory factory;
        auto insert=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("insertmajor"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        if(Unisel=="University Duisburg-Essen")
        {
            input->Type="insertmajor";
            inputlist->append("UDE");
            inputlist->append(Name);
            inputlist->append(supervisor);
            input->ExchangeData=inputlist;
            isOk=true;
        }
        if(Unisel=="University ZhengZhou")
        {
            input->Type="insertmajor";
            inputlist->append("ZZU");
            inputlist->append(Name);
            inputlist->append(supervisor);
            QString UDEName=ui->MapEdit->text();
            auto it=UDEMajor.find(UDEName.toStdString());
            if(it==UDEMajor.end())
            {
                wcout<<"Can not find pair in MajorMap!"<<endl;
                qDebug()<<"Can not find pair in MajorMap!";
                QMessageBox::critical(NULL,"Error","Can not find pair in MajorMap! Please refresh the window.");
                isOk=false;
            }
            else
            {
                QString UDEUID=QString::fromStdString(it->second);
                inputlist->append(UDEUID);
                input->ExchangeData=inputlist;
                isOk=true;
            }
        }
        if(isOk)
        {
            insert->inputdata(input);
            insert->setdb(db->getdb());
            auto res=insert->exec();
            if(res)
            {
                QMessageBox::information(NULL,"Info","Insert finished.");
            }
            else
            {
                QMessageBox::critical(NULL,"Error","Error happens during insert operation!");
            }
        }

    }

}

void MajorEditor::on_DeleteButton_clicked()
{
    int currrow=-1;
    currrow=ui->MajorView->currentIndex().row();
    if(currrow==-1)
    {
        QMessageBox::critical(NULL,"Error","No row selected!");
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
    }
    else
    {
        QString UID=TableModel->item(currrow,0)->text();
        QString Unisel=ui->Unibox->currentText();
        SQLFactory factory;
        auto del=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("deletemajor"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        if(Unisel=="University Duisburg-Essen")
        {
            input->Type="deletemajor";
            inputlist->append("UDE");
            inputlist->append(UID);
            input->ExchangeData=inputlist;
        }
        if(Unisel=="University ZhengZhou")
        {
            input->Type="deletemajor";
            inputlist->append("ZZU");
            inputlist->append(UID);
            input->ExchangeData=inputlist;
        }
        del->inputdata(input);
        del->setdb(db->getdb());
        auto res=del->exec();
        if(res)
        {
            QMessageBox::information(NULL,"Info","Delete finished.");
        }
        else
        {
            QMessageBox::critical(NULL,"Error","Error happens during delete operation!");
        }
    }
}

void MajorEditor::on_Updatebutton_clicked()
{
    QString Name=ui->NameEditor->text();
    QString supervisor=ui->SupervisorEdit->text();
    QString Unisel=ui->Unibox->currentText();
    bool isOk=false;
    int currrow=-1;
    currrow=ui->MajorView->currentIndex().row();
    if(currrow==-1)
    {
        QMessageBox::critical(NULL,"Error","No row selected!");
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
        isOk=false;
    }
    else
    {
        QString UID=TableModel->item(currrow,0)->text();
        SQLFactory factory;
        auto upd=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("updatemajor"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        if(Unisel=="University Duisburg-Essen")
        {
            input->Type="updatemajor";
            inputlist->append("UDE");
            inputlist->append(UID);
            inputlist->append(Name);
            inputlist->append(supervisor);
            input->ExchangeData=inputlist;
            isOk=true;
        }
        if(Unisel=="University ZhengZhou")
        {
            input->Type="updatemajor";
            inputlist->append("ZZU");
            inputlist->append(UID);
            inputlist->append(Name);
            inputlist->append(supervisor);
            QString UDEName=ui->MapEdit->text();
            auto it=UDEMajor.find(UDEName.toStdString());
            if(it==UDEMajor.end())
            {
                wcout<<"Can not find pair in MajorMap!"<<endl;
                qDebug()<<"Can not find pair in MajorMap!";
                QMessageBox::critical(NULL,"Error","Can not find pair in MajorMap! Please refresh the window.");
                isOk=false;
            }
            else
            {
                QString UDEUID=QString::fromStdString(it->second);
                inputlist->append(UDEUID);
                input->ExchangeData=inputlist;
                isOk=true;
            }
        }
        if(isOk)
        {
            upd->inputdata(input);
            upd->setdb(db->getdb());
            auto res=upd->exec();
            if(res)
            {
                QMessageBox::information(NULL,"Info","update finished.");
            }
            else
            {
                QMessageBox::critical(NULL,"Error","Error happens during update operation!");
            }
        }

    }
}

void MajorEditor::on_loadLectureButton_clicked()
{
    ui->LectureList->clear();
    GetLectureUIDMap();
    int currrow=-1;
    currrow=ui->MajorView->currentIndex().row();
    if(currrow==-1)
    {
        QMessageBox::critical(NULL,"Error","No row selected!");
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
    }
    else
    {
        QString UID=TableModel->item(currrow,0)->text();
        QString Unisel=ui->Unibox->currentText();
        SQLFactory factory;
        auto list=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("listlectureselect"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        input->Type="listlectureselect";
        if(Unisel=="University Duisburg-Essen")
        {
            inputlist->append("UDE");
            inputlist->append(UID);
        }
        if(Unisel=="University ZhengZhou")
        {
            inputlist->append("ZZU");
            inputlist->append(UID);
        }
        input->ExchangeData=inputlist;
        list->inputdata(input);
        list->setdb(db->getdb());
        auto res=list->exec();
        if(res)
        {
            auto output=shared_ptr<queryexchange>(new queryexchange);
            auto outputlist=new QStringList;
            output->ExchangeData=outputlist;
            list->outputdata(output);
            
            for(int i=0;i<output->ExchangeData->size();++i)
            {
                ui->LectureList->addItem(output->ExchangeData->at(i));
            }
        }
        else
        {
            QMessageBox::critical(NULL,"Error","Error happens during list operation!");
        }
    }

}

void MajorEditor::on_AddLectureButton_clicked()
{
    int currrow=-1;
    currrow=ui->MajorView->currentIndex().row();
    if(currrow==-1)
    {
        QMessageBox::critical(NULL,"Error","No row selected!");
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
    }
    else
    {
        QString MajorUID=TableModel->item(currrow,0)->text();
        lectureselectDialog* dlg=new lectureselectDialog(this);
        QString Unisel=ui->Unibox->currentText();
        QString Uni;
        QString UID;
        QString name;
        if(Unisel=="University Duisburg-Essen")
        {
            Uni="UDE";
        }
        if(Unisel=="University ZhengZhou")
        {
            Uni="ZZU";
        }
        dlg->SetUni(Uni);
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
            auto it=ui->LectureList->findItems(name,Qt::MatchExactly);
            if(it.size()==0)
            {
                if(Uni=="UDE")
                {
                    SQLFactory factory;
                    auto add=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("insertlectureselect"));
                    auto input=shared_ptr<queryexchange>(new queryexchange);
                    auto inputlist=new QStringList;
                    input->Type="insertlectureselect";
                    inputlist->append("UDE");
                    inputlist->append(MajorUID);
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
                    auto add=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("insertlectureselect"));
                    auto input=shared_ptr<queryexchange>(new queryexchange);
                    auto inputlist=new QStringList;
                    input->Type="insertlectureselect";
                    inputlist->append("ZZU");
                    inputlist->append(MajorUID);
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

        }
    }

}

void MajorEditor::on_DeleteLecture_clicked()
{
    QString Unisel=ui->Unibox->currentText();
    QString Uni;
    if(Unisel=="University Duisburg-Essen")
    {
        Uni="UDE";
    }
    if(Unisel=="University ZhengZhou")
    {
        Uni="ZZU";
    }
    int currrow=-1;
    QString LectureUID;
    QString MajorUID;
    currrow=ui->LectureList->currentIndex().row();
    if(currrow==-1)
    {
        QMessageBox::critical(NULL,"Error","No row selected!");
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
    }
    else
    {
        QString LectName=ui->LectureList->currentItem()->text();
        if(Uni=="UDE")
        {
            auto itr=UDELecture.find(LectName.toStdString());
            if(itr==UDELecture.end())
            {
                wcout<<"Can not find pair in LecturMap!"<<endl;
                qDebug()<<"Can not find pair in LecturMap!";
            }
            else
            {
                LectureUID=QString::fromStdString(itr->second);
            }
        }
        if(Uni=="ZZU")
        {
            auto itr=ZZULecture.find(LectName.toStdString());
            if(itr==ZZULecture.end())
            {
                wcout<<"Can not find pair in LecturMap!"<<endl;
                qDebug()<<"Can not find pair in LecturMap!";
            }
            else
            {
                LectureUID=QString::fromStdString(itr->second);
            }
        }

    }
    int row2=-1;
    row2=ui->MajorView->currentIndex().row();
    if(row2!=-1)
    {
        MajorUID=TableModel->item(row2,0)->text();
    }
    else
    {
        QMessageBox::critical(NULL,"Error","No row selected!");
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
    }
    if(!MajorUID.isEmpty()&&!LectureUID.isEmpty())
    {
        SQLFactory factory;
        auto del=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("deletelectureselect"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        input->Type="deletelectureselect";
        if(Uni=="ZZU")
        {
            inputlist->append("ZZU");
            inputlist->append(MajorUID);
            inputlist->append(LectureUID);
        }
        if(Uni=="UDE")
        {
            inputlist->append("UDE");
            inputlist->append(MajorUID);
            inputlist->append(LectureUID);
        }
        input->ExchangeData=inputlist;
        del->inputdata(input);
        del->setdb(db->getdb());
        auto res=del->exec();
        if(!res)
        {
            std::wcout<<"Error happens in delete select operation!"<<endl;
            qDebug()<<"Error happens in delete select operation!";
            QMessageBox::critical(NULL,"Error","SQL command execute failed!");
        }
        else
        {
            QMessageBox::information(NULL,"Info","Operation finish!");
        }
    }
    else
    {
        QMessageBox::critical(NULL,"Error","Cannot get UID information!");
    }
}

void MajorEditor::on_pushButton_2_clicked()
{
    MajorSelectDialog* dlg=new MajorSelectDialog(this);
    QString Unisel=ui->Unibox->currentText();
    QString Uni;
    if(Unisel=="University Duisburg-Essen")
    {
        Uni="ZZU";
    }
    if(Unisel=="University ZhengZhou")
    {
        Uni="UDE";
    }
    if(Uni.isEmpty())
    {
        wcout<<"Unexpected error, at on_pushButton_2_clicked"<<endl;
        qDebug()<<"Unexpected error, at on_pushButton_2_clicked";
    }
    else
    {
        dlg->SetUni(Uni);
        dlg->initDB(db);
        dlg->prepare();
        if(dlg->Rejected==dlg->exec())
        {
            QMessageBox::information(NULL,"Info","No Selection!");
        }
        else
        {
            ui->MapEdit->setText(dlg->getSelectName());
        }
    }
    delete dlg;
}
