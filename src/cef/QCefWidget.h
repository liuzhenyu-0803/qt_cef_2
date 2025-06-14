#ifndef QT_QCEF_WIDGET_H
#define QT_QCEF_WIDGET_H

#include "cef/QCefAppBrowser.h"
#include "cef/QCefClient.h"
#include <QtWidgets/QWidget>

class QCefWidget : public QWidget
{
    Q_OBJECT
signals:
    void SignalReceiveJsMessage(QString func_name, QString func_param);
public:
    QCefWidget(QWidget *parent = nullptr);
    ~QCefWidget();
    void CallJsFunction(const QString &func_name, const QString &func_param);
protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private slots:
    void OnBrowserAfterCreated(CefRefPtr<CefBrowser> browser);
    void OnReceiveJsMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId process_id, CefRefPtr<CefProcessMessage> process_message);
private:
    void CreateBrowser();
    void AdjustBrowserSize();
private:
    CefRefPtr<CefBrowser> cef_browser_;
    CefRefPtr<QCefClient> cef_client_;
    QWidget *widget_;
};

#endif // QT_QCEF_WIDGET_H
