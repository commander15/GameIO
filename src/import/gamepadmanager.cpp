#include "gamepadmanager.h"

#define GMAN GameIO::GamepadManager::instance()

GamepadManager::GamepadManager(QObject *parent)
    : QObject(parent)
{
    connect(GMAN, &GameIO::GamepadManager::connectedGamepadsChanged, this, &GamepadManager::connectedGamepadsChanged);
}

QList<int> GamepadManager::connectedGamepads() const
{
    return GMAN->connectedGamepads();
}
