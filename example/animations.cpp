//  kaimana.cpp
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
//  Kaimana animations based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "kaimana.h"
#include "constants.h"
#include "animations.h"


// Color Fade Animation when Idle
//
int animationIdle(void)
{
  int  index;
  int  i;

  // set initial color to BLACK
  kaimana.setALL(BLACK);

  while(true)
  {
    for(index=0;index<IDLE_SIZE;++index)
    {
      // update strip with new color2
      for(i=0;i<LED_COUNT;++i)
      {
        kaimana.setLED(
          i,
          pgm_read_byte_near(&colorCycleData[((index+IDLE_OFFSET_2+((LED_COUNT-i)*IDLE_OFFSET))%IDLE_SIZE)]),
          pgm_read_byte_near(&colorCycleData[((index+IDLE_OFFSET_1+((LED_COUNT-i)*IDLE_OFFSET))%IDLE_SIZE)]),
          pgm_read_byte_near(&colorCycleData[((index+IDLE_OFFSET_0+((LED_COUNT-i)*IDLE_OFFSET))%IDLE_SIZE)])
        );
      }

      // update the leds with new/current colors in the array
      kaimana.updateALL();

      // test all switches and exit idle animation if active switch found
      for(i=0;i<SWITCH_COUNT;++i)
      {
        if( !digitalRead(switchPins[i]) )
          return(false);
      }

      // place test for switches here and use calculated timer not delay
      //
      delay( IDLE_ANIMATION_DELAY );
    }
  }
}


// ==============================================================
//
//  Added Animations
//
// ==============================================================

// Generic Animations

// turns 1 led on for a duration, then back to black
void blinkLed(int led, int delay_time, int iR, int iG, int iB)
{
  kaimana.setLED( led, iR, iG, iB);
  kaimana.updateALL();
  delay(delay_time);
  kaimana.setLED( led, BLACK );
  kaimana.updateALL();
}

// turns 2 leds on for a duration, then back to black
void blinkLedPair(int led1, int led2, int delay_time, int iR, int iG, int iB)
{
  kaimana.setLED( led1, iR, iG, iB);
  kaimana.setLED( led2, iR, iG, iB);
  kaimana.updateALL();
  delay(delay_time);
  kaimana.setLED( led1, BLACK );
  kaimana.setLED( led2, BLACK );
  kaimana.updateALL();
  delay(1); //need delay of 1, otherwise leds stay dark
}


// Specific Animations

void ledChecker(void)
{
  int delay_time = 500;

  for(int i = 0; i < 14; i++)
  {
    delay(1);
    kaimana.setALL(BLACK);
    delay(1);
    kaimana.setLED(i, WHITE);
    kaimana.updateALL();
    delay(delay_time);
  }
}

// animation runs when combo-break button is pressed
void comboBreakAnimation(void)
{
  int delay_time = 50;

  for(int i = 0; i < 20; i++)
  {
    kaimana.setALL(WHITE);
    for(int j = 0; j < 14; j++)
    {
      if((i%2) == (j%2))
      {
        kaimana.setLEDRandomColor(j);
      }
    }
    kaimana.updateALL();
    delay(delay_time);
  }
}

// animation runs when roman cancel button is pressed
void romanCancelAnimation(void) {
  // top row
  kaimana.setLED(0, PURPLE);
  kaimana.setLED(1, PURPLE);
  kaimana.setLED(8, PURPLE);
  kaimana.setLED(9, PURPLE);

  // middle row
  kaimana.setLED(2,  BLUE);
  kaimana.setLED(3,  BLUE);
  kaimana.setLED(10, BLUE);
  kaimana.setLED(11, BLUE);

  // bottom row
  kaimana.setLED(4,  YELLOW);
  kaimana.setLED(5,  YELLOW);  
  kaimana.setLED(12, YELLOW);
  kaimana.setLED(13, YELLOW);

  // center button
  kaimana.setLED(6, RED);
  kaimana.setLED(7, RED);

  kaimana.updateALL();
  delay(30); 


  kaimana.setALL(BLACK);
  kaimana.updateALL();
  delay(50);

  // top row
  kaimana.setLED(0, PURPLE);
  kaimana.setLED(1, PURPLE);
  kaimana.setLED(8, PURPLE);
  kaimana.setLED(9, PURPLE);

  // middle row
  kaimana.setLED(2,  BLUE);
  kaimana.setLED(3,  BLUE);
  kaimana.setLED(10, BLUE);
  kaimana.setLED(11, BLUE);

  // bottom row
  kaimana.setLED(4,  YELLOW);
  kaimana.setLED(5,  YELLOW);  
  kaimana.setLED(12, YELLOW);
  kaimana.setLED(13, YELLOW);

  // center button
  kaimana.setLED(6, RED);
  kaimana.setLED(7, RED);

  kaimana.updateALL();
  delay(550);
}

void selectButtonAnimation(void) {
  int delay_time = IDLE_ANIMATION_DELAY*10;

  for(int i = 0; i < 3; i++)
  {
    blinkLedPair(LED_K2,     LED_K1,     delay_time, GOLD);
    blinkLedPair(LED_K3,     LED_K2,     delay_time, GOLD);
    blinkLedPair(LED_K4,     LED_K3,     delay_time, GOLD);
    blinkLedPair(LED_GUIDE,  LED_K4,     delay_time, GOLD);
    blinkLedPair(LED_BACK,   LED_GUIDE,  delay_time, GOLD);
    blinkLedPair(LED_P2,     LED_BACK,   delay_time, GOLD);
    blinkLedPair(LED_P1,     LED_P2,     delay_time, GOLD);
    blinkLedPair(LED_START,  LED_P1,     delay_time, GOLD);
    blinkLedPair(LED_SELECT, LED_START,  delay_time, GOLD);
    blinkLedPair(LED_HOME,   LED_SELECT, delay_time, GOLD);
    blinkLedPair(LED_JOY,    LED_HOME,   delay_time, GOLD);
    blinkLedPair(LED_K1,     LED_JOY,    delay_time, GOLD);
  }

  delay(BOOT_DELAY);
}

void startButtonAnimation(void) {
  int delay_time = IDLE_ANIMATION_DELAY*10;

  for(int i = 0; i < 3; i++)
  {    
    blinkLedPair(LED_JOY,    LED_HOME,   delay_time, GOLD);
    blinkLedPair(LED_HOME,   LED_SELECT, delay_time, GOLD);
    blinkLedPair(LED_SELECT, LED_START,  delay_time, GOLD);
    blinkLedPair(LED_START,  LED_P1,     delay_time, GOLD);
    blinkLedPair(LED_P1,     LED_P2,     delay_time, GOLD);
    blinkLedPair(LED_P2,     LED_BACK,   delay_time, GOLD);
    blinkLedPair(LED_BACK,   LED_GUIDE,  delay_time, GOLD);
    blinkLedPair(LED_GUIDE,  LED_K4,     delay_time, GOLD);
    blinkLedPair(LED_K4,     LED_K3,     delay_time, GOLD);
    blinkLedPair(LED_K3,     LED_K2,     delay_time, GOLD);
    blinkLedPair(LED_K2,     LED_K1,     delay_time, GOLD);
    blinkLedPair(LED_K1,     LED_JOY,    delay_time, GOLD);
  }

  delay(BOOT_DELAY);
}

void guideButtonAnimation(void) {
  int delay_time = IDLE_ANIMATION_DELAY*20;

  kaimana.setLED(LED_P2, GOLD);
  kaimana.setLED(LED_BACK, GOLD);
  kaimana.updateALL();
  delay(delay_time);
  
  kaimana.setLED(LED_P1, GOLD);
  kaimana.setLED(LED_GUIDE, GOLD);
  kaimana.updateALL();
  delay(delay_time);

  kaimana.setLED(LED_START, GOLD);
  kaimana.setLED(LED_K4, GOLD);
  kaimana.updateALL();
  delay(delay_time);

  kaimana.setLED(LED_SELECT, GOLD);
  kaimana.setLED(LED_K3, GOLD);
  kaimana.updateALL();
  delay(delay_time);

  kaimana.setLED(LED_HOME, GOLD);
  kaimana.setLED(LED_K2, GOLD);
  kaimana.updateALL();
  delay(delay_time);
    
  kaimana.setLED(LED_JOY, GOLD);
  kaimana.setLED(LED_K1, GOLD);
  kaimana.updateALL();
  delay(delay_time);
  
  for(int i = 0; i < 4; i++) {
    kaimana.setLED( LED_P3, MAGENTA);
    kaimana.setLED( LED_P4, MAGENTA);
    kaimana.updateALL();
    delay(delay_time/2);

    kaimana.setLED( LED_P3, BLACK);
    kaimana.setLED( LED_P4, BLACK);
    kaimana.updateALL();  
    delay(delay_time/2);
  }
}

// blink main button when toggling tournament mode for clarity
void tournamentModeToggleAnimation(int iR, int iG, int iB)
{
  int delay_time = IDLE_ANIMATION_DELAY*10;
  kaimana.setALL(BLACK);
  kaimana.updateALL();

  for(int i = 0; i < 3; i++)
  {
    blinkLedPair(LED_P3, LED_P4, delay_time, iR, iG, iB);
    delay(delay_time);
  }
}

// creates a looping animation around the controller
// my buttons are layed out oddly for wiring though,
// so this will need to be editted by controller
void startupAnimation(void)
{
  int delay_time = IDLE_ANIMATION_DELAY*10;

  for(int i = 0; i < 3; i++)
  {
    blinkLedPair(LED_P3, LED_P4, delay_time, WHITE);
    delay(delay_time);
  }

  delay(delay_time);

  kaimana.setLED( LED_P3, PINK);
  kaimana.setLED( LED_P4, PINK);

  blinkLed(LED_K1,     delay_time, CYAN);

  for(int i = 0; i < 3; i++)
  {
    blinkLedPair(LED_K2,     LED_K1,     delay_time, CYAN);
    blinkLedPair(LED_K3,     LED_K2,     delay_time, CYAN);
    blinkLedPair(LED_K4,     LED_K3,     delay_time, CYAN);
    blinkLedPair(LED_GUIDE,  LED_K4,     delay_time, CYAN);
    blinkLedPair(LED_BACK,   LED_GUIDE,  delay_time, CYAN);
    blinkLedPair(LED_P2,     LED_BACK,   delay_time, CYAN);
    blinkLedPair(LED_P1,     LED_P2,     delay_time, CYAN);
    blinkLedPair(LED_START,  LED_P1,     delay_time, CYAN);
    blinkLedPair(LED_SELECT, LED_START,  delay_time, CYAN);
    blinkLedPair(LED_HOME,   LED_SELECT, delay_time, CYAN);
    blinkLedPair(LED_JOY,    LED_HOME,   delay_time, CYAN);
    blinkLedPair(LED_K1,     LED_JOY,    delay_time, CYAN);
  }

  kaimana.setALL(PINK);
  kaimana.updateALL();

  delay(BOOT_DELAY*2);
  kaimana.setALL( BLACK );
  kaimana.updateALL();
  delay(BOOT_DELAY);
}

// ==============================================================
//
//  Ryu combination animations
//
// ==============================================================


// Hadouken (Fireball)
void animation_combo_1(void)
{
  int  index;
  int  i;
  int  counter;

  counter = FIREBALL_SIZE-1;

  kaimana.setALL( BLACK );

  while(counter >=0)
  {
    // P1 & K1
    if( (counter < FIREBALL_SIZE) && (counter >= 0) )
    {
      kaimana.setLED(
        LED_P1,
        0,  // no red just cyan used for fireball
        pgm_read_byte_near(&colorCycleData[counter%FIREBALL_SIZE]),
        pgm_read_byte_near(&colorCycleData[counter%FIREBALL_SIZE])
      );
      kaimana.setLED(
        LED_K1,
        0,  // no red just cyan used for fireball
        pgm_read_byte_near(&colorCycleData[counter%FIREBALL_SIZE]),
        pgm_read_byte_near(&colorCycleData[counter%FIREBALL_SIZE])
      );
    }
    else
    {
      kaimana.setLED( LED_P1, BLACK );
      kaimana.setLED( LED_K1, BLACK );
    }

    // P2 & K2
    if( ((counter+(FIREBALL_OFFSET_1)) < FIREBALL_SIZE) && ((counter+(FIREBALL_OFFSET_1)) >= 0) )
    {
      kaimana.setLED(
        LED_P2,
        0,  // no red just cyan used for fireball
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_1))%FIREBALL_SIZE]),
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_1))%FIREBALL_SIZE])
      );
      kaimana.setLED(
        LED_K2,
        0,  // no red just cyan used for fireball
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_1))%FIREBALL_SIZE]),
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_1))%FIREBALL_SIZE])
      );
    }
    else
    {
      kaimana.setLED( LED_P2, BLACK );
      kaimana.setLED( LED_K2, BLACK );
    }

    // P3 & K3
    if( ((counter+(FIREBALL_OFFSET_2)) < 768) && ((counter+(FIREBALL_OFFSET_2)) >= 0) )
    {
      kaimana.setLED(
        LED_P3,
        0,  // no red just cyan used for fireball
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_2))%FIREBALL_SIZE]),
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_2))%FIREBALL_SIZE])
      );
      kaimana.setLED(
        LED_K3,
        0,  // no red just cyan used for fireball
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_2))%FIREBALL_SIZE]),
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_2))%FIREBALL_SIZE])
      );
    }
    else
    {
      kaimana.setLED( LED_P3, BLACK );
      kaimana.setLED( LED_K3, BLACK );
    }

    // P4 & K4
    if( ((counter+(FIREBALL_OFFSET_3)) < 768) && ((counter+(FIREBALL_OFFSET_3)) >= 0) )
    {
      kaimana.setLED(
        LED_P4,
        0,  // no red just cyan used for fireball
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_3))%FIREBALL_SIZE]),
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_3))%FIREBALL_SIZE])
      );
      kaimana.setLED(
        LED_K4,
        0,  // no red just cyan used for fireball
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_3))%FIREBALL_SIZE]),
        pgm_read_byte_near(&colorCycleData[(counter+(FIREBALL_OFFSET_3))%FIREBALL_SIZE])
      );
    }
    else
    {
      kaimana.setLED( LED_P4, BLACK );
      kaimana.setLED( LED_K4, BLACK );
    }

    // update the leds with new/current colors in the array
    kaimana.updateALL();

    // slow down the fireball animation
    delayMicroseconds( FIREBALL_DELAY );

    counter -= 4;
  }

  kaimana.setALL( BLACK );
}


// Shoryuken (Dragon Punch)
void animation_combo_2(void)
{
  kaimana.setALL(BLACK);

  kaimana.setALL(RED);
  delay(2000);

  kaimana.setALL(BLACK);
}


// Tatsumaki Senpukyaku (Hurricane Kick)
void animation_combo_3(void)
{

  kaimana.setALL(BLACK);

 kaimana.setLED( LED_K1, RED );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K2, RED );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K3, RED );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K4, RED );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P4, RED );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P3, RED );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P2, RED );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P1, RED );
   delay(25);
   kaimana.updateALL();


 kaimana.setLED( LED_K1, GREEN );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K2, GREEN );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K3, GREEN );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K4, GREEN );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P4, GREEN );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P3, GREEN );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P2, GREEN );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P1, GREEN );
   delay(25);
   kaimana.updateALL();


 kaimana.setLED( LED_K1, BLUE );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K2, BLUE );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K3, BLUE );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K4, BLUE );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P4, BLUE );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P3, BLUE );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P2, BLUE );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P1, BLUE );
   delay(25);
   kaimana.updateALL();

 kaimana.setLED( LED_K1, BLACK );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K2, BLACK );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K3, BLACK );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_K4, BLACK );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P4, BLACK );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P3, BLACK );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P2, BLACK );
   delay(25);
   kaimana.updateALL();
 kaimana.setLED( LED_P1, BLACK );
   delay(25);
   kaimana.updateALL();

}


// Super (Shinkuu Hadouken)
void animation_combo_4(void)
{
  kaimana.setALL(BLACK);

  kaimana.setALL(BLUE);
  delay(2000);

  kaimana.setALL(BLACK);
}


// Ultra 1 (Metsu Hadouken)
void animation_combo_5(void)
{
  kaimana.setALL(BLACK);

  kaimana.setALL(PURPLE);
  delay(2000);

  kaimana.setALL(BLACK);
}


// Ultra 2 (Metsu Shoryuken)
void animation_combo_6(void)
{
  kaimana.setALL(BLACK);


  kaimana.setALL(WHITE);
  delay(100);

  kaimana.setALL(BLACK);
  delay(100);


  kaimana.setALL(WHITE);
  delay(80);

  kaimana.setALL(BLACK);
  delay(80);


  kaimana.setALL(WHITE);
  delay(60);

  kaimana.setALL(BLACK);
  delay(60);


  kaimana.setALL(WHITE);
  delay(40);

  kaimana.setALL(BLACK);
  delay(40);


  kaimana.setALL(WHITE);
  delay(20);

  kaimana.setALL(BLACK);
  delay(20);


  kaimana.setALL(WHITE);
  delay(10);

  kaimana.setALL(BLACK);
  delay(10);


  kaimana.setALL(WHITE);
  delay(5);

  kaimana.setALL(BLACK);
  delay(5);


  kaimana.setALL(BLACK);
}
