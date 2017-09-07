#include "studentselectdialog.h"
#include "ui_studentselectdialog.h"

StudentSelectDialog::StudentSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentSelectDialog)
{
    TableModel=new QStandardItemModel();
    ui->setupUi(this);
    qDebug()<<"StudentSelectDialog create";
    wcout<<"StudentSelectDialog create"<<endl;
    TableModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("StudentUUID")));
    TableModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("StudentID")));
    TableModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("Name")));
    ui->tableView->setModel(TableModel);
    ui->tableView->setColumnHidden(0,true);
}

QString StudentSelectDialog::getSelectName()
{
    int currrow=-1;
    currrow=ui->tableView->currentIndex().row();
    if(currrow==-1)
    {
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
        return QString("NULL");
    }
    else
    {
        QString Name=TableModel->item(currrow,2)->text();
        return Name;
    }
}

QString StudentSelectDialog::getSelectStudentID()
{
    int currrow=-1;
    currrow=ui->tableView->currentIndex().row();
    if(currrow==-1)
    {
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
        return QString("NULL");
    }
    else
    {
        QString STDID=TableModel->item(currrow,1)->text();
        return STDID;
    }
}

QString StudentSelectDialog::getSelectUUID()
{
    int currrow=-1;
    currrow=ui->tableView->currentIndex().row();
    if(currrow==-1)
    {
        qDebug()<<"No row selected!";
        wcout<<"No row selected!"<<endl;
        return QString("NULL");
    }
    else
    {
        QString UUID=TableModel->item(currrow,0)->text();
        return UUID;
    }
}

void StudentSelectDialog::prepare()
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
            QList<QStandardItem*> newRow;
            auto Row0=new QStandardItem(attrs.at(0));
            auto Row1=new QStandardItem(attrs.at(1));
            auto Row2=new QStandardItem(attrs.at(2));
            newRow.append(Row0);
            newRow.append(Row1);
            newRow.append(Row2);
            TableModel->appendRow(newRow);
        }
    }
    ui->tableView->resizeColumnsToContents();
}


StudentSelectDialog::~StudentSelectDialog()
{
    delete ui;
    delete TableModel;
    qDebug()<<"StudentSelectDialog destory";
    wcout<<"StudentSelectDialog destory"<<endl;
}

void StudentSelectDialog::initDB(shared_ptr<SQLBase> setdb)
{
    db=setdb;
}

void StudentSelectDialog::on_FindButton_clicked()
{
    int rows=TableModel->rowCount();
    
    for(int i=0;i<rows;i++)
    {
        ui->tableView->showRow(i);
    }
    auto type=ui->comboBox->currentText();
    auto cond=ui->FindEdit->text();
    if(!cond.isEmpty())
    {
        if(type=="Name")
        {
            
            for(int i=0;i<rows;i++)
            {
                QString name=TableModel->item(i,2)->text();
                if(!name.toLower().contains(cond.toLower()))
                {
                    ui->tableView->hideRow(i);
                }
            }
        }
        if(type=="StudentID")
        {
            
            for(int i=0;i<rows;i++)
            {
                QString stdID=TableModel->item(i,1)->text();
                if(!stdID.contains(cond))
                {
                    ui->tableView->hideRow(i);
                }
            }
        }
    }

}
