#include "ButtonClass.h"


#define TRIGGER_LIMIT   2
Button::Button()
{
    // Dummy
}
Button::Button(uint8_t pin, uint16_t ledNr, Adafruit_NeoPixel* stripRef)
{
    _pin = pin;
    strip = stripRef;
    _ledNr = ledNr;
    _effect = off;
    _ledState = 0;
    setColor(255,255,255);
    pinMode(_pin, INPUT_PULLUP);
}

uint8_t Button::Poll()
{
    _btState = digitalRead(_pin);
    handleLED();
    if(_btState == 0 && _counter >= 0)
        _counter++;
    else if(_btState == 1)
        _counter = 0;
    if(_counter >= TRIGGER_LIMIT)
    {
        _counter = -10;
        doLedAction();
        return 1;
    }
    else return 0;
}

#pragma region LED-related
// set the led color from r g b values
void Button::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    _color = Adafruit_NeoPixel::Color(r,g,b);
    _r = r;
    _g = g;
    _b = b;
    setLED();
}
// set the led color from a hue value
void Button::setColor(uint16_t hue)
{
    _color = Adafruit_NeoPixel::ColorHSV(hue);
    _r = (uint8_t)(_color >> 16),
    _g = (uint8_t)(_color >>  8),
    _b = (uint8_t)_color;
    setLED();
}
// returns the 32bit led color
int Button::getColor()
{
    return _color;
}
// sets led on or off
void Button::setLEDState(uint8_t state)
{
    _ledState = state;
    setLED();
}
// returns current led state
uint8_t Button::getLEDState()
{
    return _ledState;
}
// set the effect to use for the button
void Button::setEffect(ColorEffect effect)
{
    _effect = effect;
    switch(_effect)
    {
        case solid:
        case invFade:
        case onIdle:
            setLEDState(1);
            break;
        default:
            setLEDState(0);
            break;
    }
}
// returns the current effect on the button
Button::ColorEffect Button::getEffect()
{
    return _effect;
}
// triggers the led effect if applicable
void Button::doLedAction()
{
    switch(_effect)
    {
        case off:
            setLEDState(0);
            break;
        case solid:
            setLEDState(1);
            break;
        case toggle:
            setLEDState(!_ledState);
            break;
        case fade:
            _currentFadeCount = 0;
            setLEDState(1);
            break;
        case invFade:
            _currentFadeCount = 0;
            setLEDState(0);
            break;
        default:
            break;
    }
}
// set the number of cycles a fade takes from 100% to 0%
void Button::setFadeCount(uint16_t count)
{
    _fadeCount = count;
    _fadeFactor = 1.0f/(float)count;
}


void Button::setLED()
{
    if(_ledState)
        strip->setPixelColor(_ledNr, _color);
    else
        strip->setPixelColor(_ledNr, 0);
}
void Button::handleLED()
{
    switch(_effect)
    {
        case onIdle:
            if(_btState) setLEDState(1);
            else setLEDState(0);
            break;
        case onPush:
            if(_btState) setLEDState(0);
            else setLEDState(1);
            break;
        case fade:
            if(_currentFadeCount < _fadeCount)
            { 
                uint8_t r = round(_r * (1 - _currentFadeCount * _fadeFactor));
                uint8_t g = round(_g * (1 - _currentFadeCount * _fadeFactor));
                uint8_t b = round(_b * (1 - _currentFadeCount * _fadeFactor)); 
                strip->setPixelColor(_ledNr, r, g, b);
                _currentFadeCount++;
            }
            else setLEDState(0);
            break;
        case invFade:
            if(_currentFadeCount < _fadeCount)
            { 
                uint8_t r = round(_r * (_currentFadeCount * _fadeFactor));
                uint8_t g = round(_g * (_currentFadeCount * _fadeFactor));
                uint8_t b = round(_b * (_currentFadeCount * _fadeFactor)); 
                strip->setPixelColor(_ledNr, r, g, b);
                _currentFadeCount++;
            }
            else setLEDState(1);
            break;
        default:
            break;
    }
}

#pragma endregion
