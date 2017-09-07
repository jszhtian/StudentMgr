#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "myprodlg.h"
#include "structdef.h"
#include "common.h"
#include "connectdialog.h"
#include "sqlserver.h"
#include "lectureeditor.h"
#include "thdconnect.h"
#include "majoreditor.h"
#include "studenteditor.h"
#include "scoremgr.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    void recvconnectsignal(bool result);

private slots:
    void on_actionExit_triggered();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
    void on_actionLectureEditor_triggered();

    void on_actionMajorEditor_triggered();

    void on_actionStudentEditor_triggered();

    void on_actionExamEditor_triggered();

private:
    Ui::MainWindow *ui;
    shared_ptr<SQLBase> sqldb;
    bool connectstatus=false;
};

#endif // MAINWINDOW_H
