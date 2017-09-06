#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <windows.h>
bool debugflag=true;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //add non-ASCII CodePage support
    setlocale(LC_CTYPE, "");
    if(debugflag)
    {
        //open console
        if(AllocConsole())
         {
            //Redirection stdout
          freopen("CONOUT$","w",stdout);
         }
    }
    MainWindow w;
    w.show();

    return a.exec();
}
