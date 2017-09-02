#ifndef SQLCOMMANDBASE_H
#define SQLCOMMANDBASE_H
#include "common.h"
#include "structdef.h"
class SQLCommandBase{
public:
    virtual ~SQLCommandBase();
    virtual bool inputdata(queryexchange* input)=0;
    virtual bool outputdata(queryexchange* output)=0;
};
#endif // SQLCOMMANDBASE_H
