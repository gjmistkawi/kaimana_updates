//  example.ino
//
//  Copyright 2013 Paradise Arcade Shop, ParadiseArcadeShop.com  
//  All rights reserved.  Use is subject to license terms.
//
//  Code is provided for entertainment purposes and use with the Kaimana controller.
//  Code may be copied, modified, resused with this Copyright notice.
//  No commercial use without written permission from Paradise Arcade Shop.
//
//  Paradise Arcade Shop Kaimana LED Driver Board
//  Initial Release October 15, 2013
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
//  Kaimana example based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//


#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "kaimana.h"
#include "animations.h"
#include "constants.h"


// local function declarations
int  pollSwitches(void);
void showStartup(void);
void setLEDRandomColor(int index);


//global variables
Kaimana kaimana;
bool  tournament_mode;
int   tournament_mode_counter;
uint16_t button_activity;


// the setup routine runs first and once each time power is applied to the Kaimana board
void setup() 
{        
    tournament_mode = false;
    tournament_mode_counter = 0;

    // light up all leds at boot to demonstrate everything is functional
    startupAnimation();
}


// the loop routine repeats indefinitely and executes immediately following the setup() function
void loop() 
{
    unsigned long timeoutTimer = millis() + ((unsigned long) IDLE_TIMEOUT * 1000);

    while(true) {
        // if no button pressed, tournament mode is off, and enough time has passed,
        // run idle animation
        if(!checkAllButtons() && !tournament_mode && millis() > timeoutTimer) {
            animationIdle();
        }

        // update timer whenever button pressed
        else {
            timeoutTimer = millis() + ((unsigned long) IDLE_TIMEOUT * 1000);
        }

        kaimana.updateALL();
        delay(MAIN_LOOP_DELAY);
    }
}


// ==============================================================
//
//  local functions start here
//
// ==============================================================


uint16_t checkJoystickButtons() {
    uint16_t joystickDirection = MASK_ATTACK_NONE;

    if(!digitalRead(PIN_RIGHT))    
        joystickDirection |= MASK_ATTACK_RIGHT;
    if(!digitalRead(PIN_LEFT))
        joystickDirection |= MASK_ATTACK_LEFT;
    if(!digitalRead(PIN_DOWN))
        joystickDirection |= MASK_ATTACK_DOWN;
    if(!digitalRead(PIN_UP))
        joystickDirection |= MASK_ATTACK_UP;

    if(joystickDirection != MASK_ATTACK_NONE) {
        kaimana.setALL(WHITE);
        
        //sets the center button color
        switch(joystickDirection) {
            case MASK_ATTACK_RIGHT:    // right
            kaimana.setLED(LED_P3, GREEN);    
            kaimana.setLED(LED_P4, GREEN); 
            break;
            case MASK_ATTACK_LEFT:    // left
            kaimana.setLED(LED_P3, GREEN);    
            kaimana.setLED(LED_P4, GREEN);  
            break;
            case MASK_ATTACK_DOWN:    // down
            kaimana.setLED(LED_P3, RED);    
            kaimana.setLED(LED_P4, RED); 
            break;
            case MASK_ATTACK_DOWN + MASK_ATTACK_RIGHT:    // down + right
            kaimana.setLED(LED_P3, YELLOW);    
            kaimana.setLED(LED_P4, YELLOW); 
            break;
            case MASK_ATTACK_DOWN + MASK_ATTACK_LEFT:    // down + left
            kaimana.setLED(LED_P3, YELLOW);    
            kaimana.setLED(LED_P4, YELLOW); 
            break;
            case MASK_ATTACK_UP:    // up
            kaimana.setLED(LED_P3, BLUE);    
            kaimana.setLED(LED_P4, BLUE); 
            break;
            case MASK_ATTACK_UP + MASK_ATTACK_RIGHT:    // up + right
            kaimana.setLED(LED_P3, CYAN);    
            kaimana.setLED(LED_P4, CYAN); 
            break;
            case MASK_ATTACK_UP + MASK_ATTACK_LEFT:   // up + left
            kaimana.setLED(LED_P3, CYAN);    
            kaimana.setLED(LED_P4, CYAN); 
            break;
            default:   // zero or any undefined value on an 8 way stick like UP+DOWN which is not happening on my watch
            kaimana.setLED(LED_P3, WHITE);    
            kaimana.setLED(LED_P4, WHITE);   
            break;
        }

        joystickDirection |= MASK_JOYSTICK;
    }

    return joystickDirection;
}

bool readButton(int button, int iR, int iG, int iB) {
    if(!digitalRead(button)) {
        kaimana.setALL(iR, iG, iB);
        return true;
    }

    return false;
}

uint16_t checkMenuButtons() {
    uint16_t activity = MASK_ATTACK_NONE;

    // better to do this manually than with a loop to specify animations
    readButton(PIN_HOME,   BLUE) ? activity |= MASK_MENU_HOME : true;   //home
    readButton(PIN_SELECT, BLUE) ? activity |= MASK_MENU_SELECT : true;   //select
    readButton(PIN_START,  BLUE) ? activity |= MASK_MENU_START : true;   //start

    return activity;
}

uint16_t checkAttackButtons() {
    uint16_t activity = MASK_ATTACK_NONE;

    readButton(PIN_P1, GOLD)   ? activity |= MASK_ATTACK_P1 : true;
    readButton(PIN_P2, GREEN)  ? activity |= MASK_ATTACK_P2 : true;
    readButton(PIN_P3, CYAN)   ? activity |= MASK_ATTACK_P3 : true;
    readButton(PIN_P4, PINK)   ? activity |= MASK_ATTACK_P4 : true;
    readButton(PIN_K1, WHITE)  ? (comboBreakAnimation(),  activity |= MASK_ATTACK_K1) : true;
    readButton(PIN_K2, WHITE)  ? (romanCancelAnimation(), activity |= MASK_ATTACK_K2) : true;
    readButton(PIN_K3, ORANGE) ? activity |= MASK_ATTACK_K3 : true;
    readButton(PIN_K4, RED)    ? activity |= MASK_ATTACK_K4 : true;

    return activity;
}

bool checkAllButtons() {
    uint16_t button_activity = MASK_ATTACK_NONE;

    button_activity += checkJoystickButtons();
    button_activity += checkMenuButtons();
    button_activity += (tournament_mode ? 0x0000UL: checkAttackButtons());

    //check for tournament mode
    uint16_t tournament_check = button_activity | MASK_ATTACK_REMOVAL;
    if(tournament_check == MASK_TOURNAMENT_MODE) {
        if(tournament_mode_counter < 15) {
            tournament_mode_counter++;
        }

        else {
            tournament_mode_counter = 0;
            tournament_mode = !tournament_mode;
            tournament_mode ? tournamentModeToggleAnimation(RED): tournamentModeToggleAnimation(GREEN);
        }
    }

    if(button_activity != MASK_ATTACK_NONE && !tournament_mode) {
        kaimana.switchHistorySet(button_activity);
        return true;
    }

    else {
        kaimana.setALL(BLACK);
        return false;
    }
}
