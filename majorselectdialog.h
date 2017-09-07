#ifndef MAJORSELECTDIALOG_H
#define MAJORSELECTDIALOG_H

#include <QDialog>

namespace Ui {
class MajorSelectDialog;
}

class MajorSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MajorSelectDialog(QWidget *parent = 0);
    ~MajorSelectDialog();

private:
    Ui::MajorSelectDialog *ui;
};

#endif // MAJORSELECTDIALOG_H
