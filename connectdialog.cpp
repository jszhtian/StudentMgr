#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    qDebug()<<"ConnectDialog create";
    wcout<<"ConnectDialog create"<<endl;
}


ConnectDialog::~ConnectDialog()
{
    delete ui;
    qDebug()<<"ConnectDialog destory";
    wcout<<"ConnectDialog destory"<<endl;
}

bool ConnectDialog::GetLoginInfo(shared_ptr<LoginInfo> info)
{
        QString Address=ui->AddressEditor->text();
        QString Username=ui->UserNameEditor->text();
        QString Password=ui->PasswordEditor->text();
        info->qStr_Address=Address;
        info->qStr_Password=Password;
        info->qStr_Username=Username;
        return true;
}
