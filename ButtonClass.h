#ifndef BUTTON_CLASS
#define BUTTON_CLASS

#include "Adafruit_NeoPixel.h"
#include "stdint.h"


class Button
{
    public:
        enum ColorEffect{off, solid, toggle, fade, invFade, onPush, onIdle, remote};
        Adafruit_NeoPixel* strip;
        Button();
        Button(uint8_t pin, uint16_t ledNr, Adafruit_NeoPixel* stripRef);
        uint8_t Poll();
        #pragma region LED-related
        void setColor(uint8_t r, uint8_t g, uint8_t b);
        void setColor(uint16_t hue);
        uint32_t getColor();
        void setLEDState(uint8_t state);
        uint8_t getLEDState();
        void setEffect(ColorEffect effect);
        ColorEffect getEffect();
        void setFadeCount(uint16_t count);
        void doLedAction();
        void handleLED();
        #pragma endregion
    private:
        ColorEffect _effect;
        uint8_t _pin;
        uint16_t _ledNr;
        uint8_t _ledState;
        uint8_t _btState;
        uint16_t _fadeCount;
        uint16_t _currentFadeCount;
        uint8_t _r;
        uint8_t _g;
        uint8_t _b;
        float _fadeFactor;
        uint32_t _color;
        int8_t _counter;
        void setLED();
};
#endif