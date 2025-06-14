// 实现文件，解决多重定义问题

#include "q_cef_global_define.h"
#include <QMetaType>
#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h"
#include "include/cef_app.h"
#include "q_cef_app.h"
#include "q_cef_app_browser.h"
#include "q_cef_app_render.h"

void registerCefMetaType()
{
    qRegisterMetaType<CefRefPtr<CefBrowser>>("CefRefPtr<CefBrowser>");
    qRegisterMetaType<CefRefPtr<CefFrame>>("CefRefPtr<CefFrame>");
    qRegisterMetaType<CefProcessId>("CefProcessId");
    qRegisterMetaType<CefRefPtr<CefProcessMessage>>("CefRefPtr<CefProcessMessage>");
}

int initializeCef()
{
    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->InitFromString(::GetCommandLineW());

    CefRefPtr<CefApp> app;
    switch (QCefApp::GetProcessType(command_line))
    {
    case QCefApp::BrowserProcess:
        app = new QCefAppBrowser();
        break;
    case QCefApp::RendererProcess:
        app = new QCefAppRender();
        break;
    default:
        break;
    }

    CefMainArgs main_args(GetModuleHandle(nullptr));

    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0)
    {
        return exit_code;
    }

    CefSettings settings;
    settings.multi_threaded_message_loop = true;

    if (!CefInitialize(main_args, settings, app.get(), nullptr))
    {
        return CefGetExitCode();
    }

    registerCefMetaType();

    return -1;
}

void uninitializeCef()
{
    CefShutdown();
}