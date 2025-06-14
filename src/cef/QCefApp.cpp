#include "QCefApp.h"
#include "include/cef_command_line.h"

QCefApp::ProcessType QCefApp::GetProcessType(CefRefPtr<CefCommandLine> command_line)
{
    auto type_key = "type";

    if (!command_line->HasSwitch(type_key))
    {
        return BrowserProcess;
    }

    auto type_value = command_line->GetSwitchValue(type_key);
    if (type_value == "renderer")
    {
        return RendererProcess;
    }

    return OtherProcess;
}

QCefApp::QCefApp()
{
}

QCefApp::~QCefApp()
{
}
