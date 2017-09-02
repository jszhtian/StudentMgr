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
    void initDB(shared_ptr<SQLBase> setdb);

private slots:
    void on_UniSelect_activated(const QString &arg1);

private:
    Ui::LectureEditor *ui;
    shared_ptr<SQLBase> db;
};

#endif // LECTUREEDITOR_H
