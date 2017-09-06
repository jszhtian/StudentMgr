#ifndef MAJOREDITOR_H
#define MAJOREDITOR_H

#include <QWidget>
#include <QString>
#include "sqlbase.h"
#include <QMessageBox>
#include "common.h"
#include "sqlfactory.h"
#include "lectureselectdialog.h"
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


private slots:
    void on_Unibox_activated(const QString &arg1);

    void on_pushButton_clicked();
    void slot_sortbyColumn(int);

    void on_MajorView_clicked(const QModelIndex &index);

    void on_InsertButton_clicked();

    void on_DeleteButton_clicked();

    void on_Updatebutton_clicked();

    void on_loadLectureButton_clicked();

    void on_AddLectureButton_clicked();

    void on_DeleteLecture_clicked();

private:
    void InitViewModel();
    void GetList();
    void GetUIDMap();
    void GetLectureUIDMap();
    void fillthemodel(QStringList *list);
    Ui::MajorEditor *ui;
    shared_ptr<SQLBase> db;
    std::map<string,string> UDEMajor;
    std::map<string,string> ZZUMajor;
    std::map<string,string> UDELecture;
    std::map<string,string> ZZULecture;
    QStandardItemModel* TableModel=NULL;
};

#endif // MAJOREDITOR_H
