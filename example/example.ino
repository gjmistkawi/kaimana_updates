//  example.ino

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "controller.h"
#include "constants.h"

// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Controller* controller;


// the setup routine runs first and once each time power is applied to the Kaimana board
void setup() {      
    controller = new Controller();
}

// the loop routine repeats indefinitely and executes immediately following the setup() function
void loop() {
    unsigned long timeoutTimer = millis() + ((unsigned long) IDLE_TIMEOUT * 1000);

    while(true) {
        // if no button pressed, tournament mode is off, and enough time has passed,
        // run idle animation

        //controller->checkButtons();
        
        //if(!controller->checkButtons() && !controller->isTournamentMode()
        //   && millis() > timeoutTimer) {
        //    controller->isIdle();
        //}

        // update timer whenever button pressed
        //else { 
        //    timeoutTimer = millis() + ((unsigned long) IDLE_TIMEOUT * 1000);
        //}

        //controller->displayLEDs();

        controller->temp();
        delay(MAIN_LOOP_DELAY*10);
    }
}
