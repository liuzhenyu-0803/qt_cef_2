#include "QCefAppRender.h"
#include "log/log.h"
#include "QCefGlobalDefine.h"
#include "include/wrapper/cef_message_router.h"

const char *JS_CALL_NATIVE_FUNCTION_NAME = "callNativeFunction";

class V8HandlerImpl : public CefV8Handler
{
public:
    V8HandlerImpl() {}
    bool Execute(const CefString &name,
        CefRefPtr<CefV8Value> object,
        const CefV8ValueList &arguments,
        CefRefPtr<CefV8Value> &retval,
        CefString &exception) override
    {
        if (name == JS_CALL_NATIVE_FUNCTION_NAME)
        {
            auto params = arguments.at(0)->GetStringValue().ToString();
            auto msg = CefProcessMessage::Create(name);
            auto args = msg->GetArgumentList();
            args->SetString(0, params);
            browser_->GetMainFrame()->SendProcessMessage(PID_BROWSER, msg);
            retval = CefV8Value::CreateString("callNativeFunction sucess");
            return true;
        }
        return false;
    }
    void SetBrowser(CefRefPtr<CefBrowser> browser)
    {
        browser_ = browser;
    }
private:
    CefRefPtr<CefBrowser> browser_;
    IMPLEMENT_REFCOUNTING(V8HandlerImpl);
};

CefRefPtr<V8HandlerImpl> handler;

QCefAppRender::QCefAppRender()
{
    log("RenderApp::RenderApp");
}

void QCefAppRender::OnWebKitInitialized()
{
    log("RenderApp::OnWebKitInitialized");
    std::string extensionCode =
        "var callNativeBridge;"
        "if (!callNativeBridge)"
        "   callNativeBridge = {};"
        "(function() {"
        "   callNativeBridge.callNativeFunction = function(text) {"
        "       native function callNativeFunction();"
        "       return callNativeFunction(text);"
        "   };"
        "})();";
    handler = new V8HandlerImpl();
    CefRegisterExtension("v8/myextension", extensionCode, handler);
    return;
    if (m_message_router == NULL) {
        CefMessageRouterConfig config;
        m_message_router = CefMessageRouterRendererSide::Create(config);
    }
}

void QCefAppRender::OnBrowserCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDictionaryValue> extra_info)
{
    log("RenderApp::OnBrowserCreated");
}

void QCefAppRender::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    log("RenderApp::OnContextCreated");
    browser_ = browser;
    handler->SetBrowser(browser_);
    return;
}

void QCefAppRender::OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    m_message_router->OnContextReleased(browser, frame, context);
}

bool QCefAppRender::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> process_message)
{
    log("RenderApp::OnProcessMessageReceived: " + process_message->GetName().ToString() + " " + process_message->GetArgumentList()->GetString(0).ToString());
    return true;
}
