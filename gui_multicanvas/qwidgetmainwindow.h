#ifndef QWIDGETMAINWINDOW_H
#define QWIDGETMAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class QWidgetMainWIndow : public QMainWindow
{
    Q_OBJECT
public:
    explicit QWidgetMainWIndow(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // QWIDGETMAINWINDOW_H
