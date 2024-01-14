#include <QtCore/qcoreapplication.h>

#include <GameIO/gamepadmanager.h>

#include "gamepadlogger.h"

int gamepadId();

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    GamepadLogger gamepad(gamepadId());
    //QObject::connect(&gamepad, &GameIO::Gamepad::disconnected, &app, &QCoreApplication::quit);

    return app.exec();
}

int gamepadId()
{
    QList<int> ids = GameIO::GamepadManager::instance()->connectedGamepads();
    return (!ids.isEmpty() ? ids.constFirst() : -1);
}
