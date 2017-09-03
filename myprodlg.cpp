#include "myprodlg.h"

MyProdlg::MyProdlg(QWidget *parent):QProgressDialog(parent)
{
    this->setWindowModality(Qt::WindowModal);
    this->setMinimum(0);
    this->setMaximum(0);
    this->setLabelText("Working...");
    this->setWindowTitle("Processing...");
    this->setCancelButton(0);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowCloseButtonHint);
    this->show();
}
