#include "gamepadmanager.h"
#include "gamepadmanager_p.h"

#include <QtCore/qsystemdetection.h>
#include <QtCore/qdebug.h>
#include <QtCore/qstandardpaths.h>
#include <QtCore/qdir.h>
#include <QtCore/qfile.h>

#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_haptic.h>

#ifdef Q_OS_LINUX
#   define MAPPING_FILE ":/gameio/configs/gamecontrollerdb_linux.txt"
#elif defined(Q_OS_WINDOWS)
#   define MAPPING_FILE ":/gameio/configs/gamecontrollerdb_windows.txt"
#endif

#define AXIS_DEAD_ZONE 10000.0

namespace GameIO {
/**
 * @class GamepadManager
 * @brief Centralized manager for handling gamepad devices.
 *
 * Manages connection states, input events, and device discovery for all connected game controllers.
 * Provides access to device information and real-time input data through a unified interface.
 */

GamepadManager::GamepadManager() :
    d(new GamepadManagerPrivate(this))
{
    d->init();
}

GamepadManager::~GamepadManager()
{
    d->cleanup();
}

/*!
 * @brief Get the gamepad name associated to the id.
 * @param id The gamepad id
 * @return the human readable name of the gamepad.
 */
QString GamepadManager::gamepadName(int id) const
{
    return d->gamepadName(id);
}

/**
 * @brief Checks whether a gamepad with the given device ID is currently connected.
 *
 * @param id The device ID of the gamepad to check.
 * @return true if the gamepad is connected; false otherwise.
 */
bool GamepadManager::isGamepadConnected(int id) const
{
    return d->isGamepadConnected(id);
}

/**
 * @brief Returns the list of device IDs for all currently connected gamepads.
 *
 * @return A QList of integers representing connected gamepad device IDs.
 */
QList<int> GamepadManager::connectedGamepads() const
{
    return d->m_instanceIdForIndex.keys();
}

/**
 * @brief Returns the singleton instance of the GamepadManager.
 *
 * If the instance does not exist yet, it will be created (RAII).
 *
 * @return Pointer to the GamepadManager singleton.
 */
GamepadManager *GamepadManager::instance()
{
    if (!self)
        self.reset(new GamepadManager());
    return self.data();
}

QScopedPointer<GamepadManager> GamepadManager::self;

GamepadManagerPrivate::GamepadManagerPrivate(GamepadManager *qq) :
    q(qq),
    m_subSystems(0x0)
{
    m_subSystems |= SDL_INIT_GAMECONTROLLER;
    m_subSystems |= SDL_INIT_JOYSTICK;
    m_subSystems |= SDL_INIT_HAPTIC;
}

QString GamepadManagerPrivate::gamepadName(int id) const
{
    SDL_GameController *controller = gamepadController(id);
    SDL_Joystick *joystick = SDL_GameControllerGetJoystick(controller);
    return joystick ? QString::fromUtf8(SDL_JoystickName(joystick)) : QString();
}

bool GamepadManagerPrivate::isGamepadConnected(int id) const
{
    return m_instanceIdForIndex.contains(id);
}

SDL_GameController *GamepadManagerPrivate::gamepadController(int id) const
{
    int index = m_instanceIdForIndex.value(id);
    return m_indexForController.value(index);
}

SDL_Joystick *GamepadManagerPrivate::gamepadJoystick(int id) const
{
    return SDL_GameControllerGetJoystick(gamepadController(id));
}

SDL_Haptic *GamepadManagerPrivate::gamepadHaptic(int id) const
{
    if (!m_haptics.contains(id)) {
        SDL_Haptic *haptic = SDL_HapticOpenFromJoystick(gamepadJoystick(id));
        if (haptic)
            m_haptics.insert(id, haptic);
        return haptic;
    } else
        return m_haptics.value(id);
}

void GamepadManagerPrivate::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    runLoop();
}

bool GamepadManagerPrivate::init()
{
    //Initialize SDL with necessary subsystems for gamepad support
    if (SDL_Init(m_subSystems)) {
        qDebug() << SDL_GetError();
        return false;
    }

#ifdef MAPPING_FILE
    QFile file(MAPPING_FILE);
    file.open(QIODevice::ReadOnly);

    while (!file.atEnd()) {
        QByteArray mapping = file.readLine();
        if (!mapping.isEmpty() && !mapping.startsWith('#'))
            SDL_GameControllerAddMapping(mapping.constData());
    }

    file.close();
#endif

    for (int i = 0; i < SDL_NumJoysticks() ; i++)
        addController(i);

    startTimer(100);

    return true;
}

void GamepadManagerPrivate::cleanup()
{
    SDL_QuitSubSystem(m_subSystems);
}

void GamepadManagerPrivate::runLoop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_CONTROLLERAXISMOTION) {
            SDL_ControllerAxisEvent axisEvent = event.caxis;
            //qDebug() << axisEvent.timestamp << "Axis Event: " << axisEvent.which << axisEvent.axis << axisEvent.value;
            double value = translateValue(axisEvent.value);
            switch (axisEvent.axis) {
            case SDL_CONTROLLER_AXIS_LEFTX:
                emit gamepadAxisMoved(m_instanceIdForIndex[axisEvent.which], AxisLeftX, value);
                break;
            case SDL_CONTROLLER_AXIS_LEFTY:
                emit gamepadAxisMoved(m_instanceIdForIndex[axisEvent.which], AxisLeftY, value);
                break;
            case SDL_CONTROLLER_AXIS_RIGHTX:
                emit gamepadAxisMoved(m_instanceIdForIndex[axisEvent.which], AxisRightX, value);
                break;
            case SDL_CONTROLLER_AXIS_RIGHTY:
                emit gamepadAxisMoved(m_instanceIdForIndex[axisEvent.which], AxisRightY, value);
                break;
            case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                if (value == 0.0)
                    emit gamepadButtonReleased(m_instanceIdForIndex[axisEvent.which], ButtonL2);
                else
                    emit gamepadButtonPressed(m_instanceIdForIndex[axisEvent.which], ButtonL2, value);
                break;
            case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                if (value == 0.0)
                    emit gamepadButtonReleased(m_instanceIdForIndex[axisEvent.which], ButtonR2);
                else
                    emit gamepadButtonPressed(m_instanceIdForIndex[axisEvent.which], ButtonR2, value);
                break;
            default:
                break;
            }

        } else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
            SDL_ControllerButtonEvent buttonEvent = event.cbutton;
            //qDebug() << buttonEvent.timestamp << "Button Press: " << buttonEvent.which << buttonEvent.button << buttonEvent.state;
            emit gamepadButtonPressed(m_instanceIdForIndex[buttonEvent.which], translateButton(buttonEvent.button), 1.0);
        } else if (event.type == SDL_CONTROLLERBUTTONUP) {
            SDL_ControllerButtonEvent buttonEvent = event.cbutton;
            //qDebug() << buttonEvent.timestamp << "Button Release: " << buttonEvent.which << buttonEvent.button << buttonEvent.state;
            emit gamepadButtonReleased(m_instanceIdForIndex[buttonEvent.which], translateButton(buttonEvent.button));
        } else if (event.type == SDL_CONTROLLERDEVICEADDED) {
            SDL_ControllerDeviceEvent deviceEvent = event.cdevice;
            //qDebug() << deviceEvent.timestamp << "Controller Added: " << deviceEvent.which;
            addController(deviceEvent.which);
        } else if (event.type == SDL_CONTROLLERDEVICEREMOVED) {
            SDL_ControllerDeviceEvent deviceEvent = event.cdevice;

            int index = m_instanceIdForIndex[deviceEvent.which];
            SDL_GameControllerClose(m_indexForController[index]);
            emit gamepadRemoved(index);
            m_indexForController.remove(index);
            m_instanceIdForIndex.remove(deviceEvent.which);

        } else if (event.type == SDL_CONTROLLERDEVICEREMAPPED) {
            //SDL_ControllerDeviceEvent deviceEvent = event.cdevice;
            //qDebug() << deviceEvent.timestamp << "Controller Remapped: " << deviceEvent.which;
        }
    }
}

void GamepadManagerPrivate::addController(int index)
{
    char GUID[100];
    SDL_JoystickGetGUIDString(SDL_JoystickGetDeviceGUID(index), GUID, 100);
    if (!SDL_IsGameController(index))
        return;

    SDL_GameController *controller = SDL_GameControllerOpen(index);
    if (controller) {
        m_indexForController.insert(index, controller);

        SDL_Joystick *joystick = SDL_GameControllerGetJoystick(controller);

        int instanceID = SDL_JoystickInstanceID(joystick);
        m_instanceIdForIndex.insert(instanceID, index);

        const char *name = SDL_JoystickName(joystick);

        //qDebug() << "Controller " << index << " added with instanceId: " << instanceID;
        emit gamepadAdded(index);

        if (name)
            emit gamepadNamed(index, QString::fromUtf8(name));
    }
}

int GamepadManagerPrivate::translateButton(Uint8 button)
{
    switch (button) {
    case SDL_CONTROLLER_BUTTON_A:
        return ButtonA;
    case SDL_CONTROLLER_BUTTON_B:
        return ButtonB;
    case SDL_CONTROLLER_BUTTON_X:
        return ButtonX;
    case SDL_CONTROLLER_BUTTON_Y:
        return ButtonY;
    case SDL_CONTROLLER_BUTTON_BACK:
        return ButtonSelect;
    case SDL_CONTROLLER_BUTTON_GUIDE:
        return ButtonGuide;
    case SDL_CONTROLLER_BUTTON_START:
        return ButtonStart;
    case SDL_CONTROLLER_BUTTON_LEFTSTICK:
        return ButtonL3;
    case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
        return ButtonR3;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
        return ButtonL1;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
        return ButtonR1;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
        return ButtonUp;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        return ButtonDown;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        return ButtonLeft;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        return ButtonRight;
    default:
        return ButtonInvalid;
    }
}

double GamepadManagerPrivate::translateValue(double value)
{
    if (value < AXIS_DEAD_ZONE * -1.0 || value > AXIS_DEAD_ZONE) {
        const double deadZone = AXIS_DEAD_ZONE * (value < 0.0 ? 1.0 : -1.0);
        const double max = (value < 0.0 ? 32768.0 : 32767.0);
        return (value + deadZone) / (max - AXIS_DEAD_ZONE);
    } else
        return 0.0;
}

}
