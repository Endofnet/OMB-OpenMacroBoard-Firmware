#include "ButtonClass.h"

#include "Adafruit_NeoPixel.h"

#define TRIGGER_LIMIT   2

Button::Button(uint8_t pin, uint8_t ledNr)
{
    _pin = pin;
    _ledNr = ledNr;
    _effect = off;
    _ledState = 0;
    _color = Adafruit_NeoPixel::Color(255,255,255);
}

uint8_t Button::Poll()
{
    uint8_t state = digitalRead(_pin);
    if(state == 0 && _counter >= 0)
        _counter++;
    else if(state == 1)
        _counter = 0;
    if(_counter >= TRIGGER_LIMIT)
    {
        _counter = -1;
        return 1;
    }
    else return 0;
}

#pragma region LED-related
void Button::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    _color = Adafruit_NeoPixel::Color(r,g,b);
    setLED();
}
void Button::setColor(uint16_t hue)
{
    _color = Adafruit_NeoPixel::ColorHSV(hue);
    setLED();
}
int Button::getColor()
{
    return _color;
}
void Button::setLEDState(uint8_t state)
{
    _ledState = state;
    setLED();
}
void Button::setLED()
{
    if(_ledState)
        strip->setPixelColor(_ledNr, _color);
    else
        strip->set
}
#pragma endregion
