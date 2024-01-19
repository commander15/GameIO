#include "gamepad.h"
#include "gamepad_p.h"

#include <GameIO/gamepadmanager.h>
#include <GameIO/private/gamepadmanager_p.h>

namespace GameIO {

Gamepad::Gamepad(int id, QObject *parent) :
    QObject(parent),
    d(new GamepadPrivate(this))
{
    setId(id);

    GamepadManagerPrivate *man = d->manager();
    connect(man, &GamepadManagerPrivate::gamepadAdded, this, &Gamepad::processGamepadAdd);
    connect(man, &GamepadManagerPrivate::gamepadRemoved, this, &Gamepad::processGamepadRemove);
    connect(man, &GamepadManagerPrivate::gamepadNamed, this, &Gamepad::processGamepadName);
    connect(man, &GamepadManagerPrivate::gamepadButtonPressed, this, &Gamepad::processButtonPress);
    connect(man, &GamepadManagerPrivate::gamepadButtonReleased, this, &Gamepad::processButtonRelease);
    connect(man, &GamepadManagerPrivate::gamepadAxisMoved, this, &Gamepad::processAxisMove);
}

Gamepad::~Gamepad()
{
}

int Gamepad::id() const
{
    return d->id;
}

void Gamepad::setId(int id)
{
    if (d->id == id)
        return;

    d->id = id;
    emit idChanged(id);
}

QString Gamepad::name() const
{
    return d->name;
}

bool Gamepad::isConnected() const
{
    return d->connected;
}

int Gamepad::ledRed() const
{
    return d->ledRed;
}

int Gamepad::ledGreen() const
{
    return d->ledGreen;
}

int Gamepad::ledBlue() const
{
    return d->ledBlue;
}

void Gamepad::setLedColor(int red, int green, int blue)
{
    if (SDL_JoystickSetLED(d->joystick(), red, green, blue)) {
        d->ledRed = red;
        d->ledGreen = green;
        d->ledBlue = blue;
    }
}

void Gamepad::vibrate()
{
    SDL_HapticRumbleInit(d->haptic());
    SDL_HapticRumblePlay(d->haptic(), 32, 64);
    return;
    SDL_HapticEffect effect;
    effect.type = SDL_HAPTIC_CONSTANT;
    effect.constant.type = SDL_HAPTIC_CONSTANT;
    effect.constant.direction.dir[0] = 9000;
    effect.constant.length = SDL_HAPTIC_INFINITY;

    int effectId = SDL_HapticNewEffect(d->haptic(), &effect);

    SDL_HapticRunEffect(d->haptic(), effectId, 1);
}

bool Gamepad::buttonLeft() const
{
    return d->buttons.value(ButtonLeft);
}

bool Gamepad::buttonRight() const
{
    return d->buttons.value(ButtonRight);
}

bool Gamepad::buttonUp() const
{
    return d->buttons.value(ButtonUp);
}

bool Gamepad::buttonDown() const
{
    return d->buttons.value(ButtonDown);
}

bool Gamepad::buttonX() const
{
    return d->buttons.value(ButtonX);
}

bool Gamepad::buttonY() const
{
    return d->buttons.value(ButtonY);
}

bool Gamepad::buttonA() const
{
    return d->buttons.value(ButtonA);
}

bool Gamepad::buttonB() const
{
    return d->buttons.value(ButtonB);
}

bool Gamepad::buttonL1() const
{
    return d->buttons.value(ButtonL1);
}

double Gamepad::buttonL2() const
{
    return d->buttons.value(ButtonL2);
}

bool Gamepad::buttonL3() const
{
    return d->buttons.value(ButtonL3);
}

bool Gamepad::buttonR1() const
{
    return d->buttons.value(ButtonR1);
}

double Gamepad::buttonR2() const
{
    return d->buttons.value(ButtonR2);
}

bool Gamepad::buttonR3() const
{
    return d->buttons.value(ButtonR3);
}

bool Gamepad::buttonSelect() const
{
    return d->buttons.value(ButtonSelect);
}

bool Gamepad::buttonStart() const
{
    return d->buttons.value(ButtonStart);
}

bool Gamepad::buttonCenter() const
{
    return d->buttons.value(ButtonCenter);
}

bool Gamepad::buttonGuide() const
{
    return d->buttons.value(ButtonGuide);
}

double Gamepad::axisLeftX() const
{
    return d->axis.value(AxisLeftX);
}

double Gamepad::axisLeftY() const
{
    return d->axis.value(AxisLeftY);
}

double Gamepad::axisRightX() const
{
    return d->axis.value(AxisRightX);
}

double Gamepad::axisRightY() const
{
    return d->axis.value(AxisRightY);
}

void Gamepad::processGamepadAdd(int id)
{
    if (d->id != id)
        return;

    if (!d->connected) {
        d->connected = true;
        emit connectionStateChanged(true);
        emit connected();
    }
}

void Gamepad::processGamepadRemove(int id)
{
    if (d->id != id)
        return;

    if (d->connected) {
        d->connected = false;
        emit connectionStateChanged(false);
        emit disconnected();
    }
}

void Gamepad::processGamepadName(int id, const QString &name)
{
    if (d->id != id)
        return;
}

void Gamepad::processButtonPress(int id, int button, double value)
{
    //if (d->id != id || (d->buttons.contains(button) && d->buttons.value(button) == value))
    //    return;

    //d->buttons.insert(button, value);

    switch (button) {
    case ButtonLeft:
        emit buttonLeftChanged(value);
        break;

    case ButtonRight:
        emit buttonRightChanged(value);
        break;

    case ButtonUp:
        emit buttonUpChanged(value);
        break;

    case ButtonDown:
        emit buttonDownChanged(value);
        break;

    case ButtonX:
        emit buttonXChanged(value);
        break;

    case ButtonY:
        emit buttonYChanged(value);
        break;

    case ButtonA:
        emit buttonAChanged(value);
        break;

    case ButtonB:
        emit buttonBChanged(value);
        break;

    case ButtonL1:
        emit buttonL1Changed(value);
        break;

    case ButtonL2:
        emit buttonL2Changed(value);
        break;

    case ButtonL3:
        emit buttonL3Changed(value);
        break;

    case ButtonR1:
        emit buttonR1Changed(value);
        break;

    case ButtonR2:
        emit buttonR2Changed(value);
        break;

    case ButtonR3:
        emit buttonR3Changed(value);
        break;

    case ButtonSelect:
        emit buttonSelectChanged(value);
        break;

    case ButtonStart:
        emit buttonStartChanged(value);
        break;

    case ButtonCenter:
        emit buttonCenterChanged(value);
        break;

    case ButtonGuide:
        emit buttonGuideChanged(value);
        break;

    default:
        break;
    }
}

void Gamepad::processButtonRelease(int id, int button)
{
    //if (d->id != id || (d->buttons.contains(button) && d->buttons.value(button) == 0.0))
    //    return;

    //d->buttons.insert(button, false);

    switch (button) {
    case ButtonLeft:
        emit buttonLeftChanged(0.0);
        break;

    case ButtonRight:
        emit buttonRightChanged(0.0);
        break;

    case ButtonUp:
        emit buttonUpChanged(0.0);
        break;

    case ButtonDown:
        emit buttonDownChanged(0.0);
        break;

    case ButtonX:
        emit buttonXChanged(0.0);
        break;

    case ButtonY:
        emit buttonYChanged(0.0);
        break;

    case ButtonA:
        emit buttonAChanged(0.0);
        break;

    case ButtonB:
        emit buttonBChanged(0.0);
        break;

    case ButtonL1:
        emit buttonL1Changed(0.0);
        break;

    case ButtonL2:
        emit buttonL2Changed(0.0);
        break;

    case ButtonL3:
        emit buttonL3Changed(0.0);
        break;

    case ButtonR1:
        emit buttonR1Changed(0.0);
        break;

    case ButtonR2:
        emit buttonR2Changed(0.0);
        break;

    case ButtonR3:
        emit buttonR3Changed(0.0);
        break;

    case ButtonSelect:
        emit buttonSelectChanged(0.0);
        break;

    case ButtonStart:
        emit buttonStartChanged(0.0);
        break;

    case ButtonCenter:
        emit buttonCenterChanged(0.0);
        break;

    case ButtonGuide:
        emit buttonGuideChanged(0.0);
        break;

    default:
        break;
    }
}

void Gamepad::processAxisMove(int id, int axis, double value)
{
    //if (d->id != id || d->axis.value(axis) == value)
    //    return;

    //d->axis.insert(axis, value);

    switch (axis) {
    case AxisLeftX:
        emit axisLeftXChanged(value);
        break;

    case AxisLeftY:
        emit axisLeftYChanged(value);
        break;

    case AxisRightX:
        emit axisRightXChanged(value);
        break;

    case AxisRightY:
        emit axisRightYChanged(value);
        break;

    default:
        break;
    }
}

GamepadPrivate::GamepadPrivate(Gamepad *qq) :
    q(qq),
    id(-1),
    connected(false),
    ledRed(0),
    ledGreen(0),
    ledBlue(0)
{
    buttons.insert(ButtonLeft, 0.0);
    buttons.insert(ButtonRight, 0.0);
    buttons.insert(ButtonUp, 0.0);
    buttons.insert(ButtonDown, 0.0);
    buttons.insert(ButtonX, 0.0);
    buttons.insert(ButtonY, 0.0);
    buttons.insert(ButtonA, 0.0);
    buttons.insert(ButtonB, 0.0);
    buttons.insert(ButtonL1, 0.0);
    buttons.insert(ButtonL2, 0.0);
    buttons.insert(ButtonL3, 0.0);
    buttons.insert(ButtonR1, 0.0);
    buttons.insert(ButtonR2, 0.0);
    buttons.insert(ButtonR3, 0.0);
    buttons.insert(ButtonSelect, 0.0);
    buttons.insert(ButtonStart, 0.0);
    buttons.insert(ButtonCenter, 0.0);
    buttons.insert(ButtonGuide, 0.0);

    axis.insert(AxisLeftX, 0.0);
    axis.insert(AxisLeftY, 0.0);
    axis.insert(AxisRightX, 0.0);
    axis.insert(AxisRightY, 0.0);
}

SDL_GameController *GamepadPrivate::controller() const
{
    return manager()->gamepadController(id);
}

SDL_Joystick *GamepadPrivate::joystick() const
{
    return manager()->gamepadJoystick(id);
}

SDL_Haptic *GamepadPrivate::haptic() const
{
    return manager()->gamepadHaptic(id);
}

GamepadManagerPrivate *GamepadPrivate::manager() const
{
    return GamepadManager::instance()->d.data();
}

}
