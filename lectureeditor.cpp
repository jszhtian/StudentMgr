#include "lectureeditor.h"
#include "ui_lectureeditor.h"

LectureEditor::LectureEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LectureEditor)
{
    ui->setupUi(this);
}

LectureEditor::~LectureEditor()
{
    delete ui;
}

void LectureEditor::initDB(shared_ptr<SQLBase> setdb)
{
    db=setdb;
}

void LectureEditor::on_UniSelect_activated(const QString &arg1)
{
    if(arg1=="University ZhengZhou")
    {
        ui->TypeSelect->setEnabled(true);
        ui->SemesterEditor->setEnabled(false);
    }
    if(arg1=="University Duisburg-Essen")
    {
        ui->TypeSelect->setEnabled(false);
        ui->SemesterEditor->setEnabled(true);
    }
}
