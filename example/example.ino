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
#include "kaimana_custom.h"
#include "animations.h"


// local function declarations
int  pollSwitches(void);
void showStartup(void);
void setLEDRandomColor(int index);


// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;


// the setup routine runs first and once each time power is applied to the Kaimana board
void setup() 
{                
  // light up all leds at boot to demonstrate everything is functional
  showStartup();
}



// the loop routine repeats indefinitely and executes immediately following the setup() function
void loop() 
{
  unsigned long  ulTimeout;
  
    
  // initialize timeout value to now + some seconds
  ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
  

  // infinite loop of read switches, update LEDs and idle animation when necessary
  while(true)
  {
    // active -- poll switches and update leds
    if( pollSwitches() != 0 )
    {
        // some switches were active so reset idle timeout to now + some seconds
        ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
    }
    else
    {
        // no switches active so test for start of idle timeout  
        if( millis() > ulTimeout )
        {
          animation_idle();
        }  
    }
    
    // delay a little to avoid flickering (yea, updates happens really, really fast!)
    delay( MAIN_LOOP_DELAY );
  } 
}


// ==============================================================
//
//  local functions start here
//
// ==============================================================


// light up all leds at boot to demonstrate everything is functional
//
void showStartup(void)
{
  startup_animation();
} 


// set LED to one of 8 predefined colors selected at random
//
void setLEDRandomColor(int index)
{
  switch(random(1,8))    // pick a random color between 1 and 8
  {
    case 1:
      kaimana.setLED(index, COLOR_RANDOM_1);
      break;
    case 2:
      kaimana.setLED(index, COLOR_RANDOM_2);
      break;
    case 3:
      kaimana.setLED(index, COLOR_RANDOM_3);
      break;
    case 4:
      kaimana.setLED(index, COLOR_RANDOM_4);
      break;
    case 5:
      kaimana.setLED(index, COLOR_RANDOM_5);
      break;
    case 6:
      kaimana.setLED(index, COLOR_RANDOM_6);
      break;
    case 7:
      kaimana.setLED(index, COLOR_RANDOM_7);
      break;
    case 8:
      kaimana.setLED(index, COLOR_RANDOM_8);
      break;
    default:   // any undefined value so discard data and set led to BLACK
      kaimana.setLED(index, BLACK);    
      break;
  }  
}


uint16_t checkJoyStick(int* iLED, int iR, int iG, int iB) 
{
  static uint16_t  joystickDirection;
  joystickDirection = ATTACK_NONE;

  if(!digitalRead(PIN_RIGHT))    
    joystickDirection |= ATTACK_RIGHT;
  if(!digitalRead(PIN_LEFT))
    joystickDirection |= ATTACK_LEFT;
  if(!digitalRead(PIN_DOWN))
    joystickDirection |= ATTACK_DOWN;
  if(!digitalRead(PIN_UP))
    joystickDirection |= ATTACK_UP;

  //if any joystick button is pressed, light em up
  if(joystickDirection != ATTACK_NONE)
  {
    kaimana.setALL(iR, iG, iB);
    iLED[LED_JOY] = true;
  }
  
  else
  {
    iLED[LED_JOY] = false;
  }

  return joystickDirection;
}


//pulled out button checks into new function
bool checkButton(int* iLED, int button, int led, int iR, int iG, int iB) 
{
  // test switch and set LED based on result       // HOME = GUIDE
  if(!digitalRead(button))
  {
    // switch is active
    if(iLED[led] == true)
    {
      //maintain color while switch is active
      //setLEDRandomColor(LED_HOME); old method
      kaimana.setALL(iR, iG, iB);
      iLED[led] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setALL(iR, iG, iB);
      iLED[led] = true;
    }

    //if button is pressed
    return true;  
  }
  else
  {
      // switch is inactive
      iLED[led] = false;

      //if button is not pressed
      return false; 
  }
}


int pollSwitches(void)
{
  static int  iLED[LED_COUNT];
  static int  iActiveSwitchCount;
  static int  i;  
  static int  j;  
  static int  firsttime;
  static uint16_t  joystickDirection;
  static uint16_t  switchActivity;

  // reset LED status
  if (firsttime == 1)
  {
    for(i=0;i<LED_COUNT;++i)
    {
      iLED[i] = false;
      firsttime = 0;
    }
  }

  // read arduino pins and save results in the mapped LED if button is pressed (pin grounded)

  // complex special case for joystick but it's worth the effort
  joystickDirection = checkJoyStick(iLED, WHITE);

  // clear results for switch activity

  switchActivity = ATTACK_NONE;

  //fucntion buttons
  checkButton(iLED, PIN_HOME, LED_HOME, BLUE);
  checkButton(iLED, PIN_SELECT, LED_SELECT, BLUE);
  checkButton(iLED, PIN_START, LED_START, BLUE);

  //attack buttons
  checkButton(iLED, PIN_P1, LED_P1, COLOR_RANDOM_1) ? switchActivity |= ATTACK_P1 : true;
  checkButton(iLED, PIN_P2, LED_P2, COLOR_RANDOM_2) ? switchActivity |= ATTACK_P2 : true;
  checkButton(iLED, PIN_P3, LED_P3, COLOR_RANDOM_3) ? switchActivity |= ATTACK_P3 : true;
  checkButton(iLED, PIN_P4, LED_P4, COLOR_RANDOM_4) ? switchActivity |= ATTACK_P4 : true;
  checkButton(iLED, PIN_K1, LED_K1, COLOR_RANDOM_5) ? switchActivity |= ATTACK_K1 : true;
  checkButton(iLED, PIN_K2, LED_K2, COLOR_RANDOM_6) ? switchActivity |= ATTACK_K2 : true;
  checkButton(iLED, PIN_K3, LED_K3, COLOR_RANDOM_7) ? switchActivity |= ATTACK_K3 : true;
  checkButton(iLED, PIN_K4, LED_K4, COLOR_RANDOM_8) ? switchActivity |= ATTACK_K4 : true;


  // convert joystick, P1-P4, K1-K4 into a single unsigned int
  switchActivity = joystickDirection + switchActivity;
  kaimana.switchHistorySet(switchActivity);
  


  // test for combinations from most complext to least complex
  // test for switches in reverse order (newest to oldest)
  // combo #6
  // test for: Ultra 2 (Metsu Shoryuken)
  // combo is: DOWN, DOWN+RIGHT, RIGHT, DOWN, DOWN+RIGHT, RIGHT, RIGHT+K3
  //if( kaimana.switchHistoryTest( COMBO_PATTERN_6A ) )
  //    animation_combo_6();

  // zero active switch counter (note: 4 way joystick counts as 1)
  iActiveSwitchCount = 0;
  
  // set LED color based on switch
  for(i=0;i<LED_COUNT;++i)
  {
    if(iLED[i] == true)
      ++iActiveSwitchCount;
  }  

  // update the leds with new/current colors in the array
  kaimana.updateALL();
  
  // return number of active switches
  return(iActiveSwitchCount);
}  



 

