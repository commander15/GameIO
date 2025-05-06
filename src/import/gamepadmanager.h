#ifndef GAMEPADMANAGER_H
#define GAMEPADMANAGER_H

#include <GameIO/gamepadmanager.h>

#include <QQmlEngine>

class GamepadManager : public QObject
{
    QML_ELEMENT
    QML_SINGLETON

    Q_OBJECT
    Q_PROPERTY(QList<int> connectedGamepads READ connectedGamepads NOTIFY connectedGamepadsChanged FINAL)

public:
    explicit GamepadManager(QObject *parent = nullptr);

    QList<int> connectedGamepads() const;
    Q_SIGNAL void connectedGamepadsChanged();
};

#endif // GAMEPADMANAGER_H
