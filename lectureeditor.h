#ifndef LECTUREEDITOR_H
#define LECTUREEDITOR_H

#include <QWidget>
#include <QMessageBox>
#include "common.h"
#include "sqlbase.h"
#include "sqlfactory.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QFile>
#include <QFileDialog>
#include "lecturemapdialog.h"

namespace Ui {
class LectureEditor;
}

class LectureEditor : public QWidget
{
    Q_OBJECT

public:
    explicit LectureEditor(QWidget *parent = 0);
    ~LectureEditor();
    void initDB(shared_ptr<SQLBase> setdb);



private slots:
    void on_UniSelect_activated(const QString &arg1);
    void on_ReFButton_clicked();
    void on_LectureView_clicked(const QModelIndex &index);
    void slot_sortbyColumn(int);

    void on_InsertButton_clicked();

    void on_DelButton_clicked();

    void on_UpdateButton_clicked();

    void on_ExportButton_clicked();

    void on_EditMap_clicked();

private:
    void InitViewModel();
    void fillthemodel(QStringList* list);
    //void updateLectureUIDmap();
    void GetList();
    Ui::LectureEditor *ui;
    shared_ptr<SQLBase> db;
    QStandardItemModel* TableModel=NULL;
    //std::map<string,string> UDElectMap;
    //std::map<string,string> ZZUlectMap;
};

#endif // LECTUREEDITOR_H
