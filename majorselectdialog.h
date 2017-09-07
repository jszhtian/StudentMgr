#ifndef MAJORSELECTDIALOG_H
#define MAJORSELECTDIALOG_H

#include <QDialog>
#include <QString>
#include "sqlfactory.h"

namespace Ui {
class MajorSelectDialog;
}

class MajorSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MajorSelectDialog(QWidget *parent = 0);
    ~MajorSelectDialog();
    QString getSelectName();
    QString getSelectUID();
    void prepare();
    void SetUni(QString);
    void initDB(shared_ptr<SQLBase> setdb);

private slots:
    void on_REFButton_clicked();

private:
    Ui::MajorSelectDialog *ui;
    shared_ptr<SQLBase> db;
    QString Uni;
    std::map<string,string> MajorMap;
};

#endif // MAJORSELECTDIALOG_H
