#ifndef GAMEIO_GAMEPAD_H
#define GAMEIO_GAMEPAD_H

#include <GameIO/global.h>

#include <QtCore/qobject.h>

#ifdef QT_GUI_LIB
#   include <QtGui/qcolor.h>
#endif

namespace GameIO {

class GamepadPrivate;
class GAMEIO_EXPORT Gamepad : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged FINAL)
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectionStateChanged FINAL)

public:
    explicit Gamepad(int id = 0, QObject *parent = nullptr);
    ~Gamepad();

    int id() const;
    Q_SLOT void setId(int id);
    Q_SIGNAL void idChanged(int id);

    QString name() const;
    Q_SIGNAL void nameChanged(const QString &name);

    bool isConnected() const;
    Q_SIGNAL void connected();
    Q_SIGNAL void disconnected();
    Q_SIGNAL void connectionStateChanged(bool connected);

#ifdef QT_GUI_LIB
    QColor ledColor() const
    { return QColor(ledRed(), ledGreen(), ledBlue()); }
    void setLedColor(const QColor &color)
    { setLedColor(color.red(), color.green(), color.blue()); }
#endif
    int ledRed() const;
    int ledGreen() const;
    int ledBlue() const;
    void setLedColor(int red, int green, int blue);

    Q_SLOT void vibrate();
    Q_SLOT void vibrate(float strength, int duration);

    bool buttonLeft() const;
    Q_SIGNAL void buttonLeftChanged(bool value);

    bool buttonRight() const;
    Q_SIGNAL void buttonRightChanged(bool value);

    bool buttonUp() const;
    Q_SIGNAL void buttonUpChanged(bool value);

    bool buttonDown() const;
    Q_SIGNAL void buttonDownChanged(bool value);

    bool buttonX() const;
    Q_SIGNAL void buttonXChanged(bool value);

    bool buttonY() const;
    Q_SIGNAL void buttonYChanged(bool value);

    bool buttonA() const;
    Q_SIGNAL void buttonAChanged(bool value);

    bool buttonB() const;
    Q_SIGNAL void buttonBChanged(bool value);

    bool buttonL1() const;
    Q_SIGNAL void buttonL1Changed(bool value);

    double buttonL2() const;
    Q_SIGNAL void buttonL2Changed(double value);

    bool buttonL3() const;
    Q_SIGNAL void buttonL3Changed(bool value);

    bool buttonR1() const;
    Q_SIGNAL void buttonR1Changed(bool value);

    double buttonR2() const;
    Q_SIGNAL void buttonR2Changed(double value);

    bool buttonR3() const;
    Q_SIGNAL void buttonR3Changed(bool value);

    bool buttonSelect() const;
    Q_SIGNAL void buttonSelectChanged(bool value);

    bool buttonStart() const;
    Q_SIGNAL void buttonStartChanged(bool value);

    bool buttonCenter() const;
    Q_SIGNAL void buttonCenterChanged(bool value);

    bool buttonGuide() const;
    Q_SIGNAL void buttonGuideChanged(bool value);

    double axisLeftX() const;
    Q_SIGNAL void axisLeftXChanged(double value);

    double axisLeftY() const;
    Q_SIGNAL void axisLeftYChanged(double value);

    double axisRightX() const;
    Q_SIGNAL void axisRightXChanged(double value);

    double axisRightY() const;
    Q_SIGNAL void axisRightYChanged(double value);

protected:
    Q_SLOT void processGamepadAdd(int id);
    Q_SLOT void processGamepadRemove(int id);
    Q_SLOT void processGamepadName(int id, const QString &name);
    Q_SLOT void processButtonPress(int id, int button, double value);
    Q_SLOT void processButtonRelease(int id, int button);
    Q_SLOT void processAxisMove(int id, int axis, double value);

    QScopedPointer<GamepadPrivate> d;

    friend class GamepadManager;
};

}

#endif // GAMEIO_GAMEPAD_H
