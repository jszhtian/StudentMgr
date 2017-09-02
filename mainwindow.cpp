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
            auto dbres=sqldb->connect();
            if (!dbres)
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
        }
        catch(exception& e)
        {
            string err=e.what();
            QString info=QString::fromStdString(err);
            QMessageBox::critical(NULL,"Error",info);
        }
    }

}
