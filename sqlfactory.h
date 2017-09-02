#ifndef SQLFACTORY_H
#define SQLFACTORY_H
#include "common.h"
#include "sqlcommandbase.h"
#include <QProgressDialog>
#include "thdsqlexec.h"

class SQLFactory
{
public:
    SQLCommandBase* CreateSQLCommand(QString COMname);
};

class liststudent:public SQLCommandBase
{
public:
    ~liststudent();
    bool inputdata(shared_ptr<queryexchange> input);
    bool outputdata(shared_ptr<queryexchange> output);
    void setdb(QSqlDatabase* setdb);
    bool exec();
private:
    QStringList* outputlist;
};

class listlecture:public SQLCommandBase
{
public:
    ~listlecture();
    //input:Type=ListLecture&data=ZZU||UDE
    bool inputdata(shared_ptr<queryexchange> input);
    //Output:Type=ZZULecture||UDELecture&data is lecture information
    bool outputdata(shared_ptr<queryexchange> output);
    void setdb(QSqlDatabase* setdb);
    bool exec();
private:
    QStringList* outputlist;
    QSqlDatabase* db=NULL;
    QSqlQuery Query;
    QString Uni;
};
#endif // SQLFACTORY_H
