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
/*
#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
//#include "kaimana.h"
//#include "kaimana_custom.h"
#include "animations.h"


// Color Fade Animation when Idle
//
int animation_idle(void)
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


// Hadouken (Fireball)
//
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
//
void animation_combo_2(void)
{
  kaimana.setALL(BLACK);

  kaimana.setALL(RED);
  delay(2000);

  kaimana.setALL(BLACK);
}


// Tatsumaki Senpukyaku (Hurricane Kick)
//
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
//
void animation_combo_4(void)
{
  kaimana.setALL(BLACK);

  kaimana.setALL(BLUE);
  delay(2000);

  kaimana.setALL(BLACK);
}


// Ultra 1 (Metsu Hadouken)
//
void animation_combo_5(void)
{
  kaimana.setALL(BLACK);

  kaimana.setALL(PURPLE);
  delay(2000);

  kaimana.setALL(BLACK);
}


// Ultra 2 (Metsu Shoryuken)
//
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


//Utility functions
// set LED to one of 8 predefined colors selected at random
//
void setLEDRandomColor2(int index)
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

//New animations
//Generic Animations

//turns 1 led on for a duration, then back to black
void blink_led(int led, int delay_time, int iR, int iG, int iB)
{
  kaimana.setLED( led, iR, iG, iB);
  kaimana.updateALL();
  delay(delay_time);
  kaimana.setLED( led, BLACK );
  kaimana.updateALL();
}

//turns 2 leds on for a duration, then back to black
void blink_led_pair(int led1, int led2, int delay_time, int iR, int iG, int iB)
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

//Specific Animations

bool led_checker(void)
{
  int delay_time = 500;

  for(int i = 0; i < 14; i++)
  {
    kaimana.setALL(BLACK);
    kaimana.setLED(i, WHITE);
    kaimana.updateALL();
    delay(delay_time);
  }
  return true;
}

//animation runs when combo-break button is pressed
void combo_break_animation(void)
{
  int delay_time = 50;

  for(int i = 0; i < 20; i++)
  {
    kaimana.setALL(WHITE);
    for(int j = 0; j < 14; j++)
    {
      if((i%2) == (j%2))
      {
        setLEDRandomColor2(j);
      }
    }
    kaimana.updateALL();
    delay(delay_time);
  }
}

//blink main button when toggling tournament mode
//for clarity
void tournament_mode_toggle_animation(int iR, int iG, int iB)
{
  int delay_time = IDLE_ANIMATION_DELAY*10;
  kaimana.setALL(BLACK);
  kaimana.updateALL();

  for(int i = 0; i < 3; i++)
  {
    blink_led_pair(LED_P3, LED_P4, delay_time, iR, iG, iB);
    delay(delay_time);
  }
}

//creates a looping animation around the controller
//my buttons are layed out oddly for wiring though,
//so this will need to be editted by controller
void startup_animation(void)
{
  int delay_time = IDLE_ANIMATION_DELAY*10;

  for(int i = 0; i < 3; i++)
  {
    blink_led_pair(LED_P3, LED_P4, delay_time, WHITE);
    delay(delay_time);
  }

  delay(delay_time);

  kaimana.setLED( LED_P3, PINK);
  kaimana.setLED( LED_P4, PINK);

  blink_led(LED_K1,     delay_time, AQUA);

  for(int i = 0; i < 3; i++)
  {
    blink_led_pair(LED_K2,     LED_K1,     delay_time, AQUA);
    blink_led_pair(LED_K3,     LED_K2,     delay_time, AQUA);
    blink_led_pair(LED_K4,     LED_K3,     delay_time, AQUA);
    blink_led_pair(LED_GUIDE,  LED_K4,     delay_time, AQUA);
    blink_led_pair(LED_BACK,   LED_GUIDE,  delay_time, AQUA);
    blink_led_pair(LED_P1,     LED_BACK,   delay_time, AQUA);
    blink_led_pair(LED_P2,     LED_P1,     delay_time, AQUA);
    blink_led_pair(LED_START,  LED_P2,     delay_time, AQUA);
    blink_led_pair(LED_SELECT, LED_START,  delay_time, AQUA);
    blink_led_pair(LED_HOME,   LED_SELECT, delay_time, AQUA);
    blink_led_pair(LED_JOY,    LED_HOME,   delay_time, AQUA);
    blink_led_pair(LED_K1,     LED_JOY,    delay_time, AQUA);
  }

  kaimana.setALL(PINK);
  kaimana.updateALL();

  delay(BOOT_COLOR_DELAY*2);
  kaimana.setALL( BLACK );
  delay( BOOT_COMPLETE_DELAY );
}
*/
