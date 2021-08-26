#ifndef __button_h__
#define __button_h__

#include "led.h"
#include "color.h"
#include "constants.h"
#include <avr/io.h>
#include "Arduino.h"

class Button {
    private:
        int      _pin;
        uint16_t _mask;

    public:
        Button();
        Button(int, uint16_t);
        bool     isPressed(void);
        void     activatePin(void);
        uint16_t getMask(void);
};

class LED_Button : public Button {
    private:
        LED* _top;
        LED* _bottom;

    public:
        LED_Button();
        LED_Button(LED*,LED*,int, uint16_t);
        void changeColor(Color*);
        void toggleOn(bool);
};

#endif
