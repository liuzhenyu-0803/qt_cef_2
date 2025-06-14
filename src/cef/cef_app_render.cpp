#include "cef_app_render.h"

#include "log/log.h"
#include "cef_global_define.h"


const char *JS_CALL_NATIVE_FUNCTION_NAME = "callNativeFunction";


class V8HandlerImpl : public CefV8Handler
{
public:
    V8HandlerImpl(/*CefRefPtr<CefFrame> frame*/)
        //: frame_(frame)
    {}

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


ClientAppRender::ClientAppRender()
{
    log("RenderApp::RenderApp");
}

void ClientAppRender::OnWebKitInitialized()
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
        // Create the renderer-side router for query handling.
        CefMessageRouterConfig config;
        //���� ��Ⱦ���̲���Ϣ·�ɶ���
        m_message_router = CefMessageRouterRendererSide::Create(config);
    }
}

void ClientAppRender::OnBrowserCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDictionaryValue> extra_info)
{
    log("RenderApp::OnBrowserCreated");
}

void ClientAppRender::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    log("RenderApp::OnContextCreated");

    browser_ = browser;

    handler->SetBrowser(browser_);


    //auto window = context->GetGlobal();
    //auto call_bridge = CefV8Value::CreateObject(nullptr, nullptr);
    //CefRefPtr<CefV8Handler> handler = new V8HandlerImpl(frame);
    //CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction(k_js_call_native_function_name, handler);
    //call_bridge->SetValue(k_js_call_native_function_name, func, V8_PROPERTY_ATTRIBUTE_NONE);
    //window->SetValue("callBridge", call_bridge, V8_PROPERTY_ATTRIBUTE_NONE);


    // ���ͽ�����Ϣ����
    //auto msg = CefProcessMessage::Create(RENDER_TO_BROWSER_PROCESS_MESSAGE);
    //auto args = msg->GetArgumentList();
    //args->SetString(0, "i am a render process");
    //browser_->GetMainFrame()->SendProcessMessage(PID_BROWSER, msg);


    return;

    //  m_message_router->OnContextCreated(browser, frame, context);

    //  return;

    //  //CefRefPtr<CefV8Value> window = context->GetGlobal();
    //  //CefRefPtr<CefV8Value> appEnvObject = CefV8Value::CreateObject(nullptr, nullptr);
    //  //appEnvObject->SetValue("aaa", CefV8Value::CreateString("hellow"), V8_PROPERTY_ATTRIBUTE_READONLY);
    //  //window->SetValue("AAA", appEnvObject, V8_PROPERTY_ATTRIBUTE_NONE);


    //  //return;

    //  std::string file_content = R"(
          //var app;
    //      if(!app){
          //	app={};
          //	 (function(){
    //      app.nativeFunction=function(str){
    //          native function nativeFunction();//�������ط�����
    //          return nativeFunction(str); //ִ�б��ط���
    //      }
    //  })();
    //      }
    //  )";


    //  //// 3. Register app extension module
    //  //// JavaScript����ú���ʱ���ͻ�ȥͨ��CefRegisterExtensionע���CefV8Handler�б������
    //  //// �ҵ�"v8/app"��Ӧ��CefV8HandlerImpl���͵�������Execute����
    //  CefRefPtr<CefV8Handler> v8Handler = new AppNativeV8Handler();
    //  auto b = CefRegisterExtension("v8/app", file_content, v8Handler);

    //  //log(std::string("RenderApp::OnContextCreated: ") + (b ? "true" : "false"));

    //  return;
}

void ClientAppRender::OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    m_message_router->OnContextReleased(browser, frame, context);
}

bool ClientAppRender::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> process_message)
{
    log("RenderApp::OnProcessMessageReceived: " + process_message->GetName().ToString() + " " + process_message->GetArgumentList()->GetString(0).ToString());

    return true;

    //return m_message_router->OnProcessMessageReceived(browser, frame, source_process, message);


    //qDebug() << "�յ�����:" << source_process << "����Ϣ, ��Ϣ����:"
        //<< QString::fromStdString(message.get()->GetName());
    //return true;
}
