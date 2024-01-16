#include "gamepadwidget.h"
#include "ui_gamepadwidget.h"

#include <GameIO/gamepad.h>
#include <GameIO/gamepadmanager.h>

GamepadWidget::GamepadWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GamepadWidget)
{
    ui->setupUi(this);

    ui->gamepadOutput->installEventFilter(this);

    QPixmap buttonIcon(":/icons/button.png");
    const QList<int> buttons = this->buttons();
    for (int button : buttons) {
        QLabel *label = new QLabel(ui->gamepadOutput);
        label->setPixmap(buttonIcon);
        label->move(buttonPos(button));
        label->hide();
        m_buttons.insert(button, label);
    }

    QPixmap axisIcon(":/icons/axis.png");
    const QList<int> axes = this->axes();
    for (int axis : axes) {
        QLabel *label = new QLabel(ui->gamepadOutput);
        label->setPixmap(axisIcon);
        label->move(axisPos(axis));
        label->hide();
        m_axes.insert(axis, label);
    }
}

GamepadWidget::~GamepadWidget()
{
    delete ui;
}

void GamepadWidget::setGamepad(GameIO::Gamepad *gamepad)
{
    setWindowTitle(gamepad->name());
    connect(gamepad, &GameIO::Gamepad::nameChanged, this, &QWidget::setWindowTitle);

    connect(gamepad, &GameIO::Gamepad::buttonLeftChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonLeft, value);});
    connect(gamepad, &GameIO::Gamepad::buttonRightChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonRight, value);});
    connect(gamepad, &GameIO::Gamepad::buttonUpChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonUp, value);});
    connect(gamepad, &GameIO::Gamepad::buttonDownChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonDown, value);});
    connect(gamepad, &GameIO::Gamepad::buttonXChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonX, value);});
    connect(gamepad, &GameIO::Gamepad::buttonYChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonY, value);});
    connect(gamepad, &GameIO::Gamepad::buttonAChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonA, value);});
    connect(gamepad, &GameIO::Gamepad::buttonBChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonB, value);});
    connect(gamepad, &GameIO::Gamepad::buttonL1Changed, this, [=](bool value) {processButtonChange(GameIO::ButtonL1, value);});
    connect(gamepad, &GameIO::Gamepad::buttonL2Changed, this, [=](bool value) {processButtonChange(GameIO::ButtonL2, value);});
    connect(gamepad, &GameIO::Gamepad::buttonL3Changed, this, [=](double value) {processButtonChange(GameIO::ButtonL3, value);});
    connect(gamepad, &GameIO::Gamepad::buttonR1Changed, this, [=](bool value) {processButtonChange(GameIO::ButtonR1, value);});
    connect(gamepad, &GameIO::Gamepad::buttonR2Changed, this, [=](bool value) {processButtonChange(GameIO::ButtonR2, value);});
    connect(gamepad, &GameIO::Gamepad::buttonR3Changed, this, [=](double value) {processButtonChange(GameIO::ButtonR3, value);});
    connect(gamepad, &GameIO::Gamepad::buttonSelectChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonSelect, value);});
    connect(gamepad, &GameIO::Gamepad::buttonStartChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonStart, value);});
    connect(gamepad, &GameIO::Gamepad::buttonCenterChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonCenter, value);});
    connect(gamepad, &GameIO::Gamepad::buttonGuideChanged, this, [=](bool value) {processButtonChange(GameIO::ButtonGuide, value);});
    connect(gamepad, &GameIO::Gamepad::axisLeftXChanged, this, [=](bool value) {processAxisMove(GameIO::AxisLeftX, value);});
    connect(gamepad, &GameIO::Gamepad::axisLeftYChanged, this, [=](bool value) {processAxisMove(GameIO::AxisLeftY, value);});
    connect(gamepad, &GameIO::Gamepad::axisRightXChanged, this, [=](bool value) {processAxisMove(GameIO::AxisRightX, value);});
    connect(gamepad, &GameIO::Gamepad::axisRightYChanged, this, [=](bool value) {processAxisMove(GameIO::AxisRightY, value);});
}

QPoint GamepadWidget::buttonPos(int button) const
{
    switch (button) {
    case GameIO::ButtonLeft:
        return QPoint(184, 305);

    case GameIO::ButtonRight:
        return QPoint(257, 306);

    case GameIO::ButtonUp:
        return QPoint(218, 275);

    case GameIO::ButtonDown:
        return QPoint(220, 332);

    case GameIO::ButtonX:
        return QPoint(474, 198);

    case GameIO::ButtonY:
        return QPoint(526, 241);

    case GameIO::ButtonA:
        return QPoint(531, 152);

    case GameIO::ButtonB:
        return QPoint(586, 193);

    case GameIO::ButtonL1:
        return QPoint(135, 60);

    case GameIO::ButtonL2:
        return QPoint(136, 20);

    case GameIO::ButtonL3:
        return QPoint(113, 220);

    case GameIO::ButtonR1:
        return QPoint(513, 62);

    case GameIO::ButtonR2:
        return QPoint(509, 22);

    case GameIO::ButtonR3:
        return QPoint(419, 321);

    case GameIO::ButtonSelect:
        return QPoint(249, 197);

    case GameIO::ButtonStart:
        return QPoint(397, 197);

    case GameIO::ButtonCenter:
        return QPoint(323, 195);

    case GameIO::ButtonGuide:
        return QPoint(321, 256);

    default:
        return QPoint();
    }
}

QList<int> GamepadWidget::buttons() const
{
    return QList<int>()
           << GameIO::ButtonLeft
           << GameIO::ButtonRight
           << GameIO::ButtonUp
           << GameIO::ButtonDown
           << GameIO::ButtonX
           << GameIO::ButtonY
           << GameIO::ButtonA
           << GameIO::ButtonB
           << GameIO::ButtonL1
           << GameIO::ButtonL2
           << GameIO::ButtonL3
           << GameIO::ButtonR1
           << GameIO::ButtonR2
           << GameIO::ButtonR3
           << GameIO::ButtonSelect
           << GameIO::ButtonStart
           << GameIO::ButtonCenter
           << GameIO::ButtonGuide;
}

void GamepadWidget::processButtonChange(int button, double pression)
{
    QWidget *w = buttonWidget(button);
    w->setVisible(pression == 1.0 ? true : false);

    switch (button) {
    case GameIO::ButtonL3:
        ui->l3Output->setValue(pression * 100);
        break;

    case GameIO::ButtonR3:
        ui->r3Output->setValue(pression * 100);
        break;

    default:
        break;
    }
}

QLabel *GamepadWidget::buttonWidget(int button) const
{
    return m_buttons.value(button);
}

QPoint GamepadWidget::axisPos(int axis) const
{
    switch (axis) {
    case GameIO::AxisLeftX:
    case GameIO::AxisLeftY:
        return buttonPos(GameIO::ButtonL3);

    case GameIO::AxisRightX:
    case GameIO::AxisRightY:
        return buttonPos(GameIO::ButtonR3);

    default:
        return QPoint();
    }
}

QList<int> GamepadWidget::axes() const
{
    return QList<int>()
           << GameIO::AxisLeftX
           << GameIO::AxisLeftY
           << GameIO::AxisRightX
           << GameIO::AxisRightY;
}

void GamepadWidget::processAxisMove(int axis, double value)
{
    axisPosWidget(axis)->setVisible(value == 0.0 ? false : true);

    if (value < 0.0)
        value += 0.5;
    else if (value > 0.0)
        value -= 0.5;

    axisValueWidget(axis)->setValue((value) * 100);
}

QLabel *GamepadWidget::axisPosWidget(int axis) const
{
    return m_axes.value(axis);
}

QProgressBar *GamepadWidget::axisValueWidget(int axis) const
{
    switch (axis) {
    case GameIO::AxisLeftX:
        return ui->axisLeftXOutput;

    case GameIO::AxisLeftY:
        return ui->axisLeftYOutput;

    case GameIO::AxisRightX:
        return ui->axisRightXOutput;

    case GameIO::AxisRightY:
        return ui->axisRightYOutput;

    default:
        return nullptr;
    }
}
