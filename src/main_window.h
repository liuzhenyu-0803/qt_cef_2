#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include "ui_main_window.h"

#include <QtWidgets/QWidget>


class QCefWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui_;

    QCefWidget *cef_widget_;
};


#endif // MAIN_WINDOW_H
