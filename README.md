# OMB-OpenMacroBoard-Firmware

This is the official firmware for the [OMB-OpenMacroBoard](https://github.com/Endofnet/OMB-OpenMacroBoard "OMB on GitHub"). <br/>
It allows the O.M.B. to work as a basic Macro-Keyboard with custom, stringbased commands and rudimentary LED control.<br/>
<br/>

## Installation
<br/>

### I have a board that already contains a bootloader
<br/>
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
