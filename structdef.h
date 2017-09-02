#ifndef STRUCTDEF_H
#define STRUCTDEF_H
//define struct
#include "common.h"
struct LoginInfo{
    QString qStr_Address;
    QString qStr_Username;
    QString qStr_Password;
};

struct queryexchange{
    QString Type;
    QStringList* ExchangeData;
};
#endif // STRUCTDEF_H
