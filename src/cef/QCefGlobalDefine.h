#ifndef QCEF_GLOBAL_DEFINE_H
#define QCEF_GLOBAL_DEFINE_H

#include "include/cef_browser.h"
#include "include/cef_frame.h"
#include "include/cef_process_message.h"

#include <QMetaType>

Q_DECLARE_METATYPE(CefRefPtr<CefBrowser>)
Q_DECLARE_METATYPE(CefRefPtr<CefFrame>)
Q_DECLARE_METATYPE(CefProcessId)
Q_DECLARE_METATYPE(CefRefPtr<CefProcessMessage>)

static void RegisterCefMetaType()
{
    qRegisterMetaType<CefRefPtr<CefBrowser>>("CefRefPtr<CefBrowser>");
    qRegisterMetaType<CefRefPtr<CefFrame>>("CefRefPtr<CefFrame>");
    qRegisterMetaType<CefProcessId>("CefProcessId");
    qRegisterMetaType<CefRefPtr<CefProcessMessage>>("CefRefPtr<CefProcessMessage>");
}

const char *const RENDER_TO_BROWSER_PROCESS_MESSAGE = "RenderToBrowserProcessMessage";
const char *const BROWSER_TO_RENDER_PROCESS_MESSAGE = "BrowserToRenderProcessMessage";

#include "QCefApp.h"
#include "QCefAppBrowser.h"
#include "QCefAppRender.h"
#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h"
#include "include/cef_app.h"

inline int InitializeCef()
{
    CefMainArgs main_args(GetModuleHandle(nullptr));
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
    RegisterCefMetaType();
    return -1;
}

inline void UninitializeCef()
{
    CefShutdown();
}

#endif // QCEF_GLOBAL_DEFINE_H
