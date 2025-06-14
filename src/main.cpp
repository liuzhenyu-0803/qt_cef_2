#include "app.h"
#include "main_window.h"

#include "cef/QCefGlobalDefine.h"

#include "cef/QCefAppBrowser.h"
#include "cef/QCefAppRender.h"

#include <QtWidgets/QApplication>


int main(int argc, char* argv[])
{
    int exit_code = InitializeCef();
    if (exit_code >= 0)
    {
        return exit_code;
    }

    QApplication::setQuitOnLastWindowClosed(false);

    App a(argc, argv);
    MainWindow w;
    w.resize(1600, 1200);
    w.show();
    a.exec();

    UninitializeCef();

    return 0;
}
