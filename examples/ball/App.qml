import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import GameIO 2.0

ApplicationWindow {
    title: "Ball"
    width: 640
    height: 320
    visible: true

    ColumnLayout {
        id: appLayout

        focus: true
        anchors.fill: parent

        Keys.onSpacePressed: ball.moveToCenter()
        Keys.onLeftPressed: ball.moveLeft(1.0)
        Keys.onRightPressed: ball.moveRight(1.0)
        Keys.onUpPressed: ball.moveUp(1.0)
        Keys.onDownPressed: ball.moveDown(1.0)

        ComboBox {
            id: gamepadInput

            delegate: ItemDelegate {
                text: GamepadManager.deviceName(modelData)
                width: gamepadInput.width
            }

            model: GamepadManager.connectedGamepads

            Layout.fillWidth: true
        }

        Rectangle {
            id: canva
            color: gamepad.connected ? "white" : "dark gray"
            clip: true

            Layout.fillWidth: true
            Layout.fillHeight: true

            onWidthChanged: ball.moveToCenter()

            Ball {
                id: ball
                x: center.x
                y: center.y
            }
        }
    }

    Gamepad {
        id: gamepad

        readonly property int index: gamepadInput.currentIndex
        readonly property real pressInterval: 300

        deviceId: (index >= 0 ? GamepadManager.connectedGamepads[index] : 0)

        Timer {
            interval: gamepad.pressInterval
            repeat: true
            running: gamepad.connected

            onTriggered: function() {
                if (gamepad.buttonLeft)
                    ball.moveLeft(1.0);
                else if (gamepad.axisLeftX < 0.0)
                    ball.moveLeft(gamepad.axisLeftX * -1.0);
                else if (gamepad.buttonRight)
                    ball.moveRight(1.0);
                else if (gamepad.axisLeftX > 0.0)
                    ball.moveRight(gamepad.axisLeftX)
                else if (gamepad.buttonUp)
                    ball.moveUp(1.0);
                else if (gamepad.axisLeftY < 0.0)
                    ball.moveUp(gamepad.axisLeftY * -1.0);
                else if (gamepad.buttonDown)
                    ball.moveDown(1.0);
                else if (gamepad.axisLeftY > 0.0)
                    ball.moveDown(gamepad.axisLeftY);
                else if (gamepad.buttonA || gamepad.buttonL3)
                    ball.moveToCenter();
            }
        }
    }
}
