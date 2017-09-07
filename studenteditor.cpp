#include "studenteditor.h"
#include "ui_studenteditor.h"

StudentEditor::StudentEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentEditor)
{
    TableModel=new QStandardItemModel();
    ui->setupUi(this);
    InitViewModel();
    ui->tableView->setModel(TableModel);
    ui->tableView->setColumnHidden(0,true);
    connect(ui->tableView->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(slot_sortbyColumn(int)));
    qDebug()<<"studenteditor create";
    wcout<<"studenteditor create"<<endl;
}

StudentEditor::~StudentEditor()
{
    delete TableModel;
    delete ui;
}

void StudentEditor::initDB(shared_ptr<SQLBase> setdb)
{
    db=setdb;
}

void StudentEditor::InitViewModel()
{
    TableModel->clear();
    TableModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("StudentUUID")));
    TableModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("StudentID")));
    TableModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("Name")));
    TableModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("Birthday")));
    TableModel->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("IDNumber")));
    TableModel->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("Class")));
    TableModel->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("Gender")));
    TableModel->setHorizontalHeaderItem(7,new QStandardItem(QObject::tr("Grade")));
    TableModel->setHorizontalHeaderItem(8,new QStandardItem(QObject::tr("StudO")));
    TableModel->setHorizontalHeaderItem(9,new QStandardItem(QObject::tr("MajorinZZU")));
    TableModel->setHorizontalHeaderItem(10,new QStandardItem(QObject::tr("MajorinUDE")));
}

void StudentEditor::getMajorMap()
{
    ZZUMajor.clear();
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
}

void StudentEditor::fillmodel(QStringList* List)
{
    InitViewModel();
    for(int itr=0;itr<List->size();++itr)
    {
        QString tmp=List->at(itr);
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
        auto Row10=new QStandardItem(attrs.at(10));
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
        newRow.append(Row10);
        TableModel->appendRow(newRow);
    }
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->resizeColumnsToContents();
}

void StudentEditor::getList()
{
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
        fillmodel(output->ExchangeData);
    }

}

void StudentEditor::on_REFButton_clicked()
{
    getList();
    getMajorMap();
}

void StudentEditor::on_tableView_clicked(const QModelIndex &index)
{
    ui->STDIDEdit->setText(TableModel->item(index.row(),1)->text());
    ui->NameEdit->setText(TableModel->item(index.row(),2)->text());
    QDate birthday=QDate::fromString(TableModel->item(index.row(),3)->text(),"yyyy-MM-dd");
    ui->dateEdit->setDate(birthday);
    ui->IDEdit->setText(TableModel->item(index.row(),4)->text());
    ui->ClassEdit->setText(TableModel->item(index.row(),5)->text());
    ui->GenderBox->setCurrentText(TableModel->item(index.row(),6)->text());
    ui->GradeEdit->setText(TableModel->item(index.row(),7)->text());
    ui->stdoBox->setCurrentText(TableModel->item(index.row(),8)->text());
    ui->ZZUEdit->setText(TableModel->item(index.row(),9)->text());
    ui->UDEEdit->setText(TableModel->item(index.row(),10)->text());
}

void StudentEditor::on_UpdateButton_clicked()
{
    int currrow=-1;
    currrow=ui->tableView->currentIndex().row();
    if(currrow==-1)
    {
        QMessageBox::critical(NULL,"Error","No row selected!");
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
    }
    else
    {
        QString UUID=TableModel->item(currrow,0)->text();
        QString STDID=ui->STDIDEdit->text();
        QString name=ui->NameEdit->text();
        QString birthday=ui->dateEdit->date().toString("yyyy-MM-dd");
        QString IDnum=ui->IDEdit->text();
        QString Class=ui->ClassEdit->text();
        QString Gender=ui->GenderBox->currentText();
        QString Grade=ui->GradeEdit->text();
        QString StudO=ui->stdoBox->currentText();
        QString ZZUName=ui->ZZUEdit->text();
        auto it=ZZUMajor.find(ZZUName.toStdString());
        if(it==ZZUMajor.end())
        {
            wcout<<"Can not find pair in MajorMap!"<<endl;
            qDebug()<<"Can not find pair in MajorMap!";
            QMessageBox::critical(NULL,"Error","Can not find pair in MajorMap! Please refresh the window.");
        }
        else
        {
            QString ZZUUUID=QString::fromStdString(it->second);
            SQLFactory factory;
            auto upd=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("updatestudent"));
            auto input=shared_ptr<queryexchange>(new queryexchange);
            auto inputlist=new QStringList;
            input->Type="updatestudent";
            inputlist->append(UUID);
            inputlist->append(STDID);
            inputlist->append(name);
            inputlist->append(birthday);
            inputlist->append(IDnum);
            inputlist->append(Class);
            inputlist->append(Gender);
            inputlist->append(Grade);
            inputlist->append(StudO);
            inputlist->append(ZZUUUID);
            input->ExchangeData=inputlist;
            upd->inputdata(input);
            upd->setdb(db->getdb());
            auto res=upd->exec();
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

void StudentEditor::on_InsertButton_clicked()
{
    QString STDID=ui->STDIDEdit->text();
    QString name=ui->NameEdit->text();
    QString birthday=ui->dateEdit->date().toString("yyyy-MM-dd");
    QString IDnum=ui->IDEdit->text();
    QString Class=ui->ClassEdit->text();
    QString Gender=ui->GenderBox->currentText();
    QString Grade=ui->GradeEdit->text();
    QString StudO=ui->stdoBox->currentText();
    QString ZZUName=ui->ZZUEdit->text();
    auto it=ZZUMajor.find(ZZUName.toStdString());
    if(it==ZZUMajor.end())
    {
        wcout<<"Can not find pair in MajorMap!"<<endl;
        qDebug()<<"Can not find pair in MajorMap!";
        QMessageBox::critical(NULL,"Error","Can not find pair in MajorMap! Please refresh the window.");
    }
    else
    {
        QString ZZUUUID=QString::fromStdString(it->second);
        SQLFactory factory;
        auto insert=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("insertstudent"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        input->Type="insertstudent";
        inputlist->append(STDID);
        inputlist->append(name);
        inputlist->append(birthday);
        inputlist->append(IDnum);
        inputlist->append(Class);
        inputlist->append(Gender);
        inputlist->append(Grade);
        inputlist->append(StudO);
        inputlist->append(ZZUUUID);
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
}

void StudentEditor::on_deleteButton_clicked()
{
    int currrow=-1;
    currrow=ui->tableView->currentIndex().row();
    if(currrow==-1)
    {
        QMessageBox::critical(NULL,"Error","No row selected!");
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
    }
    else
    {
        QString UUID=TableModel->item(currrow,0)->text();
        SQLFactory factory;
        auto del=shared_ptr<SQLCommandBase>(factory.CreateSQLCommand("deletestudent"));
        auto input=shared_ptr<queryexchange>(new queryexchange);
        auto inputlist=new QStringList;
        input->Type="deletestudent";
        inputlist->append(UUID);
        input->ExchangeData=inputlist;
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

void StudentEditor::on_ExportButton_clicked()
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
        out<<"StudentID,Name,Birthday,IDNumber,Class,Gender,Grade,StudO,MajorinZZU,MajorinUDE\n";

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

void StudentEditor::on_MajorButton_clicked()
{
    MajorSelectDialog* dlg=new MajorSelectDialog(this);
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
}

void StudentEditor::slot_sortbyColumn(int column)
{
    ui->tableView->sortByColumn(column);
}
