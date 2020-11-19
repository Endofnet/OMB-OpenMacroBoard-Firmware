# OMB-OpenMacroBoard-Firmware

This is the official firmware for the [OMB-OpenMacroBoard](https://github.com/Endofnet/OMB-OpenMacroBoard "OMB on GitHub"). <br/>
It allows the O.M.B. to work as a basic Macro-Keyboard with custom, stringbased commands and rudimentary LED control.<br/>
<br/>

## Installation
<br/>

### I have a board that already contains a bootloader

To "install" the firmware you just need an [O.M.B. Baseboard](https://github.com/Endofnet/OMB-OpenMacroBoard "OMB on GitHub") and the [Arduino IDE](https://www.arduino.cc/en/software "Arduino software page") or VS-Code extension. The O.M.B. uses the Arduino-Bootloader so you can just select "Arduino/Genuino Micro" in the Boards tab and you can upload the sketch.<br/>
<br/>
<br/>

### I have a fresh / unprogrammed board
<br/>
For this you will need an AVR-Programmer or another Arduino to act as a programmer.<br/>
In the reference image you can find the pins you need.

![OMB-Pinout](https://github.com/Endofnet/OMB-OpenMacroBoard-Firmware/raw/main/pinout_reference.png "O.M.B. Pinout Reference")
After connecting the Programmer/Arduino it's recommendet to upload the Arduino bootloader with the Ardino-IDE and the follow the above steps for boards with bootloader. This makes it easy to update in the future. <br/>
But you can also just upload the sketch directly.

## Usage

The O.M.B. firmware uses a string based protocol on a virtual serial port to set button functions, leds and effects. The executing part of the firmware is using the Arduino Keyboard library, so the O.M.B. acts like a Keyboard to your computer. To setup everything graphically there is [O.M.B. Host](https://github.com/Endofnet/OMB-OpenMacroBoard-Host "OMB Host on GitHub") but if you wish you can also manually send commands or develop your own software.<br/>
The commands need to be terminated with a newline character **\n**. If a parameter is 3 characters long in the description, then it must be 3 characters long when sending, using leading 0 if necessary.

  * **rgbNNNRRRGGGBBB** sets a buttons color to an r, g, b value  
  * **hueHHH** sets a buttons color to a given hue value with saturation and value on max.
  * **effEEE** the effect number the button should use.
    * 0 = off
    * 1 = on
    * 2 = toggle on push
    * 3 = on push on and then fade to off
    * 4 = on push off then fade to on
    * 5 = light on when pushed
    * 6 = light off when pushed
    * 7 = light remotecontrolled
  * **brgXXX** the global led brightness
  * **cmdNNNS-S** the keystrokes / text to execute / print on buttonpush
  * **loa** load the settings from eeprom
  * **sav** save settings to eeprom
  * **clr** clear eeprom
  * **dmp** dump current settings to string
  * **rst** resets the O.M.B.

<br/>
<br/>

  * **NNN** Button/LED number. 
  * **RRR** red component of an rgb color. From 0 to 255.
  * **GGG** green component of an rgb color. From 0 to 255.
  * **BBB** blue component of an rgb color. From 0 to 255.
  * **HHH** a colors hue value. From 0 to 255.
  * **EEE** the effect value
  * **XXX** From 0 to 255.
  * **S-S** Commandstring