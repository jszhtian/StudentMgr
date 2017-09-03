#ifndef MYPRODLG_H
#define MYPRODLG_H

#include <QObject>
#include <QProgressDialog>
//Repackage of class QProgressDialog to simplified call function
class MyProdlg:public QProgressDialog
{
    Q_OBJECT
public:
    MyProdlg(QWidget *parent = NULL);
};

#endif // MYPRODLG_H
