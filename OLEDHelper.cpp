#include "OLEDHelper.h"
#include "Arduino.h"

OLED::OLED()
{
    _u8g = 0;
    _dummy = true;
}

OLED::OLED(U8GLIB* screen)
{
    _u8g = screen;
    _dummy = false;
}

void OLED::showSplash(uint8_t major, uint8_t minor)
{
  CHECK_VALID
  for(int i = _u8g->getHeight(); i >= ((_u8g->getHeight()-12) >> 1); i--)
  {
    _u8g->firstPage(); 
    do
    {
        _u8g->setFont(u8g_font_courB14r);
        _u8g->setFontRefHeightExtendedText();
        _u8g->setDefaultForegroundColor();
        _u8g->setFontPosTop();
        char chrArr[20];
        snprintf(chrArr, 20, "O.M.B. V%d.%d", major, minor);
        int posX = (_u8g->getWidth() - (_u8g->getStrWidth(" ") * 11)) >> 1;
        _u8g->drawStr(posX,i,chrArr);
    } while( _u8g->nextPage() );
  }
}

void OLED::showVersion(uint8_t major, uint8_t minor)
{
    CHECK_VALID
    _u8g->firstPage(); 
    do
    {
        _u8g->setFont(u8g_font_courB14r);
        _u8g->setFontRefHeightExtendedText();
        _u8g->setFontPosTop();
        char chrArr[8];
        snprintf(chrArr, 8, "V%d.%d", major, minor);
        int posX = (_u8g->getWidth() - (_u8g->getStrWidth(" ") * 4)) >> 1;
        int posY = (_u8g->getHeight()-12) >> 1;
        _u8g->setColorIndex(1);
        _u8g->drawBox(posX-2,posY, (_u8g->getStrWidth(" ") * 4) + 1, 14);
        _u8g->setColorIndex(0);
        _u8g->drawStr(posX,posY,chrArr);
    } while( _u8g->nextPage() );
}

void OLED::blank()
{
    CHECK_VALID
    _u8g->firstPage(); 
    do {
    } while( _u8g->nextPage() );
}

void OLED::mainScreen(uint8_t brg)
{
    CHECK_VALID
    blank();
    char buff[25];
    _u8g->firstPage(); 
    do {
        snprintf(buff, 25, "O.M.B. LED:%d%%", int(brg/2.55));
        _u8g->setFont(u8g_font_5x8r);
        _u8g->setFontRefHeightExtendedText();
        _u8g->setFontPosTop();
        _u8g->drawStr(0,0,buff);
        _u8g->drawLine(0,9, _u8g->getWidth(), 9);
        _u8g->drawLine(32,0,32,8);
    } while( _u8g->nextPage() );
}

void OLED::showText(char* text, uint8_t count)
{
    CHECK_VALID
    _u8g->firstPage();
    do {
        _u8g->setFont(u8g_font_courB14r);
        _u8g->setFontRefHeightExtendedText();
        _u8g->setFontPosTop();
        int posX = (_u8g->getWidth() - (_u8g->getStrWidth(" ") * count)) >> 1;
        int posY = (_u8g->getHeight()-12) >> 1;
        _u8g->drawStr(posX,posY,text);
    } while( _u8g->nextPage());
}