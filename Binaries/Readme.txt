Readme.txt

This is the pre-compiled binary for the ESP32 micropocessor and pinouts as described in the sketch:

- Board Info
     + Written for the ESPRESSIF ESP32.
     + Get microprocessor / board definitions for setting up in Arduino IDE from 
       https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#before-installing
     + ESP32-WROOM-32D Specs (Specific board datasheet for the board developed on): http://www.hiletgo.com/ProductDetail/1906566.html)
         ^ WiFi = 802.11 b/g/n; BR/EDR + Bluetooth LE v4.2
         ^ 32 GPIO; Op Temp: -40C to 85C;
         ^ 4 MB Flash; 520KB SRAM; 448KB ROM; 0KB PSRAM; 240 MHz
         ^ MP Datasheet: https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf
      + There are several specific Expressif ESP32 MP Chips (like ESP32-WROOM-32D) but a whole slew of development boards
        all with different pinouts and voltages.  It is very important that your adjust your particular wiring to reflect this,
        as well as setting the pin references in this file below.
      + This may run on future releases for the ESP32-WROOM-32 chip (E, F, etc.) but if you have issues, should re-compile a version
        specific for your version of the chip.
        
      + This is the specific board this binary was developed and tested on though other boards with the same specs should work:
        https://www.amazon.com/gp/product/B0718T232Z/
         - HiLetgo ESP-WROOM-32 ESP32 ESP-32S Development Board 
         - 2.4GHz Dual-Mode WiFi + Bluetooth 
         - Dual Cores Microcontroller Processor 
         - Integrated with Antenna RF AMP Filter AP STA
         - For Arduino IDE
         
