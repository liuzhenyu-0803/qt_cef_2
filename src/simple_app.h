#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include "include/cef_app.h"

/*
 * 为浏览器进程实现应用级回调。
 */
class SimpleApp : public CefApp, public CefBrowserProcessHandler
{
public:
  SimpleApp();

  // CefApp methods:
  CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override
  {
    return this;
  }

  // CefBrowserProcessHandler methods:
  void OnContextInitialized() override;
  CefRefPtr<CefClient> GetDefaultClient() override;

private:
  // 包含默认的引用计数实现。
  IMPLEMENT_REFCOUNTING(SimpleApp);
};

#endif // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
