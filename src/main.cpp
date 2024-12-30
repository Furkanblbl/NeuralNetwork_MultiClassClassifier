#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QDebug>

#include "CoordinateSystem.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // QML engine
    QQmlApplicationEngine engine;

    // QML headef defines
    qmlRegisterType<CoordinateSystem>("CoordinateSystem", 1, 0, "CoordinateSystem");
    qDebug() << "Current working directory:" << QDir::currentPath();

    // QML module paths
    engine.addImportPath("qrc:/qmlmodules");
    engine.addImportPath(QDir::currentPath() + "/qmlmodules");
    engine.addImportPath(QDir::currentPath());

    const QUrl url(u"qrc:/NeuralNetwork/qml/MainWindow.qml"_qs);
    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        qDebug() << "Failed to load QML file";
        return -1;
    }

    return app.exec();
}
