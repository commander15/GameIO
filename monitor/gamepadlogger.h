#ifndef GAMEPADLOGGER_H
#define GAMEPADLOGGER_H

#include <GameIO/gamepad.h>

#include <QtCore/qtextstream.h>

class GamepadLogger : public GameIO::Gamepad
{
    Q_OBJECT

public:
    GamepadLogger(int id);
    virtual ~GamepadLogger();

protected:
    virtual void logButtonChange(int button, double pression);
    virtual void logAxisMove(int axis, double value);

private:
    static QString buttonName(int button);
    static QString axisName(int axis);

    QTextStream stream;
};

#endif // GAMEPADLOGGER_H
