#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQml>


#include "controller/controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Controller>("archi.monstre", 1, 0, "Controller");
    qmlRegisterType<ArchiList>("archi.monstre", 1, 0, "ArchiList");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

