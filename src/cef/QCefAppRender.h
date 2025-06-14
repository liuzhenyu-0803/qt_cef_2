#ifndef QCEFAPPRENDER_H_
#define QCEFAPPRENDER_H_

#include "QCefApp.h"
#include "include/wrapper/cef_message_router.h"

class QCefAppRender : public QCefApp, public CefRenderProcessHandler 
{
public:
    QCefAppRender();

	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override 
	{
		return this;
	}

	void OnWebKitInitialized() override;

	void OnBrowserCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDictionaryValue> extra_info) override;

	void OnContextCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context) override;

	void OnContextReleased(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context) override;

	bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message);

private:
	CefRefPtr<CefBrowser> browser_;

	CefRefPtr<CefMessageRouterRendererSide> m_message_router;

    IMPLEMENT_REFCOUNTING(QCefAppRender);
};

#endif  // QCEFAPPRENDER_H_
