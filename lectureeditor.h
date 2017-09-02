#ifndef LECTUREEDITOR_H
#define LECTUREEDITOR_H

#include <QWidget>
#include "common.h"
#include "sqlbase.h"

namespace Ui {
class LectureEditor;
}

class LectureEditor : public QWidget
{
    Q_OBJECT

public:
    explicit LectureEditor(QWidget *parent = 0);
    ~LectureEditor();

private:
    Ui::LectureEditor *ui;
};

#endif // LECTUREEDITOR_H
