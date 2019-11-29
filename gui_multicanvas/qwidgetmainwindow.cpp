#include "qwidgetmainwindow.h"
#include <QTextEdit>
#include <QPushButton>

#include <QDebug>

QWidgetMainWIndow::QWidgetMainWIndow(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit *center = new QTextEdit(this);
    center->setMinimumSize(200, 100);
    setCentralWidget(center);

    connect(center, &QTextEdit::textChanged, [=] {
       qDebug() << Q_FUNC_INFO << center->toPlainText();
    });
    QPushButton *button = new QPushButton(this);
    button->setText("Click me");
    button->move(button->width(), 10);
    connect(button, &QPushButton::clicked, [=] {
        qDebug() << Q_FUNC_INFO << "Button clicked";
        center->insertPlainText("Button clicked\n");
    });
}
