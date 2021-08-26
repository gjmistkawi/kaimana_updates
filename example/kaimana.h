//  kaimana.h
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
//  Kaimana class based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//

#ifndef __kaimana_h__
#define __kaimana_h__

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "constants.h"


// RGB value structure.
typedef struct __attribute__ ((__packed__)) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_t;


// table of switch pin numbers
const unsigned char switchPins[SWITCH_COUNT] = { PIN_DOWN, PIN_UP, PIN_LEFT, PIN_RIGHT, PIN_HOME, PIN_SELECT, PIN_START, PIN_P1, PIN_P2, PIN_P3, PIN_P4, PIN_K1, PIN_K2, PIN_K3, PIN_K4 };


// define the Kaimana class
//
class Kaimana
{
  private:
    // declare RGB array for 15 buttons --> 12 LEDs
    // specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
    RGB_t    _led[LED_COUNT];
    uint16_t _switchHistory[SWITCH_HISTORY_MAX];

  public:
    Kaimana(void);
    void    setLED(int led, int iR, int iG, int iB);
    void    setLEDRandomColor(int led);
    void    setALL(int iR, int iG, int iB);
    void    updateALL(void);
    void    switchHistoryClear(void);
    void    switchHistorySet(uint16_t latestValue);
    boolean switchHistoryTest( uint16_t a0=MASK_ATTACK_FALSE, uint16_t a1=MASK_ATTACK_FALSE, uint16_t a2=MASK_ATTACK_FALSE,  uint16_t a3=MASK_ATTACK_FALSE,  uint16_t a4=MASK_ATTACK_FALSE,  uint16_t a5=MASK_ATTACK_FALSE,  uint16_t a6=MASK_ATTACK_FALSE,  uint16_t a7=MASK_ATTACK_FALSE, uint16_t a8=MASK_ATTACK_FALSE, uint16_t a9=MASK_ATTACK_FALSE, uint16_t a10=MASK_ATTACK_FALSE, uint16_t a11=MASK_ATTACK_FALSE, uint16_t a12=MASK_ATTACK_FALSE, uint16_t a13=MASK_ATTACK_FALSE, uint16_t a14=MASK_ATTACK_FALSE, uint16_t a15=MASK_ATTACK_FALSE );
};


// prototypes for Kaimana functions
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
//void 	setLED(int index, int iR, int iG, int iB);
//void 	setALL(int iR, int iG, int iB);
//void 	updateALL(void);
//void 	switchHistoryClear(void);
//void 	switchHistorySet(uint16_t latestValue);
//boolean switchHistoryTest( uint16_t a0=MASK_ATTACK_FALSE, uint16_t a1=MASK_ATTACK_FALSE, uint16_t a2=MASK_ATTACK_FALSE,  uint16_t a3=MASK_ATTACK_FALSE,  uint16_t a4=MASK_ATTACK_FALSE,  uint16_t a5=MASK_ATTACK_FALSE,  uint16_t a6=MASK_ATTACK_FALSE,  uint16_t a7=MASK_ATTACK_FALSE, uint16_t a8=MASK_ATTACK_FALSE, uint16_t a9=MASK_ATTACK_FALSE, uint16_t a10=MASK_ATTACK_FALSE, uint16_t a11=MASK_ATTACK_FALSE, uint16_t a12=MASK_ATTACK_FALSE, uint16_t a13=MASK_ATTACK_FALSE, uint16_t a14=MASK_ATTACK_FALSE, uint16_t a15=MASK_ATTACK_FALSE );


#endif
