#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "structdef.h"
#include "common.h"
#include "connectdialog.h"
#include "sqlserver.h"

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

private slots:
    void on_actionExit_triggered();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
