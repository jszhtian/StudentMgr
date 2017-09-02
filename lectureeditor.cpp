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
