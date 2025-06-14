#include "QCefWidget.h"
#include "app.h"
#include "QCefClient.h"
#include "QCefGlobalDefine.h"
#include <QVBoxLayout>
#include <QWindow>
#include <QApplication>
#include <QMessageBox>
#include <QWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QPainter>
#include <QTimer>
#include <QLabel>

QCefWidget::QCefWidget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    connect(App::GetInstance(), &App::SignalBeforeQuit, this, [=] {
        delete this;
    });
    CreateBrowser();
}
QCefWidget::~QCefWidget() {}
void QCefWidget::CallJsFunction(const QString &func_name, const QString &func_param)
{
    if (cef_browser_)
    {
        if (auto frame = cef_browser_->GetMainFrame())
        {
            auto code = QString("callJsFunction('func_name: %1, func_param: %2');").arg(func_name).arg(func_param).toStdString();
            cef_browser_->GetMainFrame()->ExecuteJavaScript(code, frame->GetURL(), 0);
        }
    }
}
void QCefWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawRect(rect());
}
void QCefWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    AdjustBrowserSize();
}
void QCefWidget::OnBrowserAfterCreated(CefRefPtr<CefBrowser> browser)
{
    cef_browser_ = browser;
    AdjustBrowserSize();
}
void QCefWidget::OnReceiveJsMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId process_id, CefRefPtr<CefProcessMessage> process_message)
{
    emit SignalReceiveJsMessage(QString::fromStdString(process_message->GetName()), QString::fromStdString(process_message->GetArgumentList()->GetString(0).ToString()));
    QTimer::singleShot(0, [=] {
        QMessageBox::information(this, QString::fromStdString(process_message->GetName()), QString::fromStdString(process_message->GetArgumentList()->GetString(0).ToString()));
    });
}
void QCefWidget::CreateBrowser()
{
    CefWindowInfo window_info;
    window_info.SetAsChild((HWND)winId(), { 0, 0, (int)(width() * devicePixelRatioF()), (int)(height() * devicePixelRatioF()) });
    cef_client_ = new QCefClient(/*queryHandler nullptr*/);
    auto url = (QCoreApplication::applicationDirPath() + "/test.html").toStdString();
    CefBrowserSettings browser_settings;
    CefBrowserHost::CreateBrowser(window_info, cef_client_, url, browser_settings, nullptr, nullptr);
    connect(cef_client_.get(), &QCefClient::SignalAfterCreated, this, &QCefWidget::OnBrowserAfterCreated);
    connect(cef_client_.get(), &QCefClient::SignalReceiveJsMessage, this, &QCefWidget::OnReceiveJsMessage);
}
void QCefWidget::AdjustBrowserSize()
{
    if (cef_browser_)
    {
        ::MoveWindow(cef_browser_->GetHost()->GetWindowHandle(), 0, 0, (int)(width() * devicePixelRatioF()), (int)(height() * devicePixelRatioF()), true);
    }
}
