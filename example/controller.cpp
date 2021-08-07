#include "controller.h"

Controller::Controller(void) {
    // set arduino led driver pin to output and low
    pinMode( PIN_LED, OUTPUT );
    digitalWrite( PIN_LED, LOW );

    // initialize random number seed with analog input #4 on port F1
    randomSeed(analogRead(4));

    // create list of colors
    RGB_Colors* _colors = new RGB_Colors();

    // create list of LEDs
    LED* _leds[LED_COUNT] = {
        new LED(LED_JOY,    _colors->white()),
        new LED(LED_HOME,   _colors->white()),
        new LED(LED_SELECT, _colors->white()),
        new LED(LED_START,  _colors->white()),
        new LED(LED_P1,     _colors->white()),
        new LED(LED_P2,     _colors->white()),
        new LED(LED_P3,     _colors->white()),
        new LED(LED_P4,     _colors->white()),
        new LED(LED_K1,     _colors->white()),
        new LED(LED_K2,     _colors->white()),
        new LED(LED_K3,     _colors->white()),
        new LED(LED_K4,     _colors->white()),
        new LED(LED_GUIDE,  _colors->white()),
        new LED(LED_BACK,   _colors->white())
    };


    // create button lists and initialize pin activation
    Button* _allButtons[TOTAL_BUTTON_COUNT] = {
        new LED_Button(_leds[6],  _leds[7],  PIN_UP, (MASK_ATTACK_UP + MASK_JOYSTICK)),
        new Button(PIN_DOWN,  (MASK_ATTACK_DOWN  + MASK_JOYSTICK)),
        new Button(PIN_LEFT,  (MASK_ATTACK_LEFT  + MASK_JOYSTICK)),
        new Button(PIN_RIGHT, (MASK_ATTACK_RIGHT + MASK_JOYSTICK)),
        new LED_Button(_leds[0],  _leds[1],  PIN_HOME,   MASK_MENU_HOME),
        new LED_Button(_leds[2],  _leds[3],  PIN_GUIDE,  MASK_MENU_HOME),
        new LED_Button(_leds[4],  _leds[5],  PIN_SELECT, MASK_MENU_SELECT),
        new LED_Button(_leds[8],  _leds[9],  PIN_BACK,   MASK_MENU_SELECT),
        new LED_Button(_leds[10], _leds[11], PIN_START,  MASK_MENU_START),
        new LED_Button(_leds[12], _leds[13], PIN_EXTRA,  MASK_MENU_START),
        new Button(PIN_P1, MASK_ATTACK_P1),
        new Button(PIN_P2, MASK_ATTACK_P2),
        new Button(PIN_P3, MASK_ATTACK_P3),
        new Button(PIN_P4, MASK_ATTACK_P4),
        new Button(PIN_K1, MASK_ATTACK_K1),
        new Button(PIN_K2, MASK_ATTACK_K2),
        new Button(PIN_K3, MASK_ATTACK_K3),
        new Button(PIN_K4, MASK_ATTACK_K4)
    };

    Button* _joystickButtons[JOYSTICK_BUTTON_COUNT] = {
        _allButtons[0], //up
        _allButtons[1], //down
        _allButtons[2], //left
        _allButtons[3]  //right
    };

    Button* _menuButtons[MENU_BUTTON_COUNT] = {
        _allButtons[4], //home
        _allButtons[5], //guide
        _allButtons[6], //select
        _allButtons[7], //back
        _allButtons[8], //start
        _allButtons[9]  //extra
    };

    Button* _attackButtons[ATTACK_BUTTON_COUNT] = {
        _allButtons[10], //p1
        _allButtons[11], //p2
        _allButtons[12], //p3
        _allButtons[13], //p4
        _allButtons[14], //k1
        _allButtons[15], //k2
        _allButtons[16], //k3
        _allButtons[17]  //k4
    };

    for(int i = 0; i < TOTAL_BUTTON_COUNT; i++) {
        _allButtons[i]->activatePin();
    }

    buttonHistoryClear();
    //startupAnimation();
}

Controller::~Controller(void) {
    for(int i = 0; i < TOTAL_BUTTON_COUNT; i++) {
        delete(_allButtons[i]);
    }

    for(int i = 0; i < LED_COUNT; i++) {
        delete(_leds[i]);
    }

    delete(_colors);
}

void Controller::displayLEDs(void) {
    Color* color;

    for(int i = 0; i < LED_COUNT; i++) {
        if(_leds[i]->isOn()) {
            color = _leds[i]->getColor();
        }

        // If the switch is off, set the color to black
        else {
            color = _colors->black();
        }

        //color = _colors->gold();
        //color = new Color(GOLD);

        _led[i].r = color->r;
        _led[i].g = color->g;
        _led[i].b = color->b;
    }
        
    // update the leds with new/current colors and delay a little to avoid flickering (yea, it happens really, really fast!)
    // specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
    // port F0 drives LED data out
    //
    //  WS2811 timing based upon the threepixeldemo example by Alan Burlison ( alan@bleaklow.com )
    //    http://sourceforge.net/p/abavr/lib/ci/21a95bf1f6c437cac414e8efb0c80558e5c369db/tree/WS2811/
    //

  asm volatile( \
  /* initialise */ \
  "    cp %A[len], r1      ; check len > 0, return immediately if it is\n" \
  "    cpc %B[len], r1\n" \
  "    brne 1f\n" \
  "    rjmp 16f\n" \
  "1:  ld r18, Z+           ; load in first red byte to be output\n" \
  "    ld r19, Z+           ; load in first green byte to be output\n" \
  "    ld r20, Z+           ; load in first blue byte to be output\n" \
  "    ldi r27, 8           ; load inner loop counter\n" \
  "    in r26, __SREG__     ; timing-critical, so no interrupts\n" \
  "    cli\n" \
  /* green - loop over 8 bits */ \
  "2:  sbi  %[port], %[pin] ; pin lo -> hi\n" \
  "    sbrc r19, 7          ; test hi bit clear\n" \
  "    rjmp 3f              ; true, skip pin hi -> lo\n" \
  "    cbi  %[port], %[pin] ; false, pin hi -> lo\n" \
  "3:  sbrc r19, 7          ; equalise delay of both code paths\n" \
  "    rjmp 4f\n" \
  "4:  nop                  ; pulse timing delay\n" \
  "    nop\n" \
  "    nop\n" \
  "    nop\n" \
  "    nop\n" \
  "    nop\n" \
  "    lsl r19              ; shift to next bit\n" \
  "    dec r27              ; decrement loop counter\n" \
  "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
  "    brne 2b\n            ; loop if required\n" \
  "    ldi r27, 7           ; reload inner loop counter\n" \
  /* red - loop over first 7 bits */ \
  "5:  sbi %[port], %[pin]  ; pin lo -> hi\n" \
  "    sbrc r18, 7          ; test hi bit clear\n" \
  "    rjmp 6f              ; true, skip pin hi -> lo\n" \
  "    cbi %[port], %[pin]  ; false, pin hi -> lo\n" \
  "6:  sbrc r18, 7          ; equalise delay of both code paths\n" \
  "    rjmp 7f\n" \
  "7:  nop                  ; pulse timing delay\n" \
  "    nop\n" \
  "    nop\n" \
  "    nop\n" \
  "    nop\n" \
  "    nop\n" \
  "    lsl r18              ; shift to next bit\n" \
  "    dec r27              ; decrement inner loop counter\n" \
  "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
  "    brne 5b              ; inner loop, if required\n" \
  "    nop                  ; equalise delay of both code paths\n" \
  /* red, 8th bit - output & fetch next values */ \
  "    sbi %[port], %[pin]  ; pin lo -> hi\n" \
  "    sbrc r18, 7          ; test hi bit clear\n" \
  "    rjmp 8f              ; true, skip pin hi -> lo\n" \
  "    cbi %[port], %[pin]  ; false, pin hi -> lo\n" \
  "8:  sbrc r18, 7          ; equalise delay of both code paths\n" \
  "    rjmp 9f\n" \
  "9:  nop                  ; pulse timing delay\n" \
  "    nop\n" \
  "    nop\n" \
  "    ld r18, Z+           ; load next red byte\n" \
  "    ld r19, Z+           ; load next green byte\n" \
  "    ldi r27, 7           ; reload inner loop counter\n" \
  "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
  "    nop                  ; pulse timing delay\n" \
  "    nop\n" \
  /* blue - loop over first 7 bits */ \
  "10:  sbi %[port], %[pin] ; pin lo -> hi\n" \
  "    sbrc r20, 7          ; test hi bit clear\n" \
  "    rjmp 11f             ; true, skip pin hi -> lo\n" \
  "    cbi %[port], %[pin]  ; false, pin hi -> lo\n" \
  "11: sbrc r20, 7          ; equalise delay of both code paths\n" \
  "    rjmp 12f\n" \
  "12: nop                  ; pulse timing delay\n" \
  "    nop\n" \
  "    nop\n" \
  "    nop\n" \
  "    nop\n" \
  "    nop\n" \
  "    lsl r20              ; shift to next bit\n" \
  "    dec r27              ; decrement inner loop counter\n" \
  "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
  "    brne 10b             ; inner loop, if required\n" \
  "    nop                  ; equalise delay of both code paths\n" \
  /* blue, 8th bit -  output & handle outer loop */ \
  "    sbi %[port], %[pin]  ; pin lo -> hi\n" \
  "    sbrc r20, 7          ; test hi bit clear\n" \
  "    rjmp 13f             ; true, skip pin hi -> lo\n" \
  "    cbi %[port], %[pin]  ; false, pin hi -> lo\n" \
  "13: sbrc r20, 7          ; equalise delay of both code paths\n" \
  "    rjmp 14f\n" \
  "14: nop                  ; pulse timing delay\n" \
  "    nop\n" \
  "    ldi r27, 8           ; reload inner loop counter\n" \
  "    sbiw %A[len], 1      ; decrement outer loop counter\n" \
  "    breq 15f             ; exit outer loop if zero\n" \
  "    ld r20, Z+           ; load in next blue byte\n" \
  "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
  "    rjmp 2b              ; outer loop, if required\n" \
  "15: nop                  ; pulse timing delay\n" \
  "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
  "    nop                  ; pulse timing delay\n" \
  "    nop\n" \
  "    out __SREG__, r26    ; reenable interrupts\n" \
  "16:\n" \
  : \
  : [rgb] "z" (&_led), \
    [len] "w" (sizeof(_led)/sizeof(_led[0])), \
    [port] "I" (_SFR_IO_ADDR(PORTF)), \
    [pin] "I" (0) \
  : "r18", "r19", "r20", "r26", "r27", "cc", "memory" \
  );
}  

void Controller::setAllLEDs(Color* color) {
    for(int i = 0; i < LED_COUNT; i++) {
        _leds[i]->setColor(color);
    }
}

void Controller::buttonHistoryClear(void) {
    _buttonHistory.clear();
}

void Controller::buttonHistoryUpdate(uint16_t input) {
    if(_buttonHistory.size() < BUTTON_HISTORY_SIZE) {
        _buttonHistory.pop_back();
    }

    _buttonHistory.push_front(input);
}

void Controller::tournamentModeToggle(bool tournamentMode) {
    for(int i = 0; i < LED_COUNT; i++) {
        _leds[i]->toggleOn(!tournamentMode);
    }

    _tournamentMode = tournamentMode;
}

bool Controller::isTournamentMode(void) {
    return _tournamentMode;
}

void Controller::isIdle(void) {
    unsigned long  ulTimeout;
    ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT * 1000 );
    while(false) {
        //idleAnimation();
    }
}

bool Controller::checkButtons(void) {
    bool buttonPressed = false; 
    uint16_t buttonActivity = MASK_ATTACK_NONE;

    buttonActivity += checkJoystickButtons(_colors->white());
    buttonActivity += checkMenuButtons();
    buttonActivity += checkAttackButtons();

    //_tournamentMode
        //mask the bits, check the bits we want
        //F is 15, so we mask with 0x0FFFUL use or operator
        //and test against 0xFFFFUL

    if(buttonActivity != MASK_ATTACK_NONE) {
        buttonPressed = true;
        buttonHistoryUpdate(buttonActivity);
    }

    else {
        setAllLEDs(_colors->black());
    }

    setAllLEDs(_colors->red());
    

    return buttonPressed;
}

uint16_t Controller::checkJoystickButtons(Color* color) {
    uint16_t joystickDirection = MASK_ATTACK_NONE;

    for(int i = 0; i < JOYSTICK_BUTTON_COUNT; i++) {
        if(_joystickButtons[i]->isPressed()) {
            joystickDirection |= _joystickButtons[i]->getMask();
        }
    }

    if(joystickDirection != MASK_ATTACK_NONE) {
        setAllLEDs(_colors->white());
        joystickCenterButton(joystickDirection);
    }

    return joystickDirection;
}

void Controller::joystickCenterButton(uint16_t direction) {
    LED_Button* button = (LED_Button*) _joystickButtons[0];

    switch(direction)
    {
        case MASK_ATTACK_RIGHT:   // right
            button->changeColor(_colors->green());
            break;
        case MASK_ATTACK_LEFT:    // left
            button->changeColor(_colors->green());
            break;
        case MASK_ATTACK_DOWN:    // down
            button->changeColor(_colors->red());
            break;
        case MASK_ATTACK_DOWN + MASK_ATTACK_RIGHT:    // down + right
            button->changeColor(_colors->yellow());
            break;
        case MASK_ATTACK_DOWN + MASK_ATTACK_LEFT:    // down + left
            button->changeColor(_colors->yellow());
            break;
        case MASK_ATTACK_UP:    // up
            button->changeColor(_colors->blue());
            break;
        case MASK_ATTACK_UP + MASK_ATTACK_RIGHT:    // up + right
            button->changeColor(_colors->cyan());
            break;
        case MASK_ATTACK_UP + MASK_ATTACK_LEFT:   // up + left
            button->changeColor(_colors->cyan());
            break;
        default:   // zero or any undefined value on an 8 way stick like UP+DOWN which is not happening on my watch
            button->changeColor(_colors->white());
            break;
    }  
}


uint16_t Controller::checkMenuButtons(void) {
    uint16_t activity = MASK_ATTACK_NONE;

    // better to do this manually than with a loop to specify animations
    _menuButtons[0]->isPressed() ? (setAllLEDs(_colors->blue()), activity |= _menuButtons[0]->getMask()) : true;    //home
    _menuButtons[1]->isPressed() ? (setAllLEDs(_colors->blue()), activity |= _menuButtons[1]->getMask()) : true;    //guide
    _menuButtons[2]->isPressed() ? (setAllLEDs(_colors->blue()), activity |= _menuButtons[2]->getMask()) : true;    //select
    _menuButtons[3]->isPressed() ? (setAllLEDs(_colors->blue()), activity |= _menuButtons[3]->getMask()) : true;    //back
    _menuButtons[4]->isPressed() ? (setAllLEDs(_colors->blue()), activity |= _menuButtons[4]->getMask()) : true;    //start
    _menuButtons[5]->isPressed() ? (setAllLEDs(_colors->blue()), activity |= _menuButtons[5]->getMask()) : true;    //extra

    return activity;
}

uint16_t Controller::checkAttackButtons(void) {
    uint16_t activity = MASK_ATTACK_NONE;

    _attackButtons[0]->isPressed() ? (setAllLEDs(_colors->purple()),    activity |= _attackButtons[0]->getMask()) : true;    //home
    _attackButtons[1]->isPressed() ? (setAllLEDs(_colors->magenta()),   activity |= _attackButtons[1]->getMask()) : true;    //guide
    _attackButtons[2]->isPressed() ? (setAllLEDs(_colors->blue()),      activity |= _attackButtons[2]->getMask()) : true;    //select
    _attackButtons[3]->isPressed() ? (setAllLEDs(_colors->cyan()),      activity |= _attackButtons[3]->getMask()) : true;    //back
    _attackButtons[4]->isPressed() ? (setAllLEDs(_colors->green()),     activity |= _attackButtons[4]->getMask()) : true;    //start
    _attackButtons[5]->isPressed() ? (setAllLEDs(_colors->limeGreen()), activity |= _attackButtons[5]->getMask()) : true;    //extra
    _attackButtons[6]->isPressed() ? (setAllLEDs(_colors->yellow()),    activity |= _attackButtons[6]->getMask()) : true;    //extra
    _attackButtons[7]->isPressed() ? (setAllLEDs(_colors->gold()),      activity |= _attackButtons[7]->getMask()) : true;    //extra

    return activity;
}

void Controller::temp(void) {
    setAllLEDs(new Color(BLUE));//_colors->blue());
    displayLEDs();
}
