#ifndef GAMEIO_GAMEPAD_P_H
#define GAMEIO_GAMEPAD_P_H

#include <GameIO/gamepad.h>

#include <QtCore/qhash.h>

namespace GameIO {

class GamepadPrivate
{
public:
    GamepadPrivate(Gamepad *qq);

    Gamepad *q;

    int id;
    QString name;
    bool connected;

    QHash<int, double> buttons;
    QHash<int, double> axis;
};

}

#endif // GAMEIO_GAMEPAD_P_H
