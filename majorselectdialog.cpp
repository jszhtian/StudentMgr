#include "majorselectdialog.h"
#include "ui_majorselectdialog.h"

MajorSelectDialog::MajorSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MajorSelectDialog)
{
    ui->setupUi(this);
}

MajorSelectDialog::~MajorSelectDialog()
{
    delete ui;
}
