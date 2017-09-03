#ifndef LECTUREEDITOR_H
#define LECTUREEDITOR_H

#include <QWidget>
#include <QMessageBox>
#include "common.h"
#include "sqlbase.h"
#include "sqlfactory.h"
#include <QStandardItemModel>

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
    void InitViewModel();


private slots:
    void on_UniSelect_activated(const QString &arg1);


    void on_ReFButton_clicked();

private:
    void fillthemodel(QStringList* list);
    void GetList();
    Ui::LectureEditor *ui;
    shared_ptr<SQLBase> db;
    QStandardItemModel* TableModel=NULL;
};

#endif // LECTUREEDITOR_H
