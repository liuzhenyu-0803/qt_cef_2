#include "simple_handler.h"

#include <sstream>
#include <string>

#include "include/base/cef_callback.h"
#include "include/cef_app.h"
#include "include/cef_parser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

namespace
{

  SimpleHandler *g_instance = nullptr;

  /*
   * 将指定内容和 MIME 类型编码为 data: URI 格式（data:xxx;base64,...），
   * 可用于浏览器直接加载内嵌数据（如本地 HTML 错误页等）。
   */
  std::string GetDataURI(const std::string &data, const std::string &mime_type)
  {
    return "data:" + mime_type + ";base64," +
           CefURIEncode(CefBase64Encode(data.data(), data.size()), false)
               .ToString();
  }

}

SimpleHandler::SimpleHandler()
{
  DCHECK(!g_instance);
  g_instance = this;
}

SimpleHandler::~SimpleHandler()
{
  g_instance = nullptr;
}

/*
 * 获取全局唯一实例
 */
SimpleHandler *SimpleHandler::GetInstance()
{
  return g_instance;
}

void SimpleHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
  CEF_REQUIRE_UI_THREAD();

  browser_list_.push_back(browser);
}

bool SimpleHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
  CEF_REQUIRE_UI_THREAD();

  // 如果只剩下一个浏览器窗口（主窗口），需要特殊处理，设置标志允许关闭。
  if (browser_list_.size() == 1)
  {
    // 设置标志，允许主窗口关闭。
    // is_closing_ = true; // 已移除 is_closing_ 相关逻辑
  }

  // 返回 false 表示允许关闭窗口。对于窗口浏览器，这会触发操作系统的关闭事件。
  return false;
}

void SimpleHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
  CEF_REQUIRE_UI_THREAD();

  // 从当前浏览器列表中移除。
  BrowserList::iterator bit = browser_list_.begin();
  for (; bit != browser_list_.end(); ++bit)
  {
    if ((*bit)->IsSame(browser))
    {
      browser_list_.erase(bit);
      break;
    }
  }

  if (browser_list_.empty())
  {
    // 所有浏览器窗口已关闭，退出应用消息循环。
    CefQuitMessageLoop();
  }
}

void SimpleHandler::ShowMainWindow()
{
  if (!CefCurrentlyOn(TID_UI))
  {
    // 在 UI 线程执行。
    CefPostTask(TID_UI, base::BindOnce(&SimpleHandler::ShowMainWindow, this));
    return;
  }

  if (browser_list_.empty())
  {
    return;
  }

  auto main_browser = browser_list_.front();

  // 显示主窗口
  if (auto browser_view = CefBrowserView::GetForBrowser(main_browser))
  {
    // 使用 Views 框架显示窗口（如有需要可扩展为平台相关实现）。
    if (auto window = browser_view->GetWindow())
    {
      window->Show();
    }
  }
}

void SimpleHandler::CloseAllBrowsers(bool force_close)
{
  if (!CefCurrentlyOn(TID_UI))
  {
    // 在 UI 线程执行。
    CefPostTask(TID_UI, base::BindOnce(&SimpleHandler::CloseAllBrowsers, this,
                                       force_close));
    return;
  }

  if (browser_list_.empty())
  {
    return;
  }

  BrowserList::const_iterator it = browser_list_.begin();
  for (; it != browser_list_.end(); ++it)
  {
    (*it)->GetHost()->CloseBrowser(force_close);
  }
}
