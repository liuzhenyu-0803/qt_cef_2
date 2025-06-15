#include "main_window.h"

#include "cef/q_cef_widget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    ui_.setupUi(this);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    cef_widget_ = new QCefWidget(this);
    layout->addWidget(cef_widget_);

    auto call_js_function_button = new QPushButton("call js function", this);
    layout->addWidget(call_js_function_button);

    auto delete_cef_view_button = new QPushButton("delete cef view", this);
    layout->addWidget(delete_cef_view_button);

    connect(call_js_function_button, &QPushButton::clicked, [=]() {
        cef_widget_->callJsFunction("test", "Hello from C++");
    });

    connect(delete_cef_view_button, &QPushButton::clicked, [=]() {
        cef_widget_->deleteLater();
    });
}

MainWindow::~MainWindow()
{

}
