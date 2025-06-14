#ifndef QCEFCLIENT_H
#define QCEFCLIENT_H

#include <QObject>
#include <QVariant>
#include <list>
#include "include/cef_client.h"

class QCefClient :
    public QObject,
    public CefClient,
    public CefLifeSpanHandler,
    public CefKeyboardHandler,
    public CefRequestHandler
{
    Q_OBJECT

signals:
    void SignalAfterCreated(CefRefPtr<CefBrowser> browser);
    void SignalReceiveJsMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId process_id, CefRefPtr<CefProcessMessage> process_message);
    void SignalOnBeforeClose(CefRefPtr<CefBrowser> browser);

public:
    QCefClient();
    ~QCefClient();

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override 
    {
        return this;
    }
    CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override
    {
        return this;
    }
    virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefProcessId source_process,
        CefRefPtr<CefProcessMessage> message) override;
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        int popup_id,
        const CefString &target_url,
        const CefString &target_frame_name,
        CefLifeSpanHandler::WindowOpenDisposition target_disposition,
        bool user_gesture,
        const CefPopupFeatures &popupFeatures,
        CefWindowInfo &windowInfo,
        CefRefPtr<CefClient> &client,
        CefBrowserSettings &settings,
        CefRefPtr<CefDictionaryValue> &extra_info,
        bool *no_javascript_access) override;
    bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
        const CefKeyEvent &event,
        CefEventHandle os_event,
        bool *is_keyboard_shortcut) override;
private:
    IMPLEMENT_REFCOUNTING(QCefClient);
};

#endif  // QCEFCLIENT_H
