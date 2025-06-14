#include "app.h"
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

    QApplication::setQuitOnLastWindowClosed(false);

    App a(argc, argv);
    MainWindow w;
    w.resize(1600, 1200);
    w.show();
    a.exec();

    uninitializeCef();

    return 0;
}
