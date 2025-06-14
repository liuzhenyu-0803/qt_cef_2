#ifndef APP_H
#define APP_H


#include <QApplication>


class App : public QApplication
{
    Q_OBJECT

signals:
    void signal_before_quit();

public:
    App(int &argc, char **argv);
    ~App();

    static App *getInstance()
    {
        return qobject_cast<App *>(qApp);
    }

    void quit();

protected:
    

private:
    
};


#endif // APP_H
