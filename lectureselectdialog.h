#ifndef LECTURESELECTDIALOG_H
#define LECTURESELECTDIALOG_H

#include <QDialog>
#include <QString>
#include "sqlfactory.h"


namespace Ui {
class lectureselectDialog;
}

class lectureselectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit lectureselectDialog(QWidget *parent = 0);
    ~lectureselectDialog();
    void SetUni(QString);
    QString getSelectName();
    void initDB(shared_ptr<SQLBase> setdb);

private slots:
    void on_pushButton_clicked();

private:
    Ui::lectureselectDialog *ui;
    shared_ptr<SQLBase> db;
    QString Uni;
};

#endif // LECTURESELECTDIALOG_H
