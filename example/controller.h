#ifndef __controller_h__
#define __controller_h__

#define __PROG_TYPES_COMPAT__
#include <QList.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"

#include "button.h"
#include "led.h"
#include "color.h"
#include "rgb_colors.h"
#include "constants.h"

// size of array for tracking history of inputs
//#define BUTTON_HISTORY_MAX    10

// RGB value structure.
typedef struct __attribute__ ((__packed__)) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_t;

class Controller {
    private:
        Button**    _allButtons;
        Button**    _joystickButtons;
        Button**    _menuButtons;
        Button**    _attackButtons;
        RGB_Colors* _colors;
        LED**       _leds; //used throughout program
        RGB_t       _led[LED_COUNT];  //used to translate color to readable format for arduino
        bool        _tournamentMode;
        QList<uint16_t> _buttonHistory;

        void       setAllLEDs(Color*);
        void       buttonHistoryClear(void);
        void       buttonHistoryUpdate(uint16_t);
        //bool       buttonHistoryCheck(uint16_t*);
        void       joystickCenterButton(uint16_t);
        uint16_t   checkJoystickButtons(Color*);
        uint16_t   checkMenuButtons(void);
        uint16_t   checkAttackButtons(void);


    public:
        Controller(void);
        ~Controller(void);
        bool checkButtons(void);
        void displayLEDs(void);
        void tournamentModeToggle(bool);
        bool isTournamentMode(void);
        void isIdle(void);
        void temp(void);
};


#endif
