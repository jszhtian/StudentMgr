#include "lectureeditor.h"
#include "ui_lectureeditor.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
LectureEditor::LectureEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LectureEditor)
{
    TableModel=new QStandardItemModel();
    ui->setupUi(this);
    InitViewModel();
    ui->LectureView->setModel(TableModel);
    ui->LectureView->setColumnHidden(0,true);
    QString Unisel=ui->UniSelect->currentText();
    if(Unisel=="University ZhengZhou")
    {
        ui->Typebox->setEnabled(true);
        ui->SemesterEditor->setEnabled(false);
    }
    if(Unisel=="University Duisburg-Essen")
    {
        ui->Typebox->setEnabled(false);
        ui->SemesterEditor->setEnabled(true);
    }
    connect(ui->LectureView->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(slot_sortbyColumn(int)));
    qDebug()<<"LectureEditor create";
    wcout<<"LectureEditor create"<<endl;
}

LectureEditor::~LectureEditor()
{
    delete ui;
    delete TableModel;
    qDebug()<<"LectureEditor destory";
    wcout<<"LectureEditor destory"<<endl;
}

void LectureEditor::initDB(shared_ptr<SQLBase> setdb)
{
    db=setdb;
}

void LectureEditor::InitViewModel()
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

void LectureEditor::fillthemodel(QStringList *list)
{
    InitViewModel();
    #pragma omp parallel for
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
        for(int i=0;i<attrs.size();++i)
        {
            newRow.append(new QStandardItem(attrs.at(i)));
        }

        TableModel->appendRow(newRow);
    }
    ui->LectureView->setColumnHidden(0,true);
    ui->LectureView->resizeColumnsToContents();
}



void LectureEditor::GetList()
{
    //updateLectureUIDmap();
    //Not support lecture map editor now
    auto UniSel=ui->UniSelect->currentText();
    SQLFactory factory;
    auto listlecture=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("listlecture"));
    auto input=shared_ptr<queryexchange>(new queryexchange);
    auto inputlist=new QStringList;
    input->Type="ListLecture";
    if(UniSel=="University Duisburg-Essen")
    {
        inputlist->append("UDE");
    }
    if(UniSel=="University ZhengZhou")
    {
        inputlist->append("ZZU");
    }
    input->ExchangeData=inputlist;
    listlecture->inputdata(input);
    listlecture->setdb(db->getdb());
    auto res=listlecture->exec();
    if (res)
    {
        auto output=shared_ptr<queryexchange>(new queryexchange);
        auto outputlist=new QStringList;
        output->ExchangeData=outputlist;
        listlecture->outputdata(output);
        fillthemodel(output->ExchangeData);
    }
    else
    {
        QMessageBox::critical(NULL,"Error","SQL command execute failed!");
    }
}

void LectureEditor::on_UniSelect_activated(const QString &arg1)
{
    if(arg1=="University ZhengZhou")
    {
        ui->Typebox->setEnabled(true);
        ui->SemesterEditor->setEnabled(false);
    }
    if(arg1=="University Duisburg-Essen")
    {
        ui->Typebox->setEnabled(false);
        ui->SemesterEditor->setEnabled(true);
    }
    GetList();
}



void LectureEditor::on_ReFButton_clicked()
{
    GetList();
    auto type=ui->FilterTypeSelect->currentText();
    auto opera=ui->OperationBox->currentText();
    auto condit=ui->conditionEditor->text();
    auto UniSel=ui->UniSelect->currentText();
    if(type=="Name")
    {
        if(opera=="==")
        {
            int rows=TableModel->rowCount();
            #pragma omp parallel for
            for(int i=0;i<rows;i++)
            {
                QString name=TableModel->item(i,1)->text();
                if(name!=condit)
                {
                    ui->LectureView->hideRow(i);
                }
            }
        }
        if(opera=="LIKE")
        {
            int rows=TableModel->rowCount();
            #pragma omp parallel for
            for(int i=0;i<rows;i++)
            {
                QString name=TableModel->item(i,1)->text();
                if(!name.contains(condit))
                {
                    ui->LectureView->hideRow(i);
                }
            }
        }
    }
}

void LectureEditor::on_LectureView_clicked(const QModelIndex &index)
{
    auto UniSel=ui->UniSelect->currentText();
    if(UniSel=="University Duisburg-Essen")
    {

       ui->NameEditor->setText(TableModel->item(index.row(),1)->text());
       ui->Teachinghours->setText(TableModel->item(index.row(),5)->text());
       ui->ModuleEditor->setText(TableModel->item(index.row(),3)->text());
       ui->Credit->setText(TableModel->item(index.row(),4)->text());
       ui->SemesterEditor->setText(TableModel->item(index.row(),2)->text());


    }
    if(UniSel=="University ZhengZhou")
    {
        ui->NameEditor->setText(TableModel->item(index.row(),1)->text());
        ui->Teachinghours->setText(TableModel->item(index.row(),5)->text());
        ui->ModuleEditor->setText(TableModel->item(index.row(),3)->text());
        ui->Credit->setText(TableModel->item(index.row(),4)->text());
        QString getType=TableModel->item(index.row(),2)->text();
        int Index=-1;
        Index=ui->Typebox->findText(getType);
        if(Index!=-1)
        {
            ui->Typebox->setCurrentIndex(Index);
        }
        else
        {
            std::wcout<<"Unexpected Type!"<<endl;
            QMessageBox::critical(NULL,"Error","Unexpected Type!");
        }

    }
}

void LectureEditor::slot_sortbyColumn(int column)
{
    ui->LectureView->sortByColumn(column);
}

void LectureEditor::on_InsertButton_clicked()
{
    if(ui->NameEditor->text().isEmpty())
    {
        QMessageBox::critical(NULL,"Error","No Lecture Name input!");
        qDebug()<<"No Lecture Name input!";
        wcout<<"No Lecture Name input!"<<endl;
    }
    else
    {
        auto UniSel=ui->UniSelect->currentText();
        SQLFactory factory;
        auto insert=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("insertlecture"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        if(UniSel=="University Duisburg-Essen")
        {
            input->Type="insertlecture";
            QString LectureName=ui->NameEditor->text();
            QString Semester=ui->SemesterEditor->text();
            QString Module=ui->ModuleEditor->text();
            QString EACTSCredit=ui->Credit->text();
            QString Teachinghours=ui->Teachinghours->text();
            inputlist->append("UDE");
            inputlist->append(LectureName);
            inputlist->append(Semester);
            inputlist->append(Module);
            inputlist->append(EACTSCredit);
            inputlist->append(Teachinghours);
            input->ExchangeData=inputlist;
        }
        if(UniSel=="University ZhengZhou")
        {
            input->Type="insertlecture";
            QString LectureName=ui->NameEditor->text();
            QString Type=ui->Typebox->currentText();
            QString Module=ui->ModuleEditor->text();
            QString CreditinUDE=ui->Credit->text();
            QString Teachinghours=ui->Teachinghours->text();
            inputlist->append("ZZU");
            inputlist->append(LectureName);
            inputlist->append(Type);
            inputlist->append(Module);
            inputlist->append(CreditinUDE);
            inputlist->append(Teachinghours);
            input->ExchangeData=inputlist;
        }
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

void LectureEditor::on_DelButton_clicked()
{
    int currrow=-1;
    currrow=ui->LectureView->currentIndex().row();
    if(currrow==-1)
    {
        QMessageBox::critical(NULL,"Error","No row selected!");
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
    }
    else
    {
        auto UniSel=ui->UniSelect->currentText();
        SQLFactory factory;
        auto del=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("deletelecture"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        if(UniSel=="University Duisburg-Essen")
        {
            input->Type="deletelecture";
            inputlist->append("UDE");

            QString UID=TableModel->item(currrow,0)->text();
            inputlist->append(UID);
            input->ExchangeData=inputlist;
        }
        if(UniSel=="University ZhengZhou")
        {
            input->Type="deletelecture";
            inputlist->append("ZZU");
            QString UID=TableModel->item(currrow,0)->text();
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

void LectureEditor::on_UpdateButton_clicked()
{
    int currrow=-1;
    currrow=ui->LectureView->currentIndex().row();
    if(currrow==-1)
    {
        QMessageBox::critical(NULL,"Error","No row selected!");
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
    }
    else
    {
        auto UniSel=ui->UniSelect->currentText();
        SQLFactory factory;
        auto upd=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("updatelecture"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        if(UniSel=="University Duisburg-Essen")
        {
            QString UID=TableModel->item(currrow,0)->text();
            input->Type="updatelecture";
            QString LectureName=ui->NameEditor->text();
            QString Semester=ui->SemesterEditor->text();
            QString Module=ui->ModuleEditor->text();
            QString EACTSCredit=ui->Credit->text();
            QString Teachinghours=ui->Teachinghours->text();
            inputlist->append("UDE");
            inputlist->append(LectureName);
            inputlist->append(Semester);
            inputlist->append(Module);
            inputlist->append(EACTSCredit);
            inputlist->append(Teachinghours);
            inputlist->append(UID);
            input->ExchangeData=inputlist;
        }
        if(UniSel=="University ZhengZhou")
        {
            QString UID=TableModel->item(currrow,0)->text();
            input->Type="updatelecture";
            QString LectureName=ui->NameEditor->text();
            QString Type=ui->Typebox->currentText();
            QString Module=ui->ModuleEditor->text();
            QString CreditinUDE=ui->Credit->text();
            QString Teachinghours=ui->Teachinghours->text();
            inputlist->append("ZZU");
            inputlist->append(LectureName);
            inputlist->append(Type);
            inputlist->append(Module);
            inputlist->append(CreditinUDE);
            inputlist->append(Teachinghours);
            inputlist->append(UID);
            input->ExchangeData=inputlist;
        }
        upd->inputdata(input);
        upd->setdb(db->getdb());
        auto res=upd->exec();
        if(res)
        {
            QMessageBox::information(NULL,"Info","Update finished.");
        }
        else
        {
            QMessageBox::critical(NULL,"Error","Error happens during Update operation!");
        }
    }

}

void LectureEditor::on_ExportButton_clicked()
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
        auto UniSel=ui->UniSelect->currentText();
        if(UniSel=="University Duisburg-Essen")
        {
            out<<"LectureName,Semester,Module,Credit,Teachinghours\n";
        }
        if(UniSel=="University ZhengZhou")
        {
            out<<"LectureName,Type,Module,Credit,Teachinghours\n";
        }
        #pragma omp parallel for
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

void LectureEditor::on_EditMap_clicked()
{
    int currow=-1;
    currow=ui->LectureView->currentIndex().row();
    if(currow==-1)
    {
        QMessageBox::critical(NULL,"Error","No data in tableview!");
        wcout<<"No data in tableview!"<<endl;
        qDebug()<<"No data in tableview!";
    }
    else
    {
        QString UID=TableModel->item(currow,0)->text();
        auto Sel=ui->UniSelect->currentText();
        QString uni;
        if(Sel=="University Duisburg-Essen")uni="UDE";
        if(Sel=="University ZhengZhou")uni="ZZU";
        LectureMapDialog* dlg=new LectureMapDialog(this);
        dlg->initDB(db);
        dlg->setUni(uni);
        dlg->setLectUID(UID);
        dlg->prepare();
        dlg->exec();
        delete dlg;
    }

}
