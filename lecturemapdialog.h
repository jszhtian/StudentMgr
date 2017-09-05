#ifndef LECTUREMAPDIALOG_H
#define LECTUREMAPDIALOG_H

#include <QDialog>
#include "lectureselectdialog.h"
#include <QMessageBox>

namespace Ui {
class LectureMapDialog;
}

class LectureMapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LectureMapDialog(QWidget *parent = 0);
    ~LectureMapDialog();
    void setUni(QString);
    void initDB(shared_ptr<SQLBase> setdb);
    void setLectUID(QString UID);
private slots:
    void on_AddBut_clicked();

    void on_RefreshButton_clicked();

private:
    Ui::LectureMapDialog *ui;
    shared_ptr<SQLBase> db;
    QString Uni;
    QString lectUID;
};

#endif // LECTUREMAPDIALOG_H
