#ifndef __rgb_colors_h__
#define __rgb_colors_h__

#include"color.h"

class RGB_Colors {
    private:
        Color** _colors;

    public:
        RGB_Colors(void);
        Color* randomColor(void);
        Color* red(void);
        Color* green(void);
        Color* blue(void);
        Color* gold(void);
        Color* yellow(void);
        Color* pink(void);
        Color* cyan(void);
        Color* orange(void);
        Color* purple(void);
        Color* cobalt(void);
        Color* magenta(void);
        Color* lime_green(void);
        Color* white(void);

};

#endif