#ifndef __color_h__
#define __color_h__

#include <stdint.h>

class Color {
    private:
        uint8_t _r;
        uint8_t _g;
        uint8_t _b;

    public:
        Color(int,int,int);
        uint8_t r(void);
        uint8_t g(void);
        uint8_t b(void);
}

#endif

//#include <unordered_map>
//uordered_map<string, *color> colors = {
//  {"blue", new color(...)}    
//}