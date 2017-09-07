#include "scoremgr.h"
#include "ui_scoremgr.h"

ScoreMgr::ScoreMgr(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScoreMgr)
{
    ui->setupUi(this);
}

ScoreMgr::~ScoreMgr()
{
    delete ui;
}
