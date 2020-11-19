#include <Adafruit_NeoPixel.h>
#include "Keyboard.h"
#include "ButtonClass.h"
#include <EEPROM.h>

#pragma region Buttons
// Buttons
#define BT_CNT    10
#define TRG_LIM   2
#define STXT       String("~t#") // Start of text
#define ETXT       String("#t~") // End of text
#define BTP        String("#b~") // Button press
#define BTR        String("~b#") // Button release
int btPins[BT_CNT] = {A6, A11, A7, A8, A9, A10, 5, 13, A0, A1};
String btCommand[BT_CNT] = {""};
Button buttons[BT_CNT];
#pragma endregion

#pragma region LED
// LED 
#define LED_PIN    11
Adafruit_NeoPixel leds(BT_CNT, LED_PIN, NEO_GRB + NEO_KHZ800);
#pragma endregion

void setup() {  
  // LED
  leds.begin();
  leds.show();
  leds.setBrightness(127); 
  alive();
  
  // Buttons
  for(int i = 0; i < BT_CNT; i++)
  {
    buttons[i] = Button(btPins[i], i, &leds);
    buttons[i].setEffect(Button::ColorEffect::solid);
    btCommand[i] = String(i);
  }
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

void alive()
{
  leds.fill(leds.Color(255,0,0), 0, BT_CNT);
  leds.show();
  delay(250);
  leds.fill(leds.Color(0,255,0), 0, BT_CNT);
  leds.show();
  delay(250);
  leds.fill(leds.Color(0,0,255), 0, BT_CNT);
  leds.show();
  delay(250);
  leds.fill(leds.Color(0,0,0), 0, BT_CNT);
  leds.show();
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
    else if(command == "eff")
    {
      int btNr = (cmdStr.substring(3, 6)).toInt();
      uint8_t effNr = (cmdStr.substring(6, 8)).toInt();
      if(btNr < BT_CNT)
      {
        buttons[btNr].setEffect((Button::ColorEffect)effNr);
      }
    }
    else if(command == "brg")
    {
      int brightness = (cmdStr.substring(3, 6)).toInt();
      leds.setBrightness(brightness);
      leds.show();
    }
    else if(command == "cmd")
    {
      int btNr = (cmdStr.substring(3, 6)).toInt();
      String btCmd = (cmdStr.substring(6));
      if(btNr < BT_CNT)
      {
        btCommand[btNr] = btCmd;
      }
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
    int pos = 0;
    String cmd = btCommand[actionNr];
    String send = "";
    bool textMode = false;
    for(pos = 0; pos < cmd.length(); pos++)
    {
      if((cmd.substring(pos, pos + 3) == STXT) && (!textMode))// check start of text when not in textmode
      {
        textMode = true;
        pos += 3;
        send += cmd[pos]; // add char to sendstring
      }
      else if((cmd.substring(pos, pos + 3) == ETXT) && (textMode)) // check end of text when in textmode
      {
        textMode = false;
        pos += 3;
        Keyboard.print(send);
        send = "";
      }
      else if(textMode)
      {
        send += cmd[pos];
      }
      else if(cmd.substring(pos, pos + 3) == BTP)
      {
        pos += 3;
        
        Keyboard.press(cmd[pos]);
      }
      else if(cmd.substring(pos, pos + 3) == BTR)
      {
        pos += 3;
        Keyboard.release(cmd[pos]);
      }
      else
      {
        Keyboard.write(cmd[pos]);
      }
    }
    Keyboard.releaseAll();
}

void setButtonColor(int ledNr, int hue)
{
  if(ledNr < BT_CNT)
  {
    buttons[ledNr].setColor(hue);
  }
}

void setButtonColor(int ledNr, int r, int g, int b)
{
  if(ledNr < BT_CNT)
  {
    buttons[ledNr].setColor(r, g, b);
  }
}

#pragma region eeprom
void saveSettings()
{

}

void loadSettings()
{

}
#pragma endregion