#ifndef QCEFAPPBROWSER_H
#define QCEFAPPBROWSER_H

#include "QCefApp.h"
#include <QObject>

class QCefAppBrowser : 
    public QObject, 
    public QCefApp
{
    Q_OBJECT

public:
    QCefAppBrowser();
    ~QCefAppBrowser();

private:
    IMPLEMENT_REFCOUNTING(QCefAppBrowser);
};

#endif // QCEFAPPBROWSER_H
