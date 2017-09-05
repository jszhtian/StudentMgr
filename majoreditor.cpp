#include "majoreditor.h"
#include "ui_majoreditor.h"

MajorEditor::MajorEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MajorEditor)
{
    ui->setupUi(this);
}

MajorEditor::~MajorEditor()
{
    delete ui;
}

void MajorEditor::initDB(shared_ptr<SQLBase> setdb)
{
    db=setdb;
}
