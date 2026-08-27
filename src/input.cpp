#include <avernal/input/input.hpp>

namespace avernal {
namespace {

template<std::size_t N>
[[nodiscard]] bool read_bit(const std::array<bool, N>& bits, std::size_t index) noexcept {
    return index < N && bits[index];
}

}  // namespace

void Input::begin_frame() {
    key_pressed_.fill(false);
    key_released_.fill(false);
    button_pressed_.fill(false);
    button_released_.fill(false);
    mouse_delta_ = {};
    wheel_delta_ = 0.0f;
}

void Input::reset() {
    key_down_.fill(false);
    key_pressed_.fill(false);
    key_released_.fill(false);
    button_down_.fill(false);
    button_pressed_.fill(false);
    button_released_.fill(false);
    mouse_position_ = {};
    mouse_delta_ = {};
    wheel_delta_ = 0.0f;
    has_mouse_position_ = false;
}

void Input::release_all() {
    for (std::size_t i = 0; i < keys; ++i) {
        if (key_down_[i]) {
            key_down_[i] = false;
            key_released_[i] = true;
        }
    }
    for (std::size_t i = 0; i < buttons; ++i) {
        if (button_down_[i]) {
            button_down_[i] = false;
            button_released_[i] = true;
        }
    }
}

void Input::set_key(Key key, bool down) {
    if (!is_valid(key)) {
        return;
    }

    const auto index = static_cast<std::size_t>(key);
    if (down) {
        if (!key_down_[index]) {
            key_pressed_[index] = true;
        }
        key_down_[index] = true;
        return;
    }

    if (key_down_[index]) {
        key_released_[index] = true;
    }
    key_down_[index] = false;
}

void Input::set_mouse_button(MouseButton button, bool down) {
    if (!is_valid(button)) {
        return;
    }

    const auto index = static_cast<std::size_t>(button);
    if (down) {
        if (!button_down_[index]) {
            button_pressed_[index] = true;
        }
        button_down_[index] = true;
        return;
    }

    if (button_down_[index]) {
        button_released_[index] = true;
    }
    button_down_[index] = false;
}

void Input::set_mouse_position(float x, float y) {
    if (has_mouse_position_) {
        mouse_delta_.x += x - mouse_position_.x;
        mouse_delta_.y += y - mouse_position_.y;
    }
    mouse_position_ = {x, y};
    has_mouse_position_ = true;
}

void Input::add_mouse_delta(float dx, float dy) {
    mouse_delta_.x += dx;
    mouse_delta_.y += dy;
}

void Input::add_wheel_delta(float delta) {
    wheel_delta_ += delta;
}

bool Input::is_down(Key key) const noexcept {
    return is_valid(key) && read_bit(key_down_, static_cast<std::size_t>(key));
}

bool Input::was_pressed(Key key) const noexcept {
    return is_valid(key) && read_bit(key_pressed_, static_cast<std::size_t>(key));
}

bool Input::was_released(Key key) const noexcept {
    return is_valid(key) && read_bit(key_released_, static_cast<std::size_t>(key));
}

bool Input::is_down(MouseButton button) const noexcept {
    return is_valid(button) && read_bit(button_down_, static_cast<std::size_t>(button));
}

bool Input::was_pressed(MouseButton button) const noexcept {
    return is_valid(button) && read_bit(button_pressed_, static_cast<std::size_t>(button));
}

bool Input::was_released(MouseButton button) const noexcept {
    return is_valid(button) && read_bit(button_released_, static_cast<std::size_t>(button));
}

float Input::axis(Key negative, Key positive) const noexcept {
    return (is_down(positive) ? 1.0f : 0.0f) - (is_down(negative) ? 1.0f : 0.0f);
}

}  // namespace avernal
