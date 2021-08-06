#ifndef __button_h__
#define __button_h__

#include "led.h"

class Button {
    private:
        int _pin;

    public:
        Button();
        Button(int);
        bool isPressed(void);
};

class LED_Button : public Button {
    private:
        LED* _top;
        LED* _bottom;

    public:
        LED_Button();
        LED_Button(LED*,LED*,int);
        void changeColor(Color*);
        void toggleOn(bool);
};

#endif