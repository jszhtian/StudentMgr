#ifndef SQLFACTORY_H
#define SQLFACTORY_H
#include "common.h"
#include "sqlcommandbase.h"
#include "myprodlg.h"
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
    void setdb(QSqlDatabase setdb);
    bool exec();
private:
    QStringList* outputlist;
};

class listlecture:public SQLCommandBase
{
public:
    //input:Type=ListLecture&data=ZZU||UDE
    bool inputdata(shared_ptr<queryexchange> input);
    //Output:Type=ZZULecture||UDELecture&data is lecture information
    bool outputdata(shared_ptr<queryexchange> output);
    void setdb(QSqlDatabase setdb);
    bool exec();
private:
    QSqlDatabase db;
    QSqlQuery Query;
    QString Uni;
};

class listLectureMap:public SQLCommandBase
{
public:
    //input:Type=ListLectureMap&data0=ZZU|UDE+data1=LectureUUID
    bool inputdata(shared_ptr<queryexchange> input);
    //Output:Type=ListLectureMap||UDELecture&data is lecture information
    bool outputdata(shared_ptr<queryexchange> output);
    void setdb(QSqlDatabase setdb);
    bool exec();
private:
    QSqlDatabase db;
    QSqlQuery Query;
    QString Uni;
};
#endif // SQLFACTORY_H
