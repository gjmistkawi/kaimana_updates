#include "color.h"

Color::Color(int r, int g, int b) {
    _r = r;
    _g = g;
    _b = b;
}

uint8_t Color::r() {
    return this->_r;
}

uint8_t Color::g() {
    return this->_g;
}

uint8_t Color::b() {
    return this->_b;
}