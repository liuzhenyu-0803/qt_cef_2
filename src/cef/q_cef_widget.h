#ifndef QT_QCEF_WIDGET_H
#define QT_QCEF_WIDGET_H

#include "cef/q_cef_app_browser.h"
#include "cef/q_cef_client.h"

#include <QtWidgets/QWidget>

class QCefWidget : public QWidget
{
    Q_OBJECT

signals:
    void signalReceiveJsMessage(QString func_name, QString func_param);

public:
    QCefWidget(QWidget *parent = nullptr);
    ~QCefWidget();

    void callJsFunction(const QString &func_name, const QString &func_param);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onBrowserAfterCreated(CefRefPtr<CefBrowser> browser);
    void onReceiveJsMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId process_id, CefRefPtr<CefProcessMessage> process_message);
private:
    void createBrowser();
    void adjustBrowserSize();
private:
    CefRefPtr<CefBrowser> m_cefBrowser;
    CefRefPtr<QCefClient> m_cefClient;
};

#endif // QT_QCEF_WIDGET_H
