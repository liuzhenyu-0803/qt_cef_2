#include "include/cef_command_line.h"
#include "simple_app.h"

/*
 * 所有进程的入口函数。
 */
int main(int &argc, char *argv[])
{
  // 向 CEF 提供命令行参数。
  HINSTANCE hInstance = GetModuleHandle(nullptr);
  CefMainArgs main_args(hInstance);

  // CEF 应用包含多个子进程（渲染、GPU 等），共用同一可执行文件。
  // 此函数检查命令行参数，如果是子进程则执行相应逻辑。
  int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
  if (exit_code >= 0)
  {
    // 子进程已完成，直接返回。
    return exit_code;
  }

  // 在此处指定 CEF 全局设置。
  CefSettings settings;
  settings.no_sandbox = true;

  // SimpleApp 实现了浏览器进程的应用级回调。
  // 在 CEF 初始化后，会在 OnContextInitialized() 中创建第一个浏览器实例。
  CefRefPtr<SimpleApp> app(new SimpleApp);

  // 初始化 CEF 浏览器进程。如果初始化失败或需要提前退出（如进程单例重启），则返回 false。
  if (!CefInitialize(main_args, settings, app.get(), nullptr))
  {
    return CefGetExitCode();
  }

  // 运行 CEF 消息循环，直到调用 CefQuitMessageLoop() 前会一直阻塞。
  CefRunMessageLoop();

  // 关闭 CEF。
  CefShutdown();

  return 0;
}
