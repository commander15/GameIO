Welcome to the **GameIO** documentation!

GameIO is a lightweight, cross-platform C++/Qt library built on top of **Qt 6** and **SDL 2**, designed to simplify gamepad input handling in Qt applications. It provides both a modern declarative QML interface and a robust C++ backend to support real-time access to buttons, axes, and device metadata.

---

## 🚀 Features

* Real-time gamepad input (buttons, axes)
* Built-in device discovery & hotplugging
* Gamepad led color change (tested on PlayStation gampepads)
* Vibration support though haptic feedbacks
* QML-friendly design for reactive UI
* Simultaneous multi-gamepad support
* Per-device polling for precision input
* Clean abstraction layer over SDL 2

---

## 📂 API

* **GamepadManager** – Manages all connected gamepads, IDs, and metadata.
* **Gamepad** – Represents a single gamepad instance, exposed to QML.

---

## 🛠️ Usage

### QML Example

```qml
import QtQuick 2.15
import QtQuick.Controls 2.15

import GameIO 2.0

ApplicationWindow {
    title: "Ball"
    width: 640
    height: 320
    visible: true

    Rectangle {
        id: ball
        
        function moveLeft(steps) {}        
        function moveRight(steps) {}        
        function moveUp(steps) {}        
        function moveDown(steps) {}
        function moveToCenter() {}
        
        color: "dark gray"
        radius: width / 2
        
        width: 64
        height: 64
    }

    Gamepad {
        id: gamepad

        readonly property int index: 0 // The first detected gamepad
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
```

### C++ Example

```cpp
#include <QGuiApplication>
#include <QTimer>

#include <GameIO/gameio.h>

using namespace GameIO;

void go();

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    // Needed, since GamepadManager need an event loop
    QTimer::singleShot(50, &app, &go);
    
    return app.exec();
}

void go()
{
    auto ids = GamepadManager::instance()->connectedGamepads();
    if (!ids.isEmpty()) {
        Gamepad *gamepad = new Gamepad(ids[0], qApp);
        // Now connect to signals, call vibrate or setLedColor
    }
}
```

---

## 📄 License

GameIO is licensed under the MIT License.

---

## 👤 Author

Developed and maintained by **Amadou Wanie Benjamain**.
