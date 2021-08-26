#ifndef __constants_h__
#define __constants_h__

#define __PROG_TYPES_COMPAT__

#include <avr/io.h>
#include <avr/pgmspace.h>

typedef uint8_t prog_uint8_t;

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

// number of switch inputs on kaimana
#define  SWITCH_COUNT         15

// if this is changed then Kaimana::switchHistoryTest must also be revised
#define  SWITCH_HISTORY_MAX  16

// Number of leds on controller
#define  LED_COUNT    14   


// Size of the moves tracked on the controller
#define  BUTTON_HISTORY_SIZE 10

// Map function names to binary input masks on atmega32u4 digital pin numbers
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  MASK_JOYSTICK        0x8000UL
#define  MASK_MENU_START      0x4000UL
#define  MASK_MENU_SELECT     0x2000UL
#define  MASK_MENU_HOME       0x1000UL
#define  MASK_ATTACK_UP       0x0800UL
#define  MASK_ATTACK_DOWN     0x0400UL
#define  MASK_ATTACK_LEFT     0x0200UL
#define  MASK_ATTACK_RIGHT    0x0100UL
#define  MASK_ATTACK_K4       0x0080UL
#define  MASK_ATTACK_K3       0x0040UL
#define  MASK_ATTACK_K2       0x0020UL
#define  MASK_ATTACK_K1       0x0010UL
#define  MASK_ATTACK_P4       0x0008UL
#define  MASK_ATTACK_P3       0x0004UL
#define  MASK_ATTACK_P2       0x0002UL
#define  MASK_ATTACK_P1       0x0001UL
#define  MASK_ATTACK_NONE     0x0000UL
#define  MASK_ATTACK_FALSE    0xFFFFUL
#define  MASK_TOURNAMENT_MODE 0xFF00UL
#define  MASK_ATTACK_REMOVAL  0x0F00UL

//// Move patterns
//#define  COMBO_PATTERN_1A    ATTACK_RIGHT + ATTACK_P1, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN


// Delays for timings throughout program
#define  BOOT_DELAY           250
#define  MAIN_LOOP_DELAY      50
#define  IDLE_TIMEOUT         30
#define  IDLE_ANIMATION_DELAY 8

// Color count
#define  COLOR_COUNT 14

// Color rgb codes
#define  WHITE   255,255,255
#define  BLACK   000,000,000
#define  RED     255,000,000
#define  GREEN   000,255,000
#define  BLUE    000,000,255
#define  GOLD    255,215,000
#define  YELLOW  255,255,000
#define  PINK    255,000,255
#define  CYAN    000,255,255
#define  ORANGE  127,073,006
#define  PURPLE  255,000,255
#define  COBALT  000,127,255
#define  MAGENTA 220,000,127
#define  LIME    127,220,000


// Animation constants

// Idle animaiton
#define  IDLE_SIZE           768
#define  IDLE_OFFSET_2       512
#define  IDLE_OFFSET_1       256
#define  IDLE_OFFSET_0       0
#define  IDLE_OFFSET         12    

// Fireball Animation
#define  FIREBALL_SIZE       768    // size of animation array
#define  FIREBALL_OFFSET_3   288    
#define  FIREBALL_OFFSET_2   192    
#define  FIREBALL_OFFSET_1    96    
#define  FIREBALL_DELAY      350    // value in microseconds

// definitions for combo switch patterns
//
//   test for switches in reverse order (newest to oldest)
//
//   street figher 4 - ryu's special moves
//   http://www.eventhubs.com/guides/2008/jul/06/ryu-street-fighter-4-character-guide/
//
#define  COMBO_PATTERN_1A    ATTACK_RIGHT + ATTACK_P1, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_1B    ATTACK_RIGHT + ATTACK_P2, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_2A    ATTACK_DOWN + ATTACK_RIGHT + ATTACK_P1, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE,  ATTACK_RIGHT
#define  COMBO_PATTERN_2B    ATTACK_DOWN + ATTACK_RIGHT + ATTACK_P2, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE,  ATTACK_RIGHT
#define  COMBO_PATTERN_3A    ATTACK_LEFT + ATTACK_K1, ATTACK_LEFT, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN
#define  COMBO_PATTERN_3B    ATTACK_LEFT + ATTACK_K2, ATTACK_LEFT, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN
#define  COMBO_PATTERN_4A    ATTACK_RIGHT + ATTACK_P1, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_5A    ATTACK_RIGHT + ATTACK_P3, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_6A    ATTACK_RIGHT + ATTACK_K3, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN


// data points for single full sinusoidal wave _/-\_/-
const prog_uint8_t sinusoid[257] PROGMEM = {
  0, 3, 6, 9, 12, 15, 18, 21, 24, 28, 31, 34, 37, 40, 43, 46, 49, 52,
  55, 58, 61, 64, 68, 71, 74, 77, 79, 82, 85, 88, 91, 94, 97, 100, 103,
  106, 109, 111, 114, 117, 120, 122, 125, 128, 131, 133, 136, 139, 141,
  144, 146, 149, 151, 154, 156, 159, 161, 164, 166, 168, 171, 173, 175,
  178, 180, 182, 184, 186, 188, 191, 193, 195, 197, 199, 201, 202, 204,
  206, 208, 210, 212, 213, 215, 217, 218, 220, 221, 223, 224, 226, 227,
  229, 230, 231, 233, 234, 235, 236, 237, 239, 240, 241, 242, 243, 244,
  244, 245, 246, 247, 248, 248, 249, 250, 250, 251, 251, 252, 252, 253,
  253, 253, 254, 254, 254, 254, 254, 254, 254, 255, 254, 254, 254, 254,
  254, 254, 254, 253, 253, 253, 252, 252, 251, 251, 250, 250, 249, 248,
  248, 247, 246, 245, 244, 244, 243, 242, 241, 240, 239, 237, 236, 235,
  234, 233, 231, 230, 229, 227, 226, 224, 223, 221, 220, 218, 217, 215,
  213, 212, 210, 208, 206, 204, 202, 201, 199, 197, 195, 193, 191, 188,
  186, 184, 182, 180, 178, 175, 173, 171, 168, 166, 164, 161, 159, 156,
  154, 151, 149, 146, 144, 141, 139, 136, 133, 131, 128, 125, 122, 120,
  117, 114, 111, 109, 106, 103, 100, 97, 94, 91, 88, 85, 82, 79, 77,
  74, 71, 68, 64, 61, 58, 55, 52, 49, 46, 43, 40, 37, 34, 31, 28, 24,
  21, 18, 15, 12, 9, 6, 3, 0
};

// data points for color cycling
const prog_uint8_t colorCycleData[] PROGMEM = {
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

#endif
