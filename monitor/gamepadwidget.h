#ifndef GAMEPADWIDGET_H
#define GAMEPADWIDGET_H

#include <QWidget>

namespace Ui {
class GamepadWidget;
}

namespace GameIO {
class Gamepad;
}

class QLabel;
class QProgressBar;

class GamepadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GamepadWidget(QWidget *parent = nullptr);
    ~GamepadWidget();

    void setGamepad(GameIO::Gamepad *gamepad);

private:
    QPoint buttonPos(int button) const;
    QList<int> buttons() const;
    Q_SLOT void processButtonChange(int button, double pression);
    QLabel *buttonWidget(int button) const;

    QPoint axisPos(int axis) const;
    QList<int> axes() const;
    Q_SLOT void processAxisMove(int axis, double value);
    QLabel *axisPosWidget(int axis) const;
    QProgressBar *axisValueWidget(int axis) const;

    Ui::GamepadWidget *ui;

    QHash<int, QLabel *> m_buttons;
    QHash<int, QLabel *> m_axes;
};

#endif // GAMEPADWIDGET_H
