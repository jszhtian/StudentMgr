﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProgressDialog>
#include "structdef.h"
#include "common.h"
#include "connectdialog.h"
#include "sqlserver.h"
#include "lectureeditor.h"
#include "thdconnect.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    SQLBase* sqldb=NULL;
    ~MainWindow();
    void recvconnectsignal(bool result);

private slots:
    void on_actionExit_triggered();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
    void on_actionLectureEditor_triggered();

private:
    Ui::MainWindow *ui;
    bool connectstatus=false;
};

#endif // MAINWINDOW_H
