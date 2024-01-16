#ifndef GAMEIO_GAMEPADMANAGER_P_H
#define GAMEIO_GAMEPADMANAGER_P_H

#include <GameIO/gamepadmanager.h>

#include <QtCore/qhash.h>

#include <SDL2/SDL.h>

namespace GameIO {

class GamepadManagerPrivate : public QObject
{
    Q_OBJECT

public:
    GamepadManagerPrivate(GamepadManager *qq);

    GamepadManager *q;

    QString gamepadName(int id) const;
    bool isGamepadConnected(int id) const;
    SDL_GameController *gamepadController(int id) const;
    SDL_Joystick *gamepadJoystick(int id) const;

    Q_SIGNAL void gamepadAdded(int id);
    Q_SIGNAL void gamepadRemoved(int id);
    Q_SIGNAL void gamepadNamed(int id, const QString &name);
    Q_SIGNAL void gamepadButtonPressed(int id, int button, double value);
    Q_SIGNAL void gamepadButtonReleased(int id, int button);
    Q_SIGNAL void gamepadAxisMoved(int id, int button, double value);


protected:
    void timerEvent(QTimerEvent *event) override;

private:
    bool init();
    void cleanup();
    void runLoop();

    void addController(int id);
    static int translateButton(Uint8 button);
    static double translateValue(double value);

    QHash<int, SDL_GameController *> m_indexForController;
    QHash<int, int> m_instanceIdForIndex;

    friend class GamepadManager;
};

}

#endif // GAMEIO_GAMEPADMANAGER_P_H
