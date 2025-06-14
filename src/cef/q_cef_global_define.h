#ifndef QCEF_GLOBAL_DEFINE_H
#define QCEF_GLOBAL_DEFINE_H

#include "include/cef_browser.h"
#include "include/cef_frame.h"
#include "include/cef_process_message.h"

#include "q_cef_app.h"
#include "q_cef_app_browser.h"
#include "q_cef_app_render.h"
#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h"
#include "include/cef_app.h"

#include <QMetaType>

Q_DECLARE_METATYPE(CefRefPtr<CefBrowser>)
Q_DECLARE_METATYPE(CefRefPtr<CefFrame>)
Q_DECLARE_METATYPE(CefProcessId)
Q_DECLARE_METATYPE(CefRefPtr<CefProcessMessage>)

void registerCefMetaType();

const char *const kRenderToBrowserProcessMessage = "RenderToBrowserProcessMessage";
const char *const kBrowserToRenderProcessMessage = "BrowserToRenderProcessMessage";

int initializeCef();

void uninitializeCef();

#endif // QCEF_GLOBAL_DEFINE_H
