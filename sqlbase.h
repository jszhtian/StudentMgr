#ifndef SQLBASE_H
#define SQLBASE_H
#include <QString>
class SQLBase
{
public:
    SQLBase(){}
    virtual ~SQLBase(){}
    virtual bool connect()=0;
    virtual bool disconnect()=0;
};

#endif // SQLBASE_H
