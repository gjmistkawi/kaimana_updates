#include "color.h"

Color::Color(int r, int g, int b) {
    _r = r;
    _g = g;
    _b = b;
}

// Getters

uint8_t Color::r() {
    return _r;
}

uint8_t Color::g() {
    return _g;
}

uint8_t Color::b() {
    return _b;
}