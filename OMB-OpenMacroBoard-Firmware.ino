#include <Adafruit_NeoPixel.h>
#include "Keyboard.h"
#include "ButtonClass.h"

// Buttons
#define BT_CNT    10
#define TRG_LIM   2
#define STX       2 // Start of text
#define ETX       3 // End of text
#define SO        14 // ShiftOut
#define SI        15 // ShiftIn
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

Button buttons[BT_CNT];


void setup() {  
  // LED
  leds.begin();
  leds.show();
  leds.setBrightness(100); 
  // Buttons
  for(int i = 0; i < BT_CNT; i++)
  {
    buttons[i] = Button(btPins[i], i, &leds);
    btCommand[i] = String(i);
  }
  btCommand[9] = "test";
  // DEBUG LED
  buttons[0].setEffect(Button::ColorEffect::off);
  buttons[1].setEffect(Button::ColorEffect::solid);
  buttons[2].setEffect(Button::ColorEffect::onPush);
  buttons[3].setEffect(Button::ColorEffect::onIdle);
  buttons[4].setEffect(Button::ColorEffect::toggle);
  buttons[5].setEffect(Button::ColorEffect::fade);
  buttons[5].setFadeCount(100);
  buttons[6].setEffect(Button::ColorEffect::invFade);
  buttons[6].setFadeCount(200);
  buttons[7].setEffect(Button::ColorEffect::remote);
  buttons[8].setEffect(Button::ColorEffect::off);
  buttons[9].setEffect(Button::ColorEffect::off);

  Keyboard.begin();
  // Serial
  Serial.begin(115200);
}

void loop() {
  updateButtons();
  checkSerial();
  leds.show();
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

void updateButtons()
{
  for(int i = 0; i < BT_CNT; i++)
  {
    if(buttons[i].Poll())
    {
      doAction(i);
    }
    buttons[i].handleLED();
  }
}

void doAction(int actionNr)
{
    Keyboard.print(btCommand[actionNr]);  
    
    int pos = 0;
    String cmd = btCommand[actionNr];
    String send = "";
    for(pos = 0; pos < cmd.length(); pos++)
    {
      if(cmd[pos] == char(STX))// start of text
      {
        send += cmd[pos]; // add char to sendstring
      }
      else if(cmd[pos] == char(ETX))
      {
        Keyboard.print(send);
        send = "";
      }
      else if(cmd[pos] == char(SI))
      {
        Keyboard.press(cmd[++pos]);
      }
      else if(cmd[pos] == char(SO))
      {
        Keyboard.release(cmd[++pos]);
      }
      else
      {
        Keyboard.write(cmd[pos]);
      }
    }
    Keyboard.releaseAll();
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
