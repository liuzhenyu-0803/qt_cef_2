#ifndef QCEFAPP_H
#define QCEFAPP_H

#include "include/cef_app.h"

class QCefApp : public CefApp 
{
public:
    enum ProcessType 
    {
        BrowserProcess,
        RendererProcess,
        ZygoteProcess,
        OtherProcess,
    };

    static ProcessType GetProcessType(CefRefPtr<CefCommandLine> command_line);

    QCefApp();
    ~QCefApp();

private:
    DISALLOW_COPY_AND_ASSIGN(QCefApp);
};

#endif  // QCEFAPP_H
