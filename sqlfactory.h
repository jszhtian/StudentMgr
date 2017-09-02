#ifndef SQLFACTORY_H
#define SQLFACTORY_H
#include "common.h"
#include "sqlcommandbase.h"
class SQLFactory
{
public:
    SQLFactory();
    SQLCommandBase* CreateSQLCommand(QString COMname);
};

class liststudent:public SQLCommandBase
{
public:
    ~liststudent();
    bool inputdata(queryexchange* input);
    bool outputdata(queryexchange* output);
private:
    QStringList* outputlist;
};
#endif // SQLFACTORY_H
