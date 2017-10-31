# A320 Radio Management Arduino Firmware

++ For simulation use only! ++
## Description
Simulation software for the A32x RMP made by FSPCB. 

Current features
* Simple ClickEncoder for chosing frequencies
* VHF 1-3
* HF1-2/AM
* Stby NAV Mode
* VOR
* ILS
* MLS
* ADF with BFO

Communicated features:
Due to the lack of support of more modes in SimConnect the following values are transmitted to the sim software:
* VHF1 Active => Com1 Active
* VHF1 Standby => Com1 Standby
* VHF2 Active => Com2 Active
* VHF2 Standby => Com2 Standby
* VOR Active => NAV1 Active


## Installation
Hardware requirements:
* FSPCB RMP PCB correctly soldered
* Pro Micro with ATMega32u4 chip (ebay "pro micro")

Software requirements:
* Highly recommended: <a href="http://blog.zakkemble.co.uk/avrdudess-a-gui-for-avrdude/" target="_blank">AVRDUDESS</a>

#### Steps:

1. Download the .hex release file <a href="https://github.com/fspcb/A320RadioManagementPanel/releases/">here</a>

2. Download and install AVRDUDESS from the link above

3. Start AVRDUDESS and setup the following settings:

* **Programmer:** Atmel AppNote AVR109 Boot Loader

* **MCU:** ATmega32U4 (exactly this one - not U2 not 328)

* **Flash:** Click the "..." and chose the .hex file 

* **Port:** To find out the right COM port (the right one isn't in the list) you need to reset the Arduino (via button if present, or by shortening the RST to the GND pin). The arduino will enter the bootloader for 8 seconds (hear the usb ping). During this 8s the correct COM port will be available in the list. Select it.


* To start the flashing, enter the bootloader again (reset the arduino) and (within the 8s) press **GO** under the "Flash" button.
Many magic things will happen on the black logscreen. 

If something like this is displayed at the bottom:
```
avrdude.exe: reading on-chip flash data:

Reading | ################################################## | 100% 0.33s

avrdude.exe: verifying ...
avrdude.exe: 20002 bytes of flash verified

avrdude.exe done.  Thank you.
```
Flashing was successful.

If any error message appears, retry adjusting the Com Port and reset the arduino again. If you cannot get it to work at all. Just send in an <a href="https://github.com/fspcb/A320RadioManagementPanel/issues">issue</a>

## Development

If you 'd like to contribute to the RMP software - just fork it and send in a pull request. That's what open source is for :-)

Using Visual Studio with Visual Micro is strongly recommended for development. 