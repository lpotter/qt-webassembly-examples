#include <QtGui>
#include <QApplication>
#include <QDebug>
#ifdef HAVE_WIDGETS
#include <QtWidgets>
#endif

#include "hellowindow.h"
#include "rasterwindow.h"
#include "qwidgetmainwindow.h"

QWindow *createHelloOpenGLWindow()
{
    qDebug() << Q_FUNC_INFO << __LINE__;
    return new HelloWindow();
}

QWindow *createRasterWindow()
{
    qDebug() << Q_FUNC_INFO << __LINE__;
    return new RasterWindow();
}

#ifdef HAVE_WIDGETS
QWindow *createQWidgetMainWindow()
{
    qDebug() << Q_FUNC_INFO << __LINE__;
    QWidget* mainWindow = new QWidgetMainWIndow();
    mainWindow->winId();
    return mainWindow->windowHandle();
}
#endif

// select window content type
QWindow *createWindow(int screenAddress )
{
    qDebug() << Q_FUNC_INFO << screenAddress << (screenAddress% 16 );
    QWindow *window = /*(screenAddress% 16 == 0 ) ? createHelloOpenGLWindow() :*/ createQWidgetMainWindow();
    //QWindow *window = createHelloOpenGLWindow();
    //QWindow *window = createMaindow();
    //QWindow *window = createRasterWindow();
    return window;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Print info on initial screens
    qDebug() << "Screen count" << QGuiApplication::screens().size();
    int i = 0;
    for (QScreen *screen : QGuiApplication::screens()) {
        qDebug() << "Screen  " << i << screen->name();
        qDebug() << "Geometry" << screen->geometry();
        ++i;
    }

    // Verify that QWidnows can be constructed, even if there are
    // no screens.
    if (QGuiApplication::screens().size() == 0) {
        QWindow *dummy = createHelloOpenGLWindow();
        dummy->setScreen(nullptr);
    }

    // One window per screen
    QHash<QScreen *, QWindow *> windows;
    auto addScreenWindow = [&windows](QScreen *screen) {
        QWindow *window = createWindow(int(screen));
        window->setScreen(screen);
        window->showFullScreen();
        windows.insert(screen, window);
    };
    auto removeScreenWindow = [&windows](QScreen *screen) {
        delete windows.take(screen);
    };

    // Add windows for screens present at startup
    for (QScreen *screen : QGuiApplication::screens())
        addScreenWindow(screen);
    
    // Maintain windows as screens are added and removed
    QObject::connect(&app, &QGuiApplication::screenAdded, [=](QScreen *screen){
        addScreenWindow(screen);
    });
    QObject::connect(&app, &QGuiApplication::screenRemoved, [=](QScreen *screen){
        removeScreenWindow(screen);
    });

    return app.exec();
}
