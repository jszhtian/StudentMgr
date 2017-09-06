#ifndef STUDENTEDITOR_H
#define STUDENTEDITOR_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMessageBox>
#include "common.h"
#include <QFile>
#include <QDate>
#include <QFileDialog>
#include "sqlbase.h"
#include "sqlfactory.h"

namespace Ui {
class StudentEditor;
}

class StudentEditor : public QWidget
{
    Q_OBJECT

public:
    explicit StudentEditor(QWidget *parent = 0);
    ~StudentEditor();
    void initDB(shared_ptr<SQLBase> setdb);

private slots:
    void on_REFButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_UpdateButton_clicked();

    void on_InsertButton_clicked();

    void on_deleteButton_clicked();

    void on_ExportButton_clicked();

private:
    void InitViewModel();
    void getMajorMap();
    void fillmodel(QStringList *list);
    void getList();
    Ui::StudentEditor *ui;
    shared_ptr<SQLBase> db;
    QStandardItemModel* TableModel=NULL;
    std::map<string,string> ZZUMajor;
};

#endif // STUDENTEDITOR_H
