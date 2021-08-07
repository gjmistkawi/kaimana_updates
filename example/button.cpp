#include "button.h"

// Button ==========================================
// represents the physical buttons of the controller

Button::Button(int pin, uint16_t mask) {
    _pin  = pin;
    _mask = mask;
}

bool Button::isPressed(void) {
    return !digitalRead(_pin);
}

void Button::activatePin(void) {
    pinMode(_pin, INPUT_PULLUP);
}

uint16_t Button::getMask(void) {
    return _mask;
}

// LED Button ======================================
// used for controller buttons with LEDs

LED_Button::LED_Button(LED* top, LED* bottom, int pin, uint16_t mask) : Button(pin, mask) {
    _top = top;
    _bottom = bottom;
}

void LED_Button::changeColor(Color* color) {
    _top->setColor(color);
    _bottom->setColor(color);
}

void LED_Button::toggleOn(bool isOn) {
    _top->toggleOn(isOn);
    _bottom->toggleOn(isOn);
}