#include <Adafruit_NeoPixel.h>
#include "Keyboard.h"
#include "ButtonClass.h"

// Buttons
#define BT_CNT    10
#define TRG_LIM   2
int btPins[BT_CNT] = {A6, A11, A7, A8, A9, A10, 5, 13, A0, A1};
uint8_t btStates[BT_CNT] = {1};
int btCounter[BT_CNT] = {0};
uint8_t btTrigger[BT_CNT] = {0};
String btCommand[BT_CNT] = {""};

// LED 
#define LED_PIN    11
Adafruit_NeoPixel leds(BT_CNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t btCol[BT_CNT] = {0};
uint8_t btLedState[BT_CNT] = {0};




void setup() {  
  // LED
  leds.begin();
  leds.show();
  leds.setBrightness(100);
  // DEBUG LED
  for(int i = 0; i < BT_CNT; i++)
  {
    btCol[i] = leds.Color(255-25*i,25*i,0);
  }
  
  
  // Buttons
  for(int i = 0; i < BT_CNT; i++)
  {
    pinMode(btPins[i], INPUT_PULLUP);
    btCommand[i] = String(i);
  }
  Keyboard.begin();
  // Serial
  Serial.begin(115200);
}

void loop() {
  readButtons();
  doActions();
  checkSerial();
  delay(5);
}

void checkSerial()
{
  String buff = "";
  while (Serial.available() > 0)
  {
    char recv = Serial.read();
    if(recv != '\n') buff += recv;
    else ParseCommand(buff);
  }
}

void ParseCommand(String cmdStr)
{
  if(cmdStr.length() > 3)
  {
    String command = cmdStr.substring(0,3);
    if(command == "rgb")
    {
      int led = (cmdStr.substring(3, 6)).toInt();
      int r = (cmdStr.substring(6, 9)).toInt();
      int g = (cmdStr.substring(9, 12)).toInt();
      int b = (cmdStr.substring(12, 15)).toInt();
      setButtonColor(led, r, g, b);
    }
    else if(command == "hue")
    {
      int led = (cmdStr.substring(3, 6)).toInt();
      int hue = (cmdStr.substring(6, 11)).toInt();
      setButtonColor(led, hue);
    }
  }
}

void readButtons()
{
  for(int i = 0; i < BT_CNT; i++)
  {
    int state = digitalRead(btPins[i]);
    if(state == 0 && btCounter[i] >= 0)
      btCounter[i]++;
    else if (state == 1)
      btCounter[i] = 0;
    if(btCounter[i] >= TRG_LIM && btCounter[i] > 0) 
    {
      btTrigger[i] = 1;
      btCounter[i] = -1;
    }
    else btTrigger[i] = 0;
  }
}

void doActions()
{
  for(int i = 0; i < BT_CNT; i++)
  {
    if(btTrigger[i])
    {
      Keyboard.print(btCommand[i]);  
      btLedToggle(i);
    }
  }
}

void btLedToggle(int ledNr)
{
  if(btLedState[ledNr])
  {
    setButtonLed(ledNr, 0);
  }
  else
  {
    setButtonLed(ledNr, 1);
  }
}

void setButtonColor(int ledNr, int hue)
{
  if(ledNr < BT_CNT)
  {
    btCol[ledNr] = leds.ColorHSV(hue);
  }
}

void setButtonColor(int ledNr, int r, int g, int b)
{
  if(ledNr < BT_CNT)
  {
    btCol[ledNr] = leds.Color(r,g,b);
  }
}

void setButtonLed(int ledNr, int state)
{
  if(state)
  {
    btLedState[ledNr] = 1;
    leds.setPixelColor(ledNr, btCol[ledNr]);
  }
  else
  {
    btLedState[ledNr] = 0;
    leds.setPixelColor(ledNr, 0);
  }
  leds.show();
}
