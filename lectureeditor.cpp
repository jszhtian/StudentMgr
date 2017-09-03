#include "lectureeditor.h"
#include "ui_lectureeditor.h"

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
}

LectureEditor::~LectureEditor()
{
    delete ui;
    delete TableModel;
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
    ui->LectureView->setColumnHidden(0,true);
    ui->LectureView->resizeColumnsToContents();
}

void LectureEditor::GetList()
{
    auto UniSel=ui->UniSelect->currentText();
    SQLFactory factory;
    SQLCommandBase* listlecture=factory.CreateSQLCommand("listlecture");
    auto input=shared_ptr<queryexchange>(new queryexchange);
    auto inputlist=new QStringList;
    if(UniSel=="University Duisburg-Essen")
    {
        input->Type="ListLecture";
        inputlist->append("UDE");
        input->ExchangeData=inputlist;
    }
    if(UniSel=="University ZhengZhou")
    {
        input->Type="ListLecture";
        inputlist->append("ZZU");
        input->ExchangeData=inputlist;
    }
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
        GetList();
    }
    if(arg1=="University Duisburg-Essen")
    {
        ui->Typebox->setEnabled(false);
        ui->SemesterEditor->setEnabled(true);
        GetList();
    }
}



void LectureEditor::on_ReFButton_clicked()
{
    auto type=ui->FilterTypeSelect->currentText();
    auto opera=ui->OperationBox->currentText();
    auto condit=ui->conditionEditor->text();
    auto UniSel=ui->UniSelect->currentText();
    if(type=="None")
    {
        GetList();
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

       SQLFactory factory;
       SQLCommandBase* listlecture=factory.CreateSQLCommand("listlecturemap");
       auto input=shared_ptr<queryexchange>(new queryexchange);
       auto inputlist=new QStringList;
       input->Type="ListLectureMap";
       inputlist->append("UDE");
       inputlist->append(TableModel->item(index.row(),0)->text());
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
           int capsize=output->ExchangeData->size();
           QString Str;
           for(int i=0;i<capsize;i++)
           {
               Str+=output->ExchangeData->at(i);
               Str+=";";
           }
           ui->MapEditor->setText(Str);
       }
       else
       {
           QMessageBox::critical(NULL,"Error","SQL command execute failed!");
       }
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
            std::cout<<"Unexpected Type!"<<endl;
            QMessageBox::critical(NULL,"Error","Unexpected Type!");
        }
        SQLFactory factory;
        SQLCommandBase* listlecture=factory.CreateSQLCommand("listlecturemap");
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        input->Type="ListLectureMap";
        inputlist->append("ZZU");
        inputlist->append(TableModel->item(index.row(),0)->text());
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
            int capsize=output->ExchangeData->size();
            QString Str;
            for(int i=0;i<capsize;i++)
            {
                Str+=output->ExchangeData->at(i);
                Str+=";";
            }
            ui->MapEditor->setText(Str);
        }
        else
        {
            QMessageBox::critical(NULL,"Error","SQL command execute failed!");
        }
    }
}

void LectureEditor::slot_sortbyColumn(int column)
{
    ui->LectureView->sortByColumn(column);
}
