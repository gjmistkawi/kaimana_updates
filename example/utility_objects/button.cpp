#include "button.h"
#include "led.h"
#include "color.h"
#include <avr/io.h>

// Button ==========================================
// represents the physical buttons of the controller

Button::Button(int pin) {
    _pin = pin;
}

bool Button::isPressed(void) {
    return !digitalRead(_pin);
}


// LED Button ======================================
// used for controller buttons with LEDs

LED_Button::LED_Button(LED* top, LED* bottom, int pin) : Button(pin) {
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