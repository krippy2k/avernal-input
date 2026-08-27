#pragma once

#include <avernal/input/keys.hpp>

#include <array>
#include <cstddef>

namespace avernal {

struct MousePosition {
    float x{};
    float y{};
};

class Input {
public:
    void begin_frame();
    void reset();
    void release_all();

    void set_key(Key key, bool down);
    void set_mouse_button(MouseButton button, bool down);
    void set_mouse_position(float x, float y);
    void add_mouse_delta(float dx, float dy);
    void add_wheel_delta(float delta);

    [[nodiscard]] bool is_down(Key key) const noexcept;
    [[nodiscard]] bool was_pressed(Key key) const noexcept;
    [[nodiscard]] bool was_released(Key key) const noexcept;

    [[nodiscard]] bool is_down(MouseButton button) const noexcept;
    [[nodiscard]] bool was_pressed(MouseButton button) const noexcept;
    [[nodiscard]] bool was_released(MouseButton button) const noexcept;

    [[nodiscard]] float axis(Key negative, Key positive) const noexcept;

    [[nodiscard]] MousePosition mouse_position() const noexcept { return mouse_position_; }
    [[nodiscard]] MousePosition mouse_delta() const noexcept { return mouse_delta_; }
    [[nodiscard]] float wheel_delta() const noexcept { return wheel_delta_; }

private:
    static constexpr std::size_t keys = key_count();
    static constexpr std::size_t buttons = mouse_button_count();

    std::array<bool, keys> key_down_{};
    std::array<bool, keys> key_pressed_{};
    std::array<bool, keys> key_released_{};
    std::array<bool, buttons> button_down_{};
    std::array<bool, buttons> button_pressed_{};
    std::array<bool, buttons> button_released_{};
    MousePosition mouse_position_{};
    MousePosition mouse_delta_{};
    float wheel_delta_{};
    bool has_mouse_position_{};
};

}  // namespace avernal
