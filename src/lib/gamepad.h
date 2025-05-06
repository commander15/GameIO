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
    Q_PROPERTY(int deviceId READ deviceId WRITE setDeviceId NOTIFY deviceIdChanged FINAL)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged FINAL)
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectionStateChanged FINAL)
    Q_PROPERTY(bool buttonLeft READ buttonLeft NOTIFY buttonLeftChanged FINAL)
    Q_PROPERTY(bool buttonRight READ buttonRight NOTIFY buttonRightChanged FINAL)
    Q_PROPERTY(bool buttonUp READ buttonUp NOTIFY buttonUpChanged FINAL)
    Q_PROPERTY(bool buttonDown READ buttonDown NOTIFY buttonDownChanged FINAL)
    Q_PROPERTY(bool buttonX READ buttonX NOTIFY buttonXChanged FINAL)
    Q_PROPERTY(bool buttonY READ buttonY NOTIFY buttonYChanged FINAL)
    Q_PROPERTY(bool buttonA READ buttonA NOTIFY buttonAChanged FINAL)
    Q_PROPERTY(bool buttonB READ buttonB NOTIFY buttonBChanged FINAL)
    Q_PROPERTY(bool buttonL1 READ buttonL1 NOTIFY buttonL1Changed FINAL)
    Q_PROPERTY(double buttonL2 READ buttonL2 NOTIFY buttonL2Changed FINAL)
    Q_PROPERTY(bool buttonL3 READ buttonL3 NOTIFY buttonL3Changed FINAL)
    Q_PROPERTY(bool buttonR1 READ buttonR1 NOTIFY buttonR1Changed FINAL)
    Q_PROPERTY(double buttonR2 READ buttonR2 NOTIFY buttonR2Changed FINAL)
    Q_PROPERTY(bool buttonR3 READ buttonR3 NOTIFY buttonR3Changed FINAL)
    Q_PROPERTY(bool buttonSelect READ buttonSelect NOTIFY buttonSelectChanged FINAL)
    Q_PROPERTY(bool buttonStart READ buttonStart NOTIFY buttonStartChanged FINAL)
    Q_PROPERTY(bool buttonCenter READ buttonCenter NOTIFY buttonCenterChanged FINAL)
    Q_PROPERTY(bool buttonGuide READ buttonGuide NOTIFY buttonGuideChanged FINAL)
    Q_PROPERTY(double axisLeftX READ axisLeftX NOTIFY axisLeftXChanged FINAL)
    Q_PROPERTY(double axisLeftY READ axisLeftY NOTIFY axisLeftYChanged FINAL)
    Q_PROPERTY(double axisRightX READ axisRightX NOTIFY axisRightXChanged FINAL)
    Q_PROPERTY(double axisRightY READ axisRightY NOTIFY axisRightYChanged FINAL)

public:
    Gamepad(int id = 0, QObject *parent = nullptr);
    ~Gamepad();

    int deviceId() const;
    Q_SLOT void setDeviceId(int id);
    Q_SIGNAL void deviceIdChanged(int id);

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
    Q_SIGNAL void ledColorChanged();

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
