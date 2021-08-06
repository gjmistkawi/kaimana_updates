#ifndef __led_h__
#define __led_h__

#include "color.h"

class LED {
    private:
        int _id;
        bool _isOn;
        Color* _color;

    public:
        LED(int, Color*);
        void setColor(Color*);
        int getId(void);
        bool isOn(void);
        void changeStatus(bool);
        Color* getColor(void);
};

#endif