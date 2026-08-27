#include <avernal/input/input.hpp>

#include <print>

int main() {
    avernal::Input input;
    input.set_key(avernal::Key::up, true);
    input.set_mouse_position(32.0f, 48.0f);
    input.set_mouse_button(avernal::MouseButton::left, true);

    std::println("key     = {}", avernal::key_name(avernal::Key::up));
    std::println("held    = {}", input.is_down(avernal::Key::up));
    std::println("axis    = {}", input.axis(avernal::Key::left, avernal::Key::right));
    std::println("mouse   = {},{}", input.mouse_position().x, input.mouse_position().y);
    std::println("button  = {}", input.is_down(avernal::MouseButton::left));
    return 0;
}
