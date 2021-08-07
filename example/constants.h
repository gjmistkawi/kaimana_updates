#ifndef __constants_h__
#define __constants_h__

// Map function names to arduino leonardo atmega32u4 digital pin numbers
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  PIN_DOWN    11
#define  PIN_UP      18
#define  PIN_LEFT    19
#define  PIN_RIGHT   20
#define  PIN_HOME    8
#define  PIN_GUIDE   8
#define  PIN_SELECT  9
#define  PIN_BACK    9
#define  PIN_START   10
#define  PIN_EXTRA   10 //this pin does not exist
#define  PIN_P1      3
#define  PIN_P2      2
#define  PIN_P3      0
#define  PIN_P4      1
#define  PIN_K1      4
#define  PIN_K2      21
#define  PIN_K3      12
#define  PIN_K4      6
//
#define  PIN_LED     23


// Map function names to default LED index numbers
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
// change or expand as needed
//
//   KAIMANA->LED_JOY->LED_HOME->LED_SELECT->LED_START->LED_P1->LED-P2->LED_P3->LED-P4->LED_K1->LED-K2->LED_K3->LED-K4
//
#define  LED_JOY     0
#define  LED_HOME    1
#define  LED_SELECT  2
#define  LED_START   3
#define  LED_P1      4
#define  LED_P2      5
#define  LED_P3      6
#define  LED_P4      7
#define  LED_K1      8
#define  LED_K2      9
#define  LED_K3      10
#define  LED_K4      11
#define  LED_GUIDE   12
#define  LED_BACK    13

// Button counts for different types on the controller
#define  TOTAL_BUTTON_COUNT    18
#define  MENU_BUTTON_COUNT     6
#define  ATTACK_BUTTON_COUNT   8
#define  JOYSTICK_BUTTON_COUNT 4

// Number of leds on controller
#define  LED_COUNT    14   


// Size of the moves tracked on the controller
#define BUTTON_HISTORY_SIZE 10

// Map function names to binary input masks on atmega32u4 digital pin numbers
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  MASK_JOYSTICK       0x8000UL
#define  MASK_MENU_START     0x4000UL
#define  MASK_MENU_SELECT    0x2000UL
#define  MASK_MENU_HOME      0x1000UL
#define  MASK_ATTACK_UP      0x0800UL
#define  MASK_ATTACK_DOWN    0x0400UL
#define  MASK_ATTACK_LEFT    0x0200UL
#define  MASK_ATTACK_RIGHT   0x0100UL
#define  MASK_ATTACK_K4      0x0080UL
#define  MASK_ATTACK_K3      0x0040UL
#define  MASK_ATTACK_K2      0x0020UL
#define  MASK_ATTACK_K1      0x0010UL
#define  MASK_ATTACK_P4      0x0008UL
#define  MASK_ATTACK_P3      0x0004UL
#define  MASK_ATTACK_P2      0x0002UL
#define  MASK_ATTACK_P1      0x0001UL
#define  MASK_ATTACK_NONE    0x0000UL
#define  MASK_ATTACK_FALSE   0xFFFFUL

//// Move patterns
//#define  COMBO_PATTERN_1A    ATTACK_RIGHT + ATTACK_P1, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN


// Delays for timings throughout program
#define BOOT_DELAY     250
#define MAIN_LOOP_DELAY      50
#define IDLE_TIMEOUT         30
#define IDLE_ANIMATION_DELAY 8

// Color count
#define COLOR_COUNT 14

// Color rgb codes
#define WHITE       255,255,255
#define BLACK       000,000,000
#define RED         255,000,000
#define GREEN       000,255,000
#define BLUE        000,000,255
#define GOLD        255,215,000
#define YELLOW      255,255,000
#define PINK        255,000,255
#define CYAN        000,255,255
#define ORANGE      127,073,006
#define PURPLE      255,000,255
#define COBALT      000,127,255
#define MAGENTA     220,000,127
#define LIME_GREEN  127,220,000


// Animation constants

// Idle animaiton
#define IDLE_SIZE           768
#define IDLE_OFFSET_2       512
#define IDLE_OFFSET_1       256
#define IDLE_OFFSET_0       0
#define IDLE_OFFSET         12    

// data points for color cycling
/*const prog_uint8_t colorCycleData[] PROGMEM = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   2,   4,   6,   8,  10,  12,  14,  16,  18,  20,  22,  24,  26,  28,  30,
   32,  35,  38,  41,  44,  47,  50,  53,  56,  59,  62,  65,  68,  71,  74,  77,
   81,  85,  89,  93,  97, 101, 105, 109, 113, 117, 121, 125, 129, 133, 137, 141,
  148, 155, 162, 169, 176, 183, 190, 197, 204, 211, 218, 225, 232, 239, 246, 253,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  253, 246, 239, 232, 225, 218, 211, 204, 197, 190, 183, 176, 169, 162, 155, 148,
  141, 137, 133, 129, 125, 121, 117, 113, 109, 105, 101,  97,  93,  89,  85,  81,
   77,  74,  71,  68,  65,  62,  59,  56,  53,  50,  47,  44,  41,  38,  35,  32,
   30,  28,  26,  24,  22,  20,  18,  16,  14,  12,  10,   8,   6,   4,   2,   0
};
*/

#endif
