#ifndef SCOREMGR_H
#define SCOREMGR_H

#include <QMainWindow>

namespace Ui {
class ScoreMgr;
}

class ScoreMgr : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScoreMgr(QWidget *parent = 0);
    ~ScoreMgr();

private:
    Ui::ScoreMgr *ui;
};

#endif // SCOREMGR_H
