#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <windows.h>
bool debugflag=true;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    if(debugflag)
    {
        //open console
        if(AllocConsole())
         {
            //Redirection stdout
          freopen("CONOUT$","w",stdout);
         }
    }
    return a.exec();
}
