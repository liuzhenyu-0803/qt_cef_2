#include "q_cef_widget.h"

#include "../app.h"
#include "q_cef_client.h"
#include "q_cef_global_define.h"

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
    connect(App::getInstance(), SIGNAL(signal_before_quit()), this, SLOT(deleteLater()));
    createBrowser();
}
QCefWidget::~QCefWidget() {}
void QCefWidget::callJsFunction(const QString &func_name, const QString &func_param)
{
    if (m_cefBrowser)
    {
        if (auto frame = m_cefBrowser->GetMainFrame())
        {
            auto code = QString("callJsFunction('func_name: %1, func_param: %2');").arg(func_name).arg(func_param).toStdString();
            m_cefBrowser->GetMainFrame()->ExecuteJavaScript(code, frame->GetURL(), 0);
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
    adjustBrowserSize();
}
void QCefWidget::onBrowserAfterCreated(CefRefPtr<CefBrowser> browser)
{
    m_cefBrowser = browser;
    adjustBrowserSize();
}
void QCefWidget::onReceiveJsMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId process_id, CefRefPtr<CefProcessMessage> process_message)
{
    emit signalReceiveJsMessage(QString::fromStdString(process_message->GetName()), QString::fromStdString(process_message->GetArgumentList()->GetString(0).ToString()));
    QTimer::singleShot(0, [=] {
        QMessageBox::information(this, QString::fromStdString(process_message->GetName()), QString::fromStdString(process_message->GetArgumentList()->GetString(0).ToString()));
    });
}
void QCefWidget::createBrowser()
{
    CefWindowInfo window_info;
    window_info.SetAsChild((HWND)winId(), { 0, 0, (int)(width() * devicePixelRatioF()), (int)(height() * devicePixelRatioF()) });
    m_cefClient = new QCefClient(/*queryHandler nullptr*/);
    auto url = (QCoreApplication::applicationDirPath() + "/test.html").toStdString();
    CefBrowserSettings browser_settings;
    CefBrowserHost::CreateBrowser(window_info, m_cefClient, url, browser_settings, nullptr, nullptr);
    connect(m_cefClient.get(), &QCefClient::SignalAfterCreated, this, &QCefWidget::onBrowserAfterCreated);
    connect(m_cefClient.get(), &QCefClient::SignalReceiveJsMessage, this, &QCefWidget::onReceiveJsMessage);
}
void QCefWidget::adjustBrowserSize()
{
    if (m_cefBrowser)
    {
        ::MoveWindow(m_cefBrowser->GetHost()->GetWindowHandle(), 0, 0, (int)(width() * devicePixelRatioF()), (int)(height() * devicePixelRatioF()), true);
    }
}
