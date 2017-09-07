#ifndef SCOREMGR_H
#define SCOREMGR_H

#include <QWidget>
#include <QMessageBox>
#include "common.h"
#include "sqlbase.h"
#include "sqlfactory.h"
#include <QStandardItemModel>
#include <QFile>
#include <QFileDialog>
#include "lecturemapdialog.h"
#include "studentselectdialog.h"

namespace Ui {
class ScoreMgr;
}

class ScoreMgr : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreMgr(QWidget *parent = 0);
    ~ScoreMgr();
    void initDB(shared_ptr<SQLBase> setdb);

private slots:
    void on_SelStuButton_clicked();

    void on_LecSelButton_clicked();

    void on_ExamTypeBox_activated(const QString &arg1);

    void on_RefButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_InsertButton_clicked();

    void on_timeoptionBox_toggled(bool checked);

    void on_UpdateButton_clicked();

    void on_DeleteButton_clicked();

    void on_ExportButton_clicked();

private:
    void getlist();
    bool usecurrenttime=false;
    Ui::ScoreMgr *ui;
    void InitViewModel();
    void getMap();
    void fillmodel(QStringList* list);
    QString GetStudentID(QString UUID);
    QString GetStudentUUID(QString SID);
    QString GetLectureUUID(QString Name);
    QString GettimeStamp();
    QStandardItemModel* TableModel=NULL;
    shared_ptr<SQLBase> db;
    std::map<string,string> StudentIDMap;
    std::map<string,string> LectureMap;
};

#endif // SCOREMGR_H
