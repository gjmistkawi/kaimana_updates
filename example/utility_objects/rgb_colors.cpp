#include "rgb_colors.h"
#include "color.h"
#include<stdlib.h>


RGB_Colors::RGB_Colors(void) {
    Color* _colors[13] = {
        new Color(255,255,255),   //white
        new Color(255,000,000),   //red
        new Color(000,255,000),   //green
        new Color(000,000,255),   //blue
        new Color(255,215,000),   //gold
        new Color(255,255,000),   //yellow
        new Color(255,000,255),   //pink
        new Color(000,255,255),   //cyan
        new Color(127,073,006),   //orange
        new Color(255,000,255),   //purple
        new Color(000,127,255),   //cobalt
        new Color(220,000,127),   //magenta
        new Color(127,220,000)    //lime_green
    };
}

Color* RGB_Colors::randomColor(void) {
    int length = sizeof(_colors)/sizeof(*_colors);
    int random = rand() % (length - 1) + 1 ; //dont want white as random color
    return _colors[random];
}

Color* RGB_Colors::white(void) {
    return _colors[0];
}

Color* RGB_Colors::red(void) {
    return _colors[1];
}

Color* RGB_Colors::green(void) {
    return _colors[2];
}

Color* RGB_Colors::blue(void) {
    return _colors[3];
}

Color* RGB_Colors::gold(void) {
    return _colors[4];
}

Color* RGB_Colors::yellow(void) {
    return _colors[5];
}

Color* RGB_Colors::pink(void) {
    return _colors[6];
}

Color* RGB_Colors::cyan(void) {
    return _colors[7];
}

Color* RGB_Colors::orange(void) {
    return _colors[8];
}

Color* RGB_Colors::purple(void) {
    return _colors[9];
}

Color* RGB_Colors::cobalt(void) {
    return _colors[10];
}

Color* RGB_Colors::magenta(void) {
    return _colors[11];
}

Color* RGB_Colors::lime_green(void) {
    return _colors[12];
}
