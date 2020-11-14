#ifndef BUTTON_CLASS
#define BUTTON_CLASS

#include "stdint.h"

class Button
{
    public:
        enum ColorEffect{off, solid, toggle, fade, remote};
        Adafruit_NeoPixel* strip;
        
        Button(uint8_t pin, uint16_t ledNr);
        uint8_t Poll();
        void setColor(uint8_t r, uint8_t g, uint8_t b);
        void setColor(uint16_t hue);
        int getColor();
        void setLEDState(uint8_t state);
        uint8_t getLEDState();
    private:
        ColorEffect _effect;
        uint8_t _pin;
        uint16_t _ledNr;
        uint8_t _ledState;
        int _color;
        int8_t _counter;
        void setLED();

};
#endif