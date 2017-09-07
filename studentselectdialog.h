#ifndef STUDENTSELECTDIALOG_H
#define STUDENTSELECTDIALOG_H

#include <QDialog>
#include "sqlfactory.h"
#include <QStandardItemModel>

namespace Ui {
class StudentSelectDialog;
}

class StudentSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentSelectDialog(QWidget *parent = 0);
    QString getSelectName();
    QString getSelectStudentID();
    QString getSelectUUID();
    void prepare();
    ~StudentSelectDialog();
    void initDB(shared_ptr<SQLBase> setdb);
private slots:
    void on_FindButton_clicked();

private:
    Ui::StudentSelectDialog *ui;
    shared_ptr<SQLBase> db;
    QStandardItemModel* TableModel=NULL;
};

#endif // STUDENTSELECTDIALOG_H
