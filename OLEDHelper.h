#ifndef OLED_CLASS
#define OLED_CLASS

#include "stdint.h"
#include <U8glib.h>

#define CHECK_VALID if(_dummy) return;

class OLED
{
    public:
        OLED();
        OLED(U8GLIB* screen);
        void blank();
        void showSplash(uint8_t major, uint8_t minor);
        void showVersion(uint8_t major, uint8_t minor);
    private:
        U8GLIB* _u8g;
        bool _dummy;
};
#endif