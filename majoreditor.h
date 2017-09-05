#ifndef MAJOREDITOR_H
#define MAJOREDITOR_H

#include <QWidget>
#include "sqlbase.h"
#include "common.h"
#include "sqlfactory.h"
namespace Ui {
class MajorEditor;
}

class MajorEditor : public QWidget
{
    Q_OBJECT

public:
    explicit MajorEditor(QWidget *parent = 0);
    ~MajorEditor();
    void initDB(shared_ptr<SQLBase> setdb);

private:
    Ui::MajorEditor *ui;
    shared_ptr<SQLBase> db;
};

#endif // MAJOREDITOR_H
