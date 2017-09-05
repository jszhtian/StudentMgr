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



class listlectureuid:public SQLCommandBase
{
public:
    //input:Type=listlectureuid&data=ZZU||UDE
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

class insertlecture:public SQLCommandBase
{
public:
    //input:Type=insertlecture&data=ZZU||UDE&data1=Lecture infor Strings
    bool inputdata(shared_ptr<queryexchange> input);
    //Output:Type=None
    bool outputdata(shared_ptr<queryexchange> output);
    void setdb(QSqlDatabase setdb);
    bool exec();
private:
    QSqlDatabase db;
    QSqlQuery Query;
    QString Uni;
};

class insertlecturemap:public SQLCommandBase
{
public:
    //input:Type=insertlecturemap&data=ZZU||UDE&data1=LectureUUID1&data2=LectureUUID2
    bool inputdata(shared_ptr<queryexchange> input);
    //Output:Type=None
    bool outputdata(shared_ptr<queryexchange> output);
    void setdb(QSqlDatabase setdb);
    bool exec();
private:
    QSqlDatabase db;
    QSqlQuery Query;
    QString Uni;
};

class deletelecture:public SQLCommandBase
{
public:
    //input:Type=deletelecture&data=ZZU||UDE&data1=LectureUUID1&data2=lectureUUID2
    bool inputdata(shared_ptr<queryexchange> input);
    //Output:None
    bool outputdata(shared_ptr<queryexchange> output);
    void setdb(QSqlDatabase setdb);
    bool exec();
private:
    QSqlDatabase db;
    QSqlQuery Query;
    QString Uni;
};

class deletelecturemap:public SQLCommandBase
{
public:
    //input:Type=deletelecture&data=ZZU||UDE&data1=Lecture UUID
    bool inputdata(shared_ptr<queryexchange> input);
    //Output:None
    bool outputdata(shared_ptr<queryexchange> output);
    void setdb(QSqlDatabase setdb);
    bool exec();
private:
    QSqlDatabase db;
    QSqlQuery Query;
    QString Uni;
};

class updatelecture:public SQLCommandBase
{
public:
    //input:Type=updatelecture&data=ZZU||UDE&data1=Lecture infor Strings
    bool inputdata(shared_ptr<queryexchange> input);
    //Output:None
    bool outputdata(shared_ptr<queryexchange> output);
    void setdb(QSqlDatabase setdb);
    bool exec();
private:
    QSqlDatabase db;
    QSqlQuery Query;
    QString Uni;
};


#endif // SQLFACTORY_H
