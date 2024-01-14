#include "gamepadlogger.h"

#include <GameIO/gamepadmanager.h>

GamepadLogger::GamepadLogger(int id) :
    GameIO::Gamepad(id),
    stream(stdout)
{
    connect(this, &GameIO::Gamepad::buttonLeftChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonLeft, value);});
    connect(this, &GameIO::Gamepad::buttonRightChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonRight, value);});
    connect(this, &GameIO::Gamepad::buttonUpChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonUp, value);});
    connect(this, &GameIO::Gamepad::buttonDownChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonDown, value);});
    connect(this, &GameIO::Gamepad::buttonXChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonX, value);});
    connect(this, &GameIO::Gamepad::buttonYChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonY, value);});
    connect(this, &GameIO::Gamepad::buttonAChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonA, value);});
    connect(this, &GameIO::Gamepad::buttonBChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonB, value);});
    connect(this, &GameIO::Gamepad::buttonL1Changed, this, [=](bool value) {logButtonChange(GameIO::ButtonL1, value);});
    connect(this, &GameIO::Gamepad::buttonL2Changed, this, [=](bool value) {logButtonChange(GameIO::ButtonL2, value);});
    connect(this, &GameIO::Gamepad::buttonL3Changed, this, [=](double value) {logButtonChange(GameIO::ButtonL3, value);});
    connect(this, &GameIO::Gamepad::buttonR1Changed, this, [=](bool value) {logButtonChange(GameIO::ButtonR1, value);});
    connect(this, &GameIO::Gamepad::buttonR2Changed, this, [=](bool value) {logButtonChange(GameIO::ButtonR2, value);});
    connect(this, &GameIO::Gamepad::buttonR3Changed, this, [=](double value) {logButtonChange(GameIO::ButtonR3, value);});
    connect(this, &GameIO::Gamepad::buttonSelectChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonSelect, value);});
    connect(this, &GameIO::Gamepad::buttonStartChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonStart, value);});
    connect(this, &GameIO::Gamepad::buttonCenterChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonCenter, value);});
    connect(this, &GameIO::Gamepad::buttonGuideChanged, this, [=](bool value) {logButtonChange(GameIO::ButtonGuide, value);});
}

GamepadLogger::~GamepadLogger()
{
}

void GamepadLogger::logButtonChange(int button, double pression)
{
    stream << "Button " << buttonName(button) << ' ';
    if (pression > 0.0)
        stream << "pressed at " << pression;
    else
        stream << "released";
    stream << Qt::endl;
}

void GamepadLogger::logAxisMove(int axis, double value)
{
    stream << "Axis " << axisName(axis) << " moved to " << value << Qt::endl;
}

QString GamepadLogger::buttonName(int button)
{
    switch (button) {
    case GameIO::ButtonLeft:
        return QStringLiteral("Left");

    case GameIO::ButtonRight:
        return QStringLiteral("Right");

    case GameIO::ButtonUp:
        return QStringLiteral("Up");

    case GameIO::ButtonDown:
        return QStringLiteral("Down");

    case GameIO::ButtonX:
        return QStringLiteral("X");

    case GameIO::ButtonY:
        return QStringLiteral("Y");

    case GameIO::ButtonA:
        return QStringLiteral("A");

    case GameIO::ButtonB:
        return QStringLiteral("B");

    case GameIO::ButtonL1:
        return QStringLiteral("L1");

    case GameIO::ButtonL2:
        return QStringLiteral("L2");

    case GameIO::ButtonL3:
        return QStringLiteral("L3");

    case GameIO::ButtonR1:
        return QStringLiteral("R1");

    case GameIO::ButtonR2:
        return QStringLiteral("R2");

    case GameIO::ButtonR3:
        return QStringLiteral("R3");

    case GameIO::ButtonSelect:
        return QStringLiteral("Select");

    case GameIO::ButtonStart:
        return QStringLiteral("Start");

    case GameIO::ButtonCenter:
        return QStringLiteral("Center");

    case GameIO::ButtonGuide:
        return QStringLiteral("Guide");

    default:
        return QString();
    }
}

QString GamepadLogger::axisName(int axis)
{
    switch (axis) {
    case GameIO::AxisLeftX:
        return QStringLiteral("Left X");

    case GameIO::AxisLeftY:
        return QStringLiteral("Left Y");

    case GameIO::AxisRightX:
        return QStringLiteral("Right X");

    case GameIO::AxisRightY:
        return QStringLiteral("Right Y");

    default:
        return QString();
    }
}
