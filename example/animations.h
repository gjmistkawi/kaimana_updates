//  combo_animatinos.h
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

#ifndef __animations_h__
#define __animations_h__

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "kaimana.h"
#include "constants.h"

extern Kaimana kaimana;

// other function prototypes
int  animationIdle(void);
void startupAnimation(void);
void tournamentModeToggleAnimation(int, int, int);
void comboBreakAnimation(void);
void romanCancelAnimation(void);
void ledChecker(void);

// street figher 4 - ryu's special moves (combos)
// http://www.eventhubs.com/guides/2008/jul/06/ryu-street-fighter-4-character-guide/
void animation_combo_1(void);    // Hadouken (Fireball)
void animation_combo_2(void);    // Shoryuken (Dragon Punch)
void animation_combo_3(void);    // Tatsumaki Senpukyaku (Hurricane Kick)
void animation_combo_4(void);    // Super — Shinkuu Hadouken
void animation_combo_5(void);    // Ultra 1 — Metsu Hadouken
void animation_combo_6(void);    // Ultra 2 — Metsu Hadouken

#endif