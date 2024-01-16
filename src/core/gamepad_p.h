#ifndef GAMEIO_GAMEPAD_P_H
#define GAMEIO_GAMEPAD_P_H

#include <GameIO/gamepad.h>

#include <QtCore/qhash.h>

#include <SDL2/SDL_gamecontroller.h>

namespace GameIO {
class GamepadManagerPrivate;

class GamepadPrivate
{
public:
    GamepadPrivate(Gamepad *qq);

    SDL_GameController *controller() const;
    SDL_Joystick *joystick() const;

    GamepadManagerPrivate *manager() const;

    Gamepad *q;

    int id;
    QString name;
    bool connected;

    int ledRed;
    int ledGreen;
    int ledBlue;

    QHash<int, double> buttons;
    QHash<int, double> axis;
};

}

#endif // GAMEIO_GAMEPAD_P_H
