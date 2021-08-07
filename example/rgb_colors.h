#ifndef __rgb_colors_h__
#define __rgb_colors_h__

#include <stdlib.h>
#include "color.h"
#include "constants.h"

class RGB_Colors {
    private:
        Color* _colors[COLOR_COUNT];

    public:
        RGB_Colors(void);
        ~RGB_Colors(void);
        Color* randomColor(void);
        Color* white(void);
        Color* black(void);
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
        Color* limeGreen(void);
};

#endif
