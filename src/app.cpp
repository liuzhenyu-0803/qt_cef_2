#include "app.h"


App::App(int &argc, char **argv)
    : QApplication(argc, argv)
{
}

App::~App()
{
}

void App::quit()
{
    emit signal_before_quit();

    QApplication::quit();
}
