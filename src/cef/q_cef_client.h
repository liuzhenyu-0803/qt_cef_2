#ifndef QCEFCLIENT_H
#define QCEFCLIENT_H

#include "include/cef_client.h"

#include <QObject>

class QCefClient : public QObject,
                   public CefClient,
                   public CefLifeSpanHandler,
                   public CefKeyboardHandler,
                   public CefRequestHandler
{
    Q_OBJECT

signals:
    void signalAfterCreated(CefRefPtr<CefBrowser> browser);

    void signalJsMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId process_id, CefRefPtr<CefProcessMessage> process_message);

public:
    QCefClient()
    {

    }

    ~QCefClient()
    {
        
    }

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override
    {
        return this;
    }

    CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override
    {
        return this;
    }

    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                          CefRefPtr<CefFrame> frame,
                                          CefProcessId source_process,
                                          CefRefPtr<CefProcessMessage> message) override
    {
        emit signalJsMessageReceived(browser, frame, source_process, message);
        return true;
    }

    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override
    {
        emit signalAfterCreated(browser);
    }

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
                       bool *no_javascript_access) override
    {
        return true;
    }

private:
    IMPLEMENT_REFCOUNTING(QCefClient);
};

#endif // QCEFCLIENT_H
