#include "main_window.h"

#include "cef/q_cef_global_define.h"

#include <QApplication>


int main(int argc, char* argv[])
{
    int exitCode = initializeCef();
    if (exitCode >= 0)
    {
        return exitCode;
    }

    QApplication a(argc, argv);
    
    auto w = new MainWindow();
    w->resize(1600, 1200);
    w->show();
    
    a.exec();

    delete w;

    uninitializeCef();

    return 0;
}
