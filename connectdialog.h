#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

#include "structdef.h"
#include "common.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();
    bool GetLoginInfo(shared_ptr<LoginInfo> info);

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
