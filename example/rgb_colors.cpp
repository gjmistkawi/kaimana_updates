#include "rgb_colors.h"


RGB_Colors::RGB_Colors(void) {
    Color* _colors[COLOR_COUNT] = {
        new Color(WHITE),
        new Color(BLACK),
        new Color(RED),
        new Color(GREEN),
        new Color(BLUE),
        new Color(GOLD),
        new Color(YELLOW),
        new Color(PINK),
        new Color(CYAN),
        new Color(ORANGE),
        new Color(PURPLE),
        new Color(COBALT),
        new Color(MAGENTA),
        new Color(LIME_GREEN)
    };
}

RGB_Colors::~RGB_Colors(void) {
    int length = sizeof(_colors)/sizeof(*_colors);
    
    for(int i = 0; i < length; i++) {
        delete _colors[i];
    }
}


Color* RGB_Colors::randomColor(void) {
    int length = sizeof(_colors)/sizeof(*_colors);
    int random = rand() % (length - 1) + 2 ; //dont want white or black as random color
    return _colors[random];
}

Color* RGB_Colors::white(void) {
    return _colors[0];
}

Color* RGB_Colors::black(void) {
    return _colors[1];
}

Color* RGB_Colors::red(void) {
    //return new Color(RED);
    return _colors[2];
}

Color* RGB_Colors::green(void) {
    return _colors[3];
}

Color* RGB_Colors::blue(void) {
    //return new Color(BLUE);
    return _colors[4];
}

Color* RGB_Colors::gold(void) {
    return _colors[5];
}

Color* RGB_Colors::yellow(void) {
    return _colors[6];
}

Color* RGB_Colors::pink(void) {
    return _colors[7];
}

Color* RGB_Colors::cyan(void) {
    return _colors[8];
}

Color* RGB_Colors::orange(void) {
    return _colors[9];
}

Color* RGB_Colors::purple(void) {
    return _colors[10];
}

Color* RGB_Colors::cobalt(void) {
    return _colors[11];
}

Color* RGB_Colors::magenta(void) {
    return _colors[12];
}

Color* RGB_Colors::limeGreen(void) {
    return _colors[13];
}
