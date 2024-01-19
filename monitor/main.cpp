#include <QtWidgets/qapplication.h>

#include <GameIO/gamepadmanager.h>

#include "gamepadwidget.h"
#include "gamepadlogger.h"

int gamepadId();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GamepadWidget win;
    win.show();

    GamepadLogger gamepad(gamepadId());

    win.setGamepad(&gamepad);
    //QObject::connect(&gamepad, &GameIO::Gamepad::disconnected, &app, &QCoreApplication::quit);

    return app.exec();
}

int gamepadId()
{
    QList<int> ids = GameIO::GamepadManager::instance()->connectedGamepads();
    return (!ids.isEmpty() ? ids.constFirst() : -1);
}
