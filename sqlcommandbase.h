#ifndef SQLCOMMANDBASE_H
#define SQLCOMMANDBASE_H
#include "common.h"
#include "structdef.h"
#include "sqlbase.h"
class SQLCommandBase{
public:
    virtual ~SQLCommandBase(){}
    virtual bool inputdata(shared_ptr<queryexchange> input)=0;
    virtual bool outputdata(shared_ptr<queryexchange> output)=0;
    virtual bool exec()=0;
    virtual void setdb(QSqlDatabase setdb)=0;
};
#endif // SQLCOMMANDBASE_H
