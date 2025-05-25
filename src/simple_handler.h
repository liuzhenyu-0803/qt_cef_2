#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_

#include <list>

#include "include/cef_client.h"

class SimpleHandler : public CefClient,
                      public CefDisplayHandler,
                      public CefLifeSpanHandler,
                      public CefLoadHandler
{
public:
  SimpleHandler();
  ~SimpleHandler() override;

  // 获取该对象的全局唯一实例。
  static SimpleHandler *GetInstance();

  // CefClient 方法：
  CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
  CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }

  // CefLifeSpanHandler 方法：
  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
  bool DoClose(CefRefPtr<CefBrowser> browser) override;
  void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

  // 预留方法
  void ShowMainWindow();

  // 预留方法
  void CloseAllBrowsers(bool force_close);

  // 预留方法

private:
  // 当前所有浏览器窗口列表，仅在 CEF UI 线程访问。
  typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
  BrowserList browser_list_;


  // 包含默认的引用计数实现。
  IMPLEMENT_REFCOUNTING(SimpleHandler);
};

#endif // CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
