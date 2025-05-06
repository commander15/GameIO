#include "gamepad.h"

Gamepad::Gamepad(QObject *parent)
    : GameIO::Gamepad{0, parent}
    , m_childrenProperty(this, &m_children)
{
}

QColor Gamepad::ledColor() const
{
    return QColor(ledRed(), ledGreen(), ledBlue());
}

void Gamepad::setLedColor(const QColor &color)
{
    GameIO::Gamepad::setLedColor(color.red(), color.green(), color.blue());
}
