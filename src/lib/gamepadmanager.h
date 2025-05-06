#ifndef GAMEIO_GAMEPADMANAGER_H
#define GAMEIO_GAMEPADMANAGER_H

#include <GameIO/global.h>

#include <QtCore/qobject.h>

namespace GameIO {

class GamepadManagerPrivate;
class GAMEIO_EXPORT GamepadManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<int> connectedGamepads READ connectedGamepads NOTIFY connectedGamepadsChanged FINAL)

public:
    Q_INVOKABLE QString gamepadName(int id) const;
    Q_INVOKABLE bool isGamepadConnected(int id) const;
    QList<int> connectedGamepads() const;

    static GamepadManager *instance();

signals:
    void connectedGamepadsChanged();

private:
    GamepadManager();
    ~GamepadManager();

    QScopedPointer<GamepadManagerPrivate> d;
    static QScopedPointer<GamepadManager> self;

    friend class GamepadPrivate;
};

enum GamepadButton {
    ButtonLeft,
    ButtonRight,
    ButtonUp,
    ButtonDown,
    ButtonX,
    ButtonY,
    ButtonA,
    ButtonB,
    ButtonL1,
    ButtonL2,
    ButtonL3,
    ButtonR1,
    ButtonR2,
    ButtonR3,
    ButtonSelect,
    ButtonStart,
    ButtonCenter,
    ButtonGuide,
    ButtonInvalid = -1
};

enum GamepadAxis {
    AxisLeftX,
    AxisLeftY,
    AxisRightX,
    AxisRightY,
    AxisInvalid = -1
};

} // namespace GameIO

#endif // GAMEIO_GAMEPADMANAGER_H
