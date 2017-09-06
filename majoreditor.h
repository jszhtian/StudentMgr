#ifndef MAJOREDITOR_H
#define MAJOREDITOR_H

#include <QWidget>
#include <QString>
#include "sqlbase.h"
#include <QMessageBox>
#include "common.h"
#include "sqlfactory.h"
#include <QStandardItemModel>
namespace Ui {
class MajorEditor;
}

class MajorEditor : public QWidget
{
    Q_OBJECT

public:
    explicit MajorEditor(QWidget *parent = 0);
    ~MajorEditor();
    void initDB(shared_ptr<SQLBase> setdb);
    void InitViewModel();
    void GetList();
    void GetUIDMap();
    void fillthemodel(QStringList *list);

private slots:
    void on_Unibox_activated(const QString &arg1);

    void on_pushButton_clicked();
    void slot_sortbyColumn(int);

    void on_MajorView_clicked(const QModelIndex &index);

private:

    Ui::MajorEditor *ui;
    shared_ptr<SQLBase> db;
    std::map<string,string> UDEMajor;
    std::map<string,string> ZZUMajor;
    QStandardItemModel* TableModel=NULL;
};

#endif // MAJOREDITOR_H