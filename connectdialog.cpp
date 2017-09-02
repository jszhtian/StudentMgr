#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

bool ConnectDialog::GetLoginInfo(shared_ptr<LoginInfo> info)
{
    try{
        QString Address=ui->AddressEditor->text();
        QString Username=ui->UserNameEditor->text();
        QString Password=ui->PasswordEditor->text();
        info->qStr_Address=Address;
        info->qStr_Password=Password;
        info->qStr_Username=Username;
        return true;
    }
    catch(exception& e)
    {
        string err=e.what();
        QString info=QString::fromStdString(err);
        QMessageBox::critical(NULL,"Error",info);
        return false;
    }
}
