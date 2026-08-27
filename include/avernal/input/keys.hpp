#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace avernal {

enum class Key : std::uint8_t {
    unknown,
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    digit0,
    digit1,
    digit2,
    digit3,
    digit4,
    digit5,
    digit6,
    digit7,
    digit8,
    digit9,
    escape,
    enter,
    tab,
    space,
    backspace,
    left_shift,
    right_shift,
    left_control,
    right_control,
    left_alt,
    right_alt,
    left,
    right,
    up,
    down,
    f1,
    f2,
    f3,
    f4,
    f5,
    f6,
    f7,
    f8,
    f9,
    f10,
    f11,
    f12,
    count,
};

enum class MouseButton : std::uint8_t {
    left,
    right,
    middle,
    extra1,
    extra2,
    count,
};

[[nodiscard]] constexpr std::size_t key_count() noexcept {
    return static_cast<std::size_t>(Key::count);
}

[[nodiscard]] constexpr std::size_t mouse_button_count() noexcept {
    return static_cast<std::size_t>(MouseButton::count);
}

[[nodiscard]] constexpr bool is_valid(Key key) noexcept {
    return key != Key::unknown && key < Key::count;
}

[[nodiscard]] constexpr bool is_valid(MouseButton button) noexcept {
    return button < MouseButton::count;
}

[[nodiscard]] constexpr std::string_view key_name(Key key) noexcept {
    switch (key) {
    case Key::a:
        return "a";
    case Key::b:
        return "b";
    case Key::c:
        return "c";
    case Key::d:
        return "d";
    case Key::e:
        return "e";
    case Key::f:
        return "f";
    case Key::g:
        return "g";
    case Key::h:
        return "h";
    case Key::i:
        return "i";
    case Key::j:
        return "j";
    case Key::k:
        return "k";
    case Key::l:
        return "l";
    case Key::m:
        return "m";
    case Key::n:
        return "n";
    case Key::o:
        return "o";
    case Key::p:
        return "p";
    case Key::q:
        return "q";
    case Key::r:
        return "r";
    case Key::s:
        return "s";
    case Key::t:
        return "t";
    case Key::u:
        return "u";
    case Key::v:
        return "v";
    case Key::w:
        return "w";
    case Key::x:
        return "x";
    case Key::y:
        return "y";
    case Key::z:
        return "z";
    case Key::digit0:
        return "0";
    case Key::digit1:
        return "1";
    case Key::digit2:
        return "2";
    case Key::digit3:
        return "3";
    case Key::digit4:
        return "4";
    case Key::digit5:
        return "5";
    case Key::digit6:
        return "6";
    case Key::digit7:
        return "7";
    case Key::digit8:
        return "8";
    case Key::digit9:
        return "9";
    case Key::escape:
        return "escape";
    case Key::enter:
        return "enter";
    case Key::tab:
        return "tab";
    case Key::space:
        return "space";
    case Key::backspace:
        return "backspace";
    case Key::left_shift:
        return "left_shift";
    case Key::right_shift:
        return "right_shift";
    case Key::left_control:
        return "left_control";
    case Key::right_control:
        return "right_control";
    case Key::left_alt:
        return "left_alt";
    case Key::right_alt:
        return "right_alt";
    case Key::left:
        return "left";
    case Key::right:
        return "right";
    case Key::up:
        return "up";
    case Key::down:
        return "down";
    case Key::f1:
        return "f1";
    case Key::f2:
        return "f2";
    case Key::f3:
        return "f3";
    case Key::f4:
        return "f4";
    case Key::f5:
        return "f5";
    case Key::f6:
        return "f6";
    case Key::f7:
        return "f7";
    case Key::f8:
        return "f8";
    case Key::f9:
        return "f9";
    case Key::f10:
        return "f10";
    case Key::f11:
        return "f11";
    case Key::f12:
        return "f12";
    case Key::unknown:
    case Key::count:
        break;
    }
    return "unknown";
}

[[nodiscard]] constexpr std::string_view mouse_button_name(MouseButton button) noexcept {
    switch (button) {
    case MouseButton::left:
        return "left";
    case MouseButton::right:
        return "right";
    case MouseButton::middle:
        return "middle";
    case MouseButton::extra1:
        return "extra1";
    case MouseButton::extra2:
        return "extra2";
    case MouseButton::count:
        break;
    }
    return "unknown";
}

}  // namespace avernal
