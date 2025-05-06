#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
#ifdef QML_IMPORT_PATH
    engine.addImportPath(QML_IMPORT_PATH);
#endif
    engine.loadFromModule("Ball", "App");

    return app.exec();
}
