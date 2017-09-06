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

class listmajor:public SQLCommandBase
{
public:
    //input:Type=listmajor&data=ZZU||UDE
    bool inputdata(shared_ptr<queryexchange> input);
    //Output:Type=ZZUlistmajor||UDElistmajor&data is lecture information
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

class listLectureSelect:public SQLCommandBase
{
public:
    //input:Type=listLectureSelect&data0=ZZU|UDE+data1=MajorUID
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

class listmajoruid:public SQLCommandBase
{
public:
    //input:Type=listmajoruid&data=ZZU||UDE
    bool inputdata(shared_ptr<queryexchange> input);
    //Output:Type=ZZUMajor||UDEmajor&data is lecture information
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

class insertmajor:public SQLCommandBase
{
public:
    //input:Type=insertmajor&data=ZZU||UDE&data1=Lecture infor Strings
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

class insertlectureselect:public SQLCommandBase
{
public:
    //input:Type=insertlectureselect&data=ZZU||UDE&data1=MajorUUID&data2=LectureUUID
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

class deletemajor:public SQLCommandBase
{
public:
    //input:Type=deletemajor&data=ZZU||UDE&data1=MajorUUID
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

class deletelectureselect:public SQLCommandBase
{
public:
    //input:Type=deletelectureselect&data=ZZU||UDE&data1=MajorUUI1&data2=lectureUUID
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

class updatemajor:public SQLCommandBase
{
public:
    //input:Type=updatemajor&data=ZZU||UDE&data1=updatemajor infor Strings
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
