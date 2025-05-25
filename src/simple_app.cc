/*
 * 版权所有 (c) 2013 Chromium Embedded Framework 作者。
 * 保留所有权利。此源代码的使用遵循 BSD 风格许可证，详见 LICENSE 文件。
 */

#include "simple_app.h"

#include <string>

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "simple_handler.h"

SimpleApp::SimpleApp() = default;

void SimpleApp::OnContextInitialized()
{
    CEF_REQUIRE_UI_THREAD();

    CefWindowInfo window_info;
#if defined(OS_WIN)
    window_info.SetAsPopup(nullptr, "cefsimple");
#endif
    window_info.runtime_style = CEF_RUNTIME_STYLE_DEFAULT;

    CefRefPtr<SimpleHandler> handler(new SimpleHandler());

    std::string url = "https://www.google.com";
    
    CefBrowserSettings browser_settings;

    // 创建第一个浏览器窗口。
    CefBrowserHost::CreateBrowser(window_info, handler, url, browser_settings,
                                  nullptr, nullptr);
}

CefRefPtr<CefClient> SimpleApp::GetDefaultClient()
{
    // 通过 Chrome 风格 UI 创建新浏览器窗口时调用。
    return SimpleHandler::GetInstance();
}
