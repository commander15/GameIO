#include "gamepad.h"
#include "gamepad_p.h"

#include <GameIO/gamepadmanager.h>
#include <GameIO/private/gamepadmanager_p.h>

namespace GameIO {

/**
 * @class Gamepad
 * @brief Represents a single gamepad device with access to its buttons, axes, and features.
 *
 * Handles state, input events, and interaction with a connected game controller.
 */

/**
 * @brief Constructs a Gamepad instance with the given ID.
 * @param id The ID of the gamepad.
 * @param parent The parent QObject.
 */
Gamepad::Gamepad(int id, QObject *parent) :
    QObject(parent),
    d(new GamepadPrivate(this))
{
    setDeviceId(id);

    GamepadManagerPrivate *man = d->manager();
    connect(man, &GamepadManagerPrivate::gamepadAdded, this, &Gamepad::processGamepadAdd);
    connect(man, &GamepadManagerPrivate::gamepadRemoved, this, &Gamepad::processGamepadRemove);
    connect(man, &GamepadManagerPrivate::gamepadNamed, this, &Gamepad::processGamepadName);
    connect(man, &GamepadManagerPrivate::gamepadButtonPressed, this, &Gamepad::processButtonPress);
    connect(man, &GamepadManagerPrivate::gamepadButtonReleased, this, &Gamepad::processButtonRelease);
    connect(man, &GamepadManagerPrivate::gamepadAxisMoved, this, &Gamepad::processAxisMove);
}

/**
 * @brief Destructor.
 */
Gamepad::~Gamepad()
{
}

/**
 * @brief Gets the gamepad ID.
 * @return The ID.
 */
int Gamepad::deviceId() const
{
    return d->id;
}

/**
 * @brief Sets the gamepad ID and updates internal state.
 * @param id The new ID.
 */
void Gamepad::setDeviceId(int id)
{
    if (d->id == id)
        return;

    d->id = id;
    emit deviceIdChanged(id);

    GamepadManagerPrivate *man = d->manager();

    d->name = man->gamepadName(id);
    emit nameChanged(d->name);

    d->connected = man->isGamepadConnected(id);
    emit connectionStateChanged(d->connected);
}

/**
 * @brief Gets the gamepad name.
 * @return Name string.
 */
QString Gamepad::name() const
{
    return d->name;
}

/**
 * @brief Returns whether the gamepad is connected or not.
 * @return true if connected, false otherwise.
 */
bool Gamepad::isConnected() const
{
    return d->connected;
}

/**
 * @brief Gets the red component of the LED.
 * @return Red value (0-255).
 */
int Gamepad::ledRed() const
{
    return d->ledRed;
}

/**
 * @brief Gets the green component of the LED.
 * @return Green value (0-255).
 */
int Gamepad::ledGreen() const
{
    return d->ledGreen;
}

/**
 * @brief Gets the blue component of the LED.
 * @return Blue value (0-255).
 */
int Gamepad::ledBlue() const
{
    return d->ledBlue;
}

/**
 * @brief Sets the LED color.
 * @param red Red intensity.
 * @param green Green intensity.
 * @param blue Blue intensity.
 */
void Gamepad::setLedColor(int red, int green, int blue)
{
    if (SDL_JoystickSetLED(d->joystick(), red, green, blue) == 0) {
        d->ledRed = red;
        d->ledGreen = green;
        d->ledBlue = blue;
        emit ledColorChanged();
    }
}

/**
 * @brief Triggers vibration with given strength and duration.
 * @param strength Rumble strength (0.0 to 1.0).
 * @param duration Duration in milliseconds.
 */
void Gamepad::vibrate(float strength, int duration)
{
    SDL_HapticRumbleInit(d->haptic());
    SDL_HapticRumblePlay(d->haptic(), strength, duration);
}
/**
 * @brief Checks if the left directional button is pressed.
 * @return true if pressed, false otherwise.
 */

bool Gamepad::buttonLeft() const
{
    return d->buttons.value(ButtonLeft);
}

/**
 * @brief Checks if the right directional button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonRight() const
{
    return d->buttons.value(ButtonRight);
}

/**
 * @brief Checks if the up directional button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonUp() const
{
    return d->buttons.value(ButtonUp);
}

/**
 * @brief Checks if the down directional button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonDown() const
{
    return d->buttons.value(ButtonDown);
}

/**
 * @brief Checks if the cross (X) button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonX() const
{
    return d->buttons.value(ButtonX);
}

/**
 * @brief Checks if the cross (Y) button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonY() const
{
    return d->buttons.value(ButtonY);
}

/**
 * @brief Checks if the A button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonA() const
{
    return d->buttons.value(ButtonA);
}

/**
 * @brief Checks if the B button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonB() const
{
    return d->buttons.value(ButtonB);
}

/**
 * @brief Checks if the L1 button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonL1() const
{
    return d->buttons.value(ButtonL1);
}

/**
 * @brief Checks the L2 button presure level.
 * @note 0.0 means not pressed, 1.0 means fully pressed.
 * @return the presure level (0.0-1.0).
 */
double Gamepad::buttonL2() const
{
    return d->buttons.value(ButtonL2);
}

/**
 * @brief Checks if the L3 button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonL3() const
{
    return d->buttons.value(ButtonL3);
}

/**
 * @brief Checks if the R1 button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonR1() const
{
    return d->buttons.value(ButtonR1);
}

/**
 * @brief Checks the R2 button presure level.
 * @note 0.0 means not pressed, 1.0 means fully pressed.
 * @return the presure level (0.0-1.0).
 */
double Gamepad::buttonR2() const
{
    return d->buttons.value(ButtonR2);
}

/**
 * @brief Checks if the R3 button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonR3() const
{
    return d->buttons.value(ButtonR3);
}

/**
 * @brief Checks if the Select button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonSelect() const
{
    return d->buttons.value(ButtonSelect);
}

/**
 * @brief Checks if the Start button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonStart() const
{
    return d->buttons.value(ButtonStart);
}

/**
 * @brief Checks if the Center button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonCenter() const
{
    return d->buttons.value(ButtonCenter);
}

/**
 * @brief Checks if the Guide button is pressed.
 * @return true if pressed, false otherwise.
 */
bool Gamepad::buttonGuide() const
{
    return d->buttons.value(ButtonGuide);
}

/**
 * @brief Get left X axis value.
 * @return value in the range [-1.0, 1.0].
 */
double Gamepad::axisLeftX() const
{
    return d->axis.value(AxisLeftX);
}


/**
 * @brief Get left Y axis value.
 * @return value in the range [-1.0, 1.0].
 */
double Gamepad::axisLeftY() const
{
    return d->axis.value(AxisLeftY);
}


/**
 * @brief Get right X axis value.
 * @return value in the range [-1.0, 1.0].
 */
double Gamepad::axisRightX() const
{
    return d->axis.value(AxisRightX);
}


/**
 * @brief Get right Y axis value.
 * @return value in the range [-1.0, 1.0].
 */
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

    d->name = name;
    emit nameChanged(name);
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
