// kaimana.cpp
//
//   Created:  October 25, 2013    zonbipanda // gmail.com
//   Revised:  October 25, 2013    zonbipanda // gmail.com
//

#include <avr/io.h>
#include "arduino.h"
#include "kaimana.h"
#include "kaimana_custom.h"
#include "animations.h"


// Hadouken (Fireball)
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
      kaimana.update();

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
    kaimana.update();

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

  kaimana.setALL(GREEN);
  delay(2000);

  kaimana.setALL(BLACK);
}


// Super — Shinkuu Hadouken
//
void animation_combo_4(void)
{
  kaimana.setALL(BLACK);

  kaimana.setALL(BLUE);
  delay(2000);

  kaimana.setALL(BLACK);
}


// Ultra 1 — Metsu Hadouken
//
void animation_combo_5(void)
{
  kaimana.setALL(BLACK);

  kaimana.setALL(PURPLE);
  delay(2000);

  kaimana.setALL(BLACK);
}


// Ultra 2 — Metsu Hadouken
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


