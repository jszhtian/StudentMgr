#include "scoremgr.h"
#include "ui_scoremgr.h"

ScoreMgr::ScoreMgr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreMgr)
{
    TableModel=new QStandardItemModel();
    ui->setupUi(this);

    QString mode=ui->ExamTypeBox->currentText();
    if(mode=="SelectionExam")
    {
        ui->ZZUEdit->setEnabled(false);
        ui->UDEEdit->setEnabled(false);
        ui->NoteEdit->setEnabled(false);
        ui->SemesterEdit->setEnabled(false);
        ui->LectureTypeEdit->setEnabled(true);
        ui->LecSelButton->setEnabled(false);
    }
    if(mode=="UDEExam")
    {
        ui->ZZUEdit->setEnabled(false);
        ui->UDEEdit->setEnabled(true);
        ui->NoteEdit->setEnabled(true);
        ui->SemesterEdit->setEnabled(true);
        ui->LectureTypeEdit->setEnabled(false);
        ui->LecSelButton->setEnabled(true);
    }
    if(mode=="ZZUExam")
    {
        ui->ZZUEdit->setEnabled(true);
        ui->UDEEdit->setEnabled(false);
        ui->NoteEdit->setEnabled(true);
        ui->SemesterEdit->setEnabled(true);
        ui->LectureTypeEdit->setEnabled(false);
        ui->LecSelButton->setEnabled(true);
    }

    ui->tableView->setModel(TableModel);
    InitViewModel();
    qDebug()<<"ScoreMgr create";
    wcout<<"ScoreMgr create"<<endl;
    connect(ui->tableView->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(slot_sortbyColumn(int)));
}

ScoreMgr::~ScoreMgr()
{
    delete TableModel;
    delete ui;
    qDebug()<<"ScoreMgr destory";
    wcout<<"ScoreMgr destory"<<endl;
}

void ScoreMgr::initDB(shared_ptr<SQLBase> setdb)
{
    db=setdb;
}

void ScoreMgr::InitViewModel()
{
    QString mode=ui->ExamTypeBox->currentText();
    TableModel->clear();
    if(mode=="SelectionExam")
    {
        TableModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("ExamUUID")));
        TableModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("StudentName")));
        TableModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("StudentID")));
        TableModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("Examscore")));
        TableModel->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("Type")));
        TableModel->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("Examdatastamp")));
    }
    if(mode=="UDEExam")
    {
        TableModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("ExamUUID")));
        TableModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("StudentName")));
        TableModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("StudentID")));
        TableModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("LectureName")));
        TableModel->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("Examscore")));
        TableModel->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("Examsnote")));
        TableModel->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("Semester")));
        TableModel->setHorizontalHeaderItem(7,new QStandardItem(QObject::tr("Examdatastamp")));
    }
    if(mode=="ZZUExam")
    {
        TableModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("ExamUUID")));
        TableModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("StudentName")));
        TableModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("StudentID")));
        TableModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("LectureName")));
        TableModel->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("LectureinUDE")));
        TableModel->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("LectureType")));
        TableModel->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("Examscore")));
        TableModel->setHorizontalHeaderItem(7,new QStandardItem(QObject::tr("Examsnote")));
        TableModel->setHorizontalHeaderItem(8,new QStandardItem(QObject::tr("Semester")));
        TableModel->setHorizontalHeaderItem(9,new QStandardItem(QObject::tr("Examdatastamp")));
    }
    ui->tableView->setColumnHidden(0,true);
}

void ScoreMgr::getMap()
{
    StudentIDMap.clear();
    SQLFactory factory;
    auto liststudent=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("liststudent"));
    auto input=shared_ptr<queryexchange>(new queryexchange);
    auto inputlist=new QStringList;
    input->Type="liststudent";
    input->ExchangeData=inputlist;
    liststudent->inputdata(input);
    liststudent->setdb(db->getdb());
    auto res=liststudent->exec();
    if (res)
    {
        auto output=shared_ptr<queryexchange>(new queryexchange);
        auto outputlist=new QStringList;
        output->ExchangeData=outputlist;
        liststudent->outputdata(output);

        for(int itr=0;itr<output->ExchangeData->size();++itr)
        {
            QString tmp=output->ExchangeData->at(itr);
            istringstream sin(tmp.toStdString());
            QStringList attrs;
            string attr;
            while(getline(sin,attr,','))
            {
                attrs.append(QString::fromStdString(attr));
            }
            StudentIDMap.insert(pair<string,string>(attrs.at(1).toStdString(),attrs.at(0).toStdString()));
        }
    }
    QString mode=ui->ExamTypeBox->currentText();
    LectureMap.clear();
    if(mode=="UDEExam")
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
                LectureMap.insert(pair<string,string>(LectName.toStdString(),UID.toStdString()));
            }
        }
    }
    if(mode=="ZZUExam")
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
                LectureMap.insert(pair<string,string>(LectName.toStdString(),UID.toStdString()));
            }
        }
    }

}

void ScoreMgr::fillmodel(QStringList *list)
{
    InitViewModel();
    QString mode=ui->ExamTypeBox->currentText();
    if(mode=="SelectionExam")
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
            auto Row3=new QStandardItem(attrs.at(3));
            auto Row4=new QStandardItem(attrs.at(4));
            auto Row5=new QStandardItem(attrs.at(5));
            newRow.append(Row0);
            newRow.append(Row1);
            newRow.append(Row2);
            newRow.append(Row3);
            newRow.append(Row4);
            newRow.append(Row5);
            TableModel->appendRow(newRow);
        }
    }
    if(mode=="UDEExam")
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
            auto Row3=new QStandardItem(attrs.at(3));
            auto Row4=new QStandardItem(attrs.at(4));
            auto Row5=new QStandardItem(attrs.at(5));
            auto Row6=new QStandardItem(attrs.at(6));
            auto Row7=new QStandardItem(attrs.at(7));
            newRow.append(Row0);
            newRow.append(Row1);
            newRow.append(Row2);
            newRow.append(Row3);
            newRow.append(Row4);
            newRow.append(Row5);
            newRow.append(Row6);
            newRow.append(Row7);
            TableModel->appendRow(newRow);
        }
    }
    if(mode=="ZZUExam")
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
            auto Row3=new QStandardItem(attrs.at(3));
            auto Row4=new QStandardItem(attrs.at(4));
            auto Row5=new QStandardItem(attrs.at(5));
            auto Row6=new QStandardItem(attrs.at(6));
            auto Row7=new QStandardItem(attrs.at(7));
            auto Row8=new QStandardItem(attrs.at(8));
            auto Row9=new QStandardItem(attrs.at(9));
            newRow.append(Row0);
            newRow.append(Row1);
            newRow.append(Row2);
            newRow.append(Row3);
            newRow.append(Row4);
            newRow.append(Row5);
            newRow.append(Row6);
            newRow.append(Row7);
            newRow.append(Row8);
            newRow.append(Row9);
            TableModel->appendRow(newRow);
        }
    }
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->resizeColumnsToContents();
}

QString ScoreMgr::GetStudentID(QString UUID)
{
    for(auto itr=StudentIDMap.begin();itr!=StudentIDMap.end();++itr)
    {
        if(itr->second==UUID.toStdString())
        {
            return QString::fromStdString(itr->first);
        }
    }
    return NULL;
}

QString ScoreMgr::GetStudentUUID(QString SID)
{
    auto itr=StudentIDMap.find(SID.toStdString());
    if(itr!=StudentIDMap.end())
    {
        return QString::fromStdString(itr->second);
    }
    else
    {
        return NULL;
    }
}

QString ScoreMgr::GetLectureUUID(QString Name)
{
    auto itr=LectureMap.find(Name.toStdString());
    if(itr!=LectureMap.end())
    {
        return QString::fromStdString(itr->second);
    }
    else
    {
        return NULL;
    }
}

QString ScoreMgr::GettimeStamp()
{
    if(usecurrenttime)
    {
        QDateTime time=QDateTime::currentDateTime();
        return time.toString("yyyy-MM-dd hh:mm:ss");
    }
    else
    {
        QDateTime time=ui->dateTimeEdit->dateTime();
        return time.toString("yyyy-MM-dd hh:mm:ss");
    }
}

void ScoreMgr::on_SelStuButton_clicked()
{
    StudentSelectDialog* dlg=new StudentSelectDialog(this);
    dlg->initDB(db);
    dlg->prepare();
    if(dlg->Rejected==dlg->exec())
    {
        QMessageBox::information(NULL,"Info","No Selection!");
    }
    else
    {
        QString Name=dlg->getSelectName();
        QString STDID=dlg->getSelectStudentID();
        if(!Name.isEmpty())
        {
            ui->NameEdit->setText(dlg->getSelectName());
            ui->IDEdit->setText(dlg->getSelectStudentID());
        }

    }
    delete dlg;
}

void ScoreMgr::on_LecSelButton_clicked()
{
    QString mode=ui->ExamTypeBox->currentText();
    if(mode=="SelectionExam")
    {
        qDebug()<<"Not Support Operation!";
        wcout<<"Not Support Operation!"<<endl;
    }
    if(mode=="UDEExam")
    {
        ui->ZZUEdit->clear();
        lectureselectDialog* dlg=new lectureselectDialog(this);
        dlg->SetUni("UDE");
        dlg->initDB(db);
        dlg->prepare();
        if(dlg->Rejected==dlg->exec())
        {
            QMessageBox::information(NULL,"Info","No Selection!");
        }
        else
        {
            ui->UDEEdit->setText(dlg->getSelectName());
        }
        delete dlg;
    }
    if(mode=="ZZUExam")
    {
        ui->UDEEdit->clear();
        lectureselectDialog* dlg=new lectureselectDialog(this);
        dlg->SetUni("ZZU");
        dlg->initDB(db);
        dlg->prepare();
        if(dlg->Rejected==dlg->exec())
        {
            QMessageBox::information(NULL,"Info","No Selection!");
        }
        else
        {
            ui->ZZUEdit->setText(dlg->getSelectName());
        }
        delete dlg;
    }
}

void ScoreMgr::on_ExamTypeBox_activated(const QString &arg1)
{
    QString mode=arg1;
    if(mode=="SelectionExam")
    {
        ui->ZZUEdit->setEnabled(false);
        ui->UDEEdit->setEnabled(false);
        ui->NoteEdit->setEnabled(false);
        ui->SemesterEdit->setEnabled(false);
        ui->LectureTypeEdit->setEnabled(true);
        ui->LecSelButton->setEnabled(false);
    }
    if(mode=="UDEExam")
    {
        ui->ZZUEdit->setEnabled(false);
        ui->UDEEdit->setEnabled(true);
        ui->NoteEdit->setEnabled(true);
        ui->SemesterEdit->setEnabled(true);
        ui->LectureTypeEdit->setEnabled(false);
        ui->LecSelButton->setEnabled(true);
    }
    if(mode=="ZZUExam")
    {
        ui->ZZUEdit->setEnabled(true);
        ui->SemesterEdit->setEnabled(true);
        ui->UDEEdit->setEnabled(false);
        ui->NoteEdit->setEnabled(true);
        ui->LectureTypeEdit->setEnabled(false);
        ui->LecSelButton->setEnabled(true);
    }
    InitViewModel();
    getlist();
    getMap();
}

void ScoreMgr::on_RefButton_clicked()
{
    getlist();
    getMap();
}

void ScoreMgr::getlist()
{
    QString mode=ui->ExamTypeBox->currentText();
    SQLFactory factory;
    auto list=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("listexam"));
    auto input=shared_ptr<queryexchange>(new queryexchange);
    auto inputlist=new QStringList;
    input->Type="listexam";
    if(mode=="SelectionExam")
    {
        inputlist->append("SelectExam");
    }
    if(mode=="UDEExam")
    {
        inputlist->append("UDE");
    }
    if(mode=="ZZUExam")
    {
        inputlist->append("ZZU");
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
        fillmodel(output->ExchangeData);
    }
}

void ScoreMgr::on_tableView_clicked(const QModelIndex &index)
{
    QString mode=ui->ExamTypeBox->currentText();
    if(mode=="SelectionExam")
    {
        ui->NameEdit->setText(TableModel->item(index.row(),1)->text());
        ui->IDEdit->setText(TableModel->item(index.row(),2)->text());
        ui->ScoreEdit->setText(TableModel->item(index.row(),3)->text());
        ui->LectureTypeEdit->setText(TableModel->item(index.row(),4)->text());
        ui->dateTimeEdit->setDateTime(QDateTime::fromString(TableModel->item(index.row(),5)->text(),"yyyy-MM-dd hh:mm:ss"));

    }
    if(mode=="UDEExam")
    {
        ui->NameEdit->setText(TableModel->item(index.row(),1)->text());
        ui->IDEdit->setText(TableModel->item(index.row(),2)->text());
        ui->UDEEdit->setText(TableModel->item(index.row(),3)->text());
        ui->ScoreEdit->setText(TableModel->item(index.row(),4)->text());
        ui->NoteEdit->setText(TableModel->item(index.row(),5)->text());
        ui->SemesterEdit->setText(TableModel->item(index.row(),6)->text());
        ui->dateTimeEdit->setDateTime(QDateTime::fromString(TableModel->item(index.row(),7)->text(),"yyyy-MM-dd hh:mm:ss"));

    }
    if(mode=="ZZUExam")
    {
        ui->NameEdit->setText(TableModel->item(index.row(),1)->text());
        ui->IDEdit->setText(TableModel->item(index.row(),2)->text());
        ui->ZZUEdit->setText(TableModel->item(index.row(),3)->text());
        ui->UDEEdit->setText(TableModel->item(index.row(),4)->text());
        ui->LectureTypeEdit->setText(TableModel->item(index.row(),5)->text());
        ui->ScoreEdit->setText(TableModel->item(index.row(),6)->text());
        ui->NoteEdit->setText(TableModel->item(index.row(),7)->text());
        ui->SemesterEdit->setText(TableModel->item(index.row(),8)->text());
        ui->dateTimeEdit->setDateTime(QDateTime::fromString(TableModel->item(index.row(),9)->text(),"yyyy-MM-dd hh:mm:ss"));

    }
}

void ScoreMgr::on_InsertButton_clicked()
{
    QString StudentUUID=GetStudentUUID(ui->IDEdit->text());
    QString mode=ui->ExamTypeBox->currentText();
    SQLFactory factory;
    auto insert=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("insertexam"));
    auto input=shared_ptr<queryexchange>(new queryexchange);
    auto inputlist=new QStringList;
    input->Type="insertexam";
    if(mode=="SelectionExam")
    {
        inputlist->append("SelectExam");
        inputlist->append(StudentUUID);
        inputlist->append(ui->ScoreEdit->text());
        inputlist->append(ui->LectureTypeEdit->text());
        inputlist->append(GettimeStamp());
    }
    if(mode=="UDEExam")
    {
        inputlist->append("UDE");
        inputlist->append(StudentUUID);
        inputlist->append(GetLectureUUID(ui->UDEEdit->text()));
        inputlist->append(ui->ScoreEdit->text());
        inputlist->append(ui->NoteEdit->text());
        inputlist->append(ui->SemesterEdit->text());
        inputlist->append(GettimeStamp());
    }
    if(mode=="ZZUExam")
    {
        inputlist->append("ZZU");
        inputlist->append(StudentUUID);
        inputlist->append(GetLectureUUID(ui->ZZUEdit->text()));
        inputlist->append(ui->ScoreEdit->text());
        inputlist->append(ui->NoteEdit->text());
        inputlist->append(ui->SemesterEdit->text());
        inputlist->append(GettimeStamp());
    }
    input->ExchangeData=inputlist;
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

void ScoreMgr::on_timeoptionBox_toggled(bool checked)
{
    if(checked)
    {
        ui->dateTimeEdit->setEnabled(false);
        usecurrenttime=true;
    }
    else
    {
        ui->dateTimeEdit->setEnabled(true);
        usecurrenttime=false;
    }
}

void ScoreMgr::on_UpdateButton_clicked()
{
    int currow=-1;
    currow=ui->tableView->currentIndex().row();
    if(currow==-1)
    {
        QMessageBox::critical(NULL,"Error","No data in tableview!");
        wcout<<"No data in tableview!"<<endl;
        qDebug()<<"No data in tableview!";
    }
    else
    {
        QString examUUID=TableModel->item(currow,0)->text();
        QString StudentUUID=GetStudentUUID(ui->IDEdit->text());
        QString mode=ui->ExamTypeBox->currentText();
        SQLFactory factory;
        auto udp=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("updateexam"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        input->Type="updateexam";
        if(mode=="SelectionExam")
        {
            inputlist->append("SelectExam");
            inputlist->append(examUUID);
            inputlist->append(StudentUUID);
            inputlist->append(ui->ScoreEdit->text());
            inputlist->append(ui->LectureTypeEdit->text());
            inputlist->append(GettimeStamp());

        }
        if(mode=="UDEExam")
        {
            inputlist->append("UDE");
            inputlist->append(examUUID);
            inputlist->append(StudentUUID);
            inputlist->append(GetLectureUUID(ui->UDEEdit->text()));
            inputlist->append(ui->ScoreEdit->text());
            inputlist->append(ui->NoteEdit->text());
            inputlist->append(ui->SemesterEdit->text());
            inputlist->append(GettimeStamp());
        }
        if(mode=="ZZUExam")
        {
            inputlist->append("ZZU");
            inputlist->append(examUUID);
            inputlist->append(StudentUUID);
            inputlist->append(GetLectureUUID(ui->ZZUEdit->text()));
            inputlist->append(ui->ScoreEdit->text());
            inputlist->append(ui->NoteEdit->text());
            inputlist->append(ui->SemesterEdit->text());
            inputlist->append(GettimeStamp());
        }
        input->ExchangeData=inputlist;
        udp->inputdata(input);
        udp->setdb(db->getdb());
        auto res=udp->exec();
        if(res)
        {
            QMessageBox::information(NULL,"Info","Update finished.");
        }
        else
        {
            QMessageBox::critical(NULL,"Error","Error happens during update operation!");
        }
    }

}

void ScoreMgr::on_DeleteButton_clicked()
{
    int currow=-1;
    currow=ui->tableView->currentIndex().row();
    if(currow==-1)
    {
        QMessageBox::critical(NULL,"Error","No data in tableview!");
        wcout<<"No data in tableview!"<<endl;
        qDebug()<<"No data in tableview!";
    }
    else
    {
        QString examUUID=TableModel->item(currow,0)->text();
        QString mode=ui->ExamTypeBox->currentText();
        SQLFactory factory;
        auto del=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("deleteexam"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        input->Type="deleteexam";
        if(mode=="SelectionExam")
        {
            inputlist->append("SelectExam");
            inputlist->append(examUUID);
        }
        if(mode=="UDEExam")
        {
            inputlist->append("UDE");
            inputlist->append(examUUID);
        }
        if(mode=="ZZUExam")
        {
            inputlist->append("ZZU");
            inputlist->append(examUUID);
        }
        input->ExchangeData=inputlist;
        del->inputdata(input);
        del->setdb(db->getdb());
        auto res=del->exec();
        if(res)
        {
            QMessageBox::information(NULL,"Info","Update finished.");
        }
        else
        {
            QMessageBox::critical(NULL,"Error","Error happens during update operation!");
        }
    }
}

void ScoreMgr::on_ExportButton_clicked()
{
    QFileDialog* fileDialog=new QFileDialog(this);
    fileDialog->setWindowTitle("Export CSV File");
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setNameFilter("CSV File(*.csv)");
    fileDialog->setDirectory(".");
    if(fileDialog->exec() == QDialog::Accepted)
    {
        QString path=fileDialog->selectedFiles()[0];
        QFile csvfile(path);
        if(!csvfile.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::information(NULL, "IO Error", "Access denied!");
        }
        QTextStream out(&csvfile);
        out.setCodec("UTF-8");
        auto mode=ui->ExamTypeBox->currentText();
        if(mode=="SelectionExam")
        {
            out<<"StudentName,StudentID,Examscore,Type,Examdatastamp\n";
        }
        if(mode=="UDEExam")
        {
            out<<"StudentName,StudentID,LectureName,Examscore,Examsnote,Semester,Examdatastamp\n";
        }
        if(mode=="ZZUExam")
        {
            out<<"StudentName,StudentID,LectureName,LectureinUDE,LectureType,Examscore,Examsnote,Semester,Examdatastamp\n";
        }
        
        for(int i=0;i<TableModel->rowCount();++i)
        {
            for(int j=1;j<TableModel->columnCount();j++)
            {
                out<<TableModel->item(i,j)->text()<<",";
            }
            out<<"\n";
        }
        csvfile.close();
        QMessageBox::information(NULL, "Export", "Export finish!");
    }
    else
    {
        QMessageBox::information(NULL, "Export", "Nothing Exported!");
    }
    delete fileDialog;
}

void ScoreMgr::slot_sortbyColumn(int column)
{
    ui->tableView->sortByColumn(column);
}
