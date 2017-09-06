#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"MainWindow create";
    wcout<<"MainWindow create"<<endl;
}

MainWindow::~MainWindow()
{
    setCentralWidget(NULL);
    delete ui;
    qDebug()<<"MainWindow destory";
    wcout<<"MainWindow destory"<<endl;
}

void MainWindow::recvconnectsignal(bool result)
{

    if (!result)
    {
        QMessageBox::critical(NULL,"Error","Connection Failed!");
    }
    else
    {
        QMessageBox::information(NULL,"Connection","Connection established!");
        ui->menuEditor->setEnabled(true);
        //For Test
        /*
         *
        QSqlQuery query;
        query.exec("SELECT * FROM dbo.test");
        auto db=sqldb->getdb();
        if(!query.isActive())
                {
                    qDebug("Query Failed");
                    qDebug()<<db.lastError().text();
                }
        query.first();
                QString UID=query.value(0).toString();
                QString Name=query.value(1).toString();
                QString AGE=query.value(2).toString();
                qDebug()<<UID<<endl;
                qDebug()<<Name<<endl;
                qDebug()<<AGE<<endl;
                qDebug()<<"Open Success!"<<endl;

         */
    }

}

void MainWindow::on_actionExit_triggered()
{
    //add something here
    QApplication::exit();//exit action
}

void MainWindow::on_actionConnect_triggered()
{
    if(sqldb!=NULL)
    {
        QMessageBox::information(NULL,"Info","Database is connected!");
    }
    else
    {
        ConnectDialog *login=new ConnectDialog;
        if(login->Rejected==login->exec())
        {
            QMessageBox::critical(NULL,tr("Connecting Error"),tr("Please input Server infomation!"));
        }
        else
        {
            //use shared_ptr instead of raw pointer. The Smart pointer will auto release if references counter equal to 0
            //Use Auto. Auto will Identify the return value
            //Normal Qt Object don't need smart ptr because the Qt itself will handle this
            auto SerInfo=shared_ptr<LoginInfo>(new LoginInfo);
            auto res=login->GetLoginInfo(SerInfo);
            if(!res)
            {
                QMessageBox::critical(NULL,"Error","Get Login information failed!");
            }
            else
            {
                sqldb=shared_ptr<SQLServer>(new SQLServer(SerInfo->qStr_Address,SerInfo->qStr_Username,SerInfo->qStr_Password));
                //auto dbres=sqldb->connect();
                //set profressdialog
                MyProdlg prodlg(this);
                /*
                 *  QProgressDialog progressDlg(this);
                progressDlg.setWindowModality(Qt::WindowModal);
                progressDlg.setMinimum(0);
                progressDlg.setMaximum(0);
                progressDlg.setLabelText("Connecting...");
                progressDlg.setCancelButton(0);
                progressDlg.setWindowFlags(progressDlg.windowFlags()&~Qt::WindowCloseButtonHint);
                */

                prodlg.show();
                //change to multi thread method
                auto m_thread=new thdconnect();
                //connect thread signal->mainwindow slot
                connect(m_thread,&thdconnect::result,this,&MainWindow::recvconnectsignal);
                m_thread->setdb(sqldb);
                m_thread->start();
                //m_thread->wait();
                while(!m_thread->isFinished())
                {
                    qApp->processEvents();
                }
                prodlg.close();

                //disconnect signal/slot connect
                disconnect(m_thread,&thdconnect::result,this,&MainWindow::recvconnectsignal);
                /*
                if (!connectstatus)
                {
                    QMessageBox::critical(NULL,"Error","Connection Failed!");
                    delete sqldb;
                    sqldb=NULL;
                }
                else
                {
                    QMessageBox::information(NULL,"Connection","Connection established!");
                    ui->menuEditor->setEnabled(true);
                }
                */

            }
        }
        delete login;
    }

}

void MainWindow::on_actionDisconnect_triggered()
{
    if (sqldb==NULL)
    {
        QMessageBox::information(NULL,"Info","No Active ODBC connection.");
    }
    else
    {
        sqldb->disconnect();
        QMessageBox::information(NULL,"Info","ODBC connection disconnected.");
        ui->menuEditor->setEnabled(false);
        setCentralWidget(NULL);
        sqldb.reset();
    }

}

void MainWindow::on_actionLectureEditor_triggered()
{
    LectureEditor* newwidget=new LectureEditor(this);
    newwidget->initDB(sqldb);
    setCentralWidget(newwidget);
}

void MainWindow::on_actionMajorEditor_triggered()
{
    MajorEditor* newwidget=new MajorEditor(this);
    newwidget->initDB(sqldb);
    setCentralWidget(newwidget);
}

void MainWindow::on_actionStudentEditor_triggered()
{
    StudentEditor* newwidget=new StudentEditor(this);
    newwidget->initDB(sqldb);
    setCentralWidget(newwidget);
}
