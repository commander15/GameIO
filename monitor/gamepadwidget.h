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

private slots:
    void changeColor();
    void vibrate();

    void processButtonChange(int button, double pression);
    void processAxisMove(int axis, double value);

private:
    QPoint buttonPos(int button) const;
    QList<int> buttons() const;
    QLabel *buttonWidget(int button) const;

    QPoint axisPos(int axis) const;
    QList<int> axes() const;
    QLabel *axisPosWidget(int axis) const;
    QProgressBar *axisValueWidget(int axis) const;

    Ui::GamepadWidget *ui;

    QHash<int, QLabel *> m_buttons;
    QHash<int, QLabel *> m_axes;

    GameIO::Gamepad *m_gamepad;
};

#endif // GAMEPADWIDGET_H
