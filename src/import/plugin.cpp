#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqmlengine.h>

#include <GameIO/gameio.h>

using namespace GameIO;

class GameIOQmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT

public:
    void registerTypes(const char *uri) override
    {
        // @uri GameIO
        int major = 2, minor = 0;

        qmlRegisterSingletonInstance(uri, major, minor, "GamepadManager", GamepadManager::instance());
        qmlRegisterType<Gamepad>(uri, major, minor, "Gamepad");
    }
};

#include "plugin.moc"
