#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include "ui_main_window.h"

#include <QtWidgets/QWidget>


class CefViewWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindowClass ui_;

    CefViewWidget *cef_view_widget_;
};


#endif // MAIN_WINDOW_H
