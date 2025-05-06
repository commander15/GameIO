#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <GameIO/gamepad.h>

#include <QQmlEngine>
#include <QColor>

class Gamepad : public GameIO::Gamepad
{
    QML_ELEMENT

    Q_OBJECT
    Q_PROPERTY(QColor ledColor READ ledColor WRITE setLedColor NOTIFY ledColorChanged FINAL)
    Q_PROPERTY(QQmlListProperty<QObject> children MEMBER m_childrenProperty)

    Q_CLASSINFO("DefaultProperty", "children")

public:
    explicit Gamepad(QObject *parent = nullptr);

    QColor ledColor() const;
    Q_SLOT void setLedColor(const QColor &color);

private:
    QList<QObject *> m_children;
    QQmlListProperty<QObject> m_childrenProperty;
};

#endif // GAMEPAD_H
