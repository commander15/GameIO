#ifndef GAMEPADTEST_H
#define GAMEPADTEST_H

#include <gtest/gtest.h>

#include <GameIO/gamepad.h>

class GamepadTest : public testing::Test
{
public:
    GameIO::Gamepad gamepad;
};

#endif // GAMEPADTEST_H
