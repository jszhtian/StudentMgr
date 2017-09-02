#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recvconnectsignal(bool result)
{

    if (!result)
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
}

void MainWindow::on_actionExit_triggered()
{
    //add something here
    QApplication::exit();//exit action
}

void MainWindow::on_actionConnect_triggered()
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
        auto SerInfo=shared_ptr<LoginInfo>(new LoginInfo);
        auto res=login->GetLoginInfo(SerInfo);
        if(!res)
        {
            QMessageBox::critical(NULL,"Error","Get Login information failed!");
        }
        else
        {
            sqldb=new SQLServer(SerInfo->qStr_Address,SerInfo->qStr_Username,SerInfo->qStr_Password);
            //auto dbres=sqldb->connect();
            //set profressdialog
            QProgressDialog progressDlg(this);
            progressDlg.setWindowModality(Qt::WindowModal);
            progressDlg.setMinimum(0);
            progressDlg.setMaximum(0);
            progressDlg.setLabelText("Connecting...");
            progressDlg.setCancelButton(0);
            progressDlg.setWindowFlags(progressDlg.windowFlags()&~Qt::WindowCloseButtonHint);
            progressDlg.show();
            //change to multi thread method
            auto m_thread=new thdconnect(this);
            //connect thread signal->mainwindow slot
            connect(m_thread,&thdconnect::result,this,&MainWindow::recvconnectsignal);
            m_thread->setdb(sqldb);
            m_thread->start();
            //m_thread->wait();
            while(!m_thread->isFinished())
            {
                qApp->processEvents();
            }
            progressDlg.close();

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

void MainWindow::on_actionDisconnect_triggered()
{
    if (sqldb==NULL)
    {
        QMessageBox::information(NULL,"Info","No Active ODBC connection.");
    }
    else
    {
        try
        {
            sqldb->disconnect();
            delete sqldb;
            sqldb=NULL;
            QMessageBox::information(NULL,"Info","ODBC connection disconnected.");
            ui->menuEditor->setEnabled(false);
        }
        catch(exception& e)
        {
            string err=e.what();
            QString info=QString::fromStdString(err);
            QMessageBox::critical(NULL,"Error",info);
            std::cout<<e.what()<<endl;
        }
    }

}

void MainWindow::on_actionLectureEditor_triggered()
{
    LectureEditor* newwidget=new LectureEditor(this);
    setCentralWidget(newwidget);
}
