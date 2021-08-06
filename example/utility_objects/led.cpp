#include "led.h"
#include "color.h"

LED::LED(int id, Color* color) {
    _id = id;
    _isOn = false;
    _color = color;
}


// Setters

void LED::changeStatus(bool on) {
    _isOn = on;
}

void LED::setColor(Color* color) {
    _color = color;
}


// Getters

int LED::getId(void) {
    return _id;
}

bool LED::isOn(void) {
    return _isOn;
}

Color* LED::getColor(void) {
    return _color;
}