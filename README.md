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

## 📄 License

GameIO is licensed under the MIT License.

---

## 👤 Author

Developed and maintained by **Amadou Wanie Benjamain**.

---

### Documentation

Live documentation available here https://commander15.github.io/GameIO-Doc/
