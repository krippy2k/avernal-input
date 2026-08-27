#include <avernal/input/input.hpp>

#include <gtest/gtest.h>

TEST(Key, NamesAndValidity) {
    EXPECT_TRUE(avernal::is_valid(avernal::Key::up));
    EXPECT_FALSE(avernal::is_valid(avernal::Key::unknown));
    EXPECT_FALSE(avernal::is_valid(avernal::Key::count));
    EXPECT_EQ(avernal::key_name(avernal::Key::left), "left");
    EXPECT_EQ(avernal::key_name(avernal::Key::space), "space");
}

TEST(MouseButton, NamesAndValidity) {
    EXPECT_TRUE(avernal::is_valid(avernal::MouseButton::left));
    EXPECT_FALSE(avernal::is_valid(avernal::MouseButton::count));
    EXPECT_EQ(avernal::mouse_button_name(avernal::MouseButton::right), "right");
}

TEST(Input, KeyHeldAndEdges) {
    avernal::Input input;

    input.set_key(avernal::Key::up, true);
    EXPECT_TRUE(input.is_down(avernal::Key::up));
    EXPECT_TRUE(input.was_pressed(avernal::Key::up));
    EXPECT_FALSE(input.was_released(avernal::Key::up));

    input.begin_frame();
    EXPECT_TRUE(input.is_down(avernal::Key::up));
    EXPECT_FALSE(input.was_pressed(avernal::Key::up));

    input.set_key(avernal::Key::up, true);
    EXPECT_FALSE(input.was_pressed(avernal::Key::up));

    input.set_key(avernal::Key::up, false);
    EXPECT_FALSE(input.is_down(avernal::Key::up));
    EXPECT_TRUE(input.was_released(avernal::Key::up));
}

TEST(Input, IgnoresUnknownKeys) {
    avernal::Input input;
    input.set_key(avernal::Key::unknown, true);
    EXPECT_FALSE(input.is_down(avernal::Key::unknown));
    EXPECT_FALSE(input.was_pressed(avernal::Key::unknown));
}

TEST(Input, AxisFromHeldKeys) {
    avernal::Input input;
    EXPECT_EQ(input.axis(avernal::Key::left, avernal::Key::right), 0.0f);

    input.set_key(avernal::Key::right, true);
    EXPECT_EQ(input.axis(avernal::Key::left, avernal::Key::right), 1.0f);

    input.set_key(avernal::Key::left, true);
    EXPECT_EQ(input.axis(avernal::Key::left, avernal::Key::right), 0.0f);

    input.set_key(avernal::Key::right, false);
    EXPECT_EQ(input.axis(avernal::Key::left, avernal::Key::right), -1.0f);
}

TEST(Input, MouseButtonsAndWheel) {
    avernal::Input input;
    input.set_mouse_button(avernal::MouseButton::left, true);
    EXPECT_TRUE(input.is_down(avernal::MouseButton::left));
    EXPECT_TRUE(input.was_pressed(avernal::MouseButton::left));

    input.add_wheel_delta(1.5f);
    input.add_wheel_delta(-0.5f);
    EXPECT_FLOAT_EQ(input.wheel_delta(), 1.0f);

    input.begin_frame();
    EXPECT_TRUE(input.is_down(avernal::MouseButton::left));
    EXPECT_FALSE(input.was_pressed(avernal::MouseButton::left));
    EXPECT_FLOAT_EQ(input.wheel_delta(), 0.0f);
}

TEST(Input, MousePositionDelta) {
    avernal::Input input;
    input.set_mouse_position(10.0f, 20.0f);
    EXPECT_FLOAT_EQ(input.mouse_position().x, 10.0f);
    EXPECT_FLOAT_EQ(input.mouse_position().y, 20.0f);
    EXPECT_FLOAT_EQ(input.mouse_delta().x, 0.0f);

    input.set_mouse_position(13.0f, 16.0f);
    EXPECT_FLOAT_EQ(input.mouse_delta().x, 3.0f);
    EXPECT_FLOAT_EQ(input.mouse_delta().y, -4.0f);

    input.begin_frame();
    EXPECT_FLOAT_EQ(input.mouse_delta().x, 0.0f);
    input.add_mouse_delta(2.0f, 1.0f);
    EXPECT_FLOAT_EQ(input.mouse_delta().x, 2.0f);
}

TEST(Input, ReleaseAllClearsHeldState) {
    avernal::Input input;
    input.set_key(avernal::Key::space, true);
    input.set_mouse_button(avernal::MouseButton::right, true);

    input.begin_frame();
    input.release_all();

    EXPECT_FALSE(input.is_down(avernal::Key::space));
    EXPECT_TRUE(input.was_released(avernal::Key::space));
    EXPECT_FALSE(input.is_down(avernal::MouseButton::right));
    EXPECT_TRUE(input.was_released(avernal::MouseButton::right));
}

TEST(Input, ResetClearsEverything) {
    avernal::Input input;
    input.set_key(avernal::Key::a, true);
    input.set_mouse_position(5.0f, 6.0f);
    input.add_wheel_delta(2.0f);
    input.reset();

    EXPECT_FALSE(input.is_down(avernal::Key::a));
    EXPECT_FALSE(input.was_pressed(avernal::Key::a));
    EXPECT_FLOAT_EQ(input.mouse_position().x, 0.0f);
    EXPECT_FLOAT_EQ(input.wheel_delta(), 0.0f);
}
