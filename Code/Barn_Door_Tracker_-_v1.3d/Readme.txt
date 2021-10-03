Code Readme.txt

This is the Ardunino IDE Sketch.  You can use this to compile your own binary, or just get the pre-compiled binary from the /Binaries directory.

To use this sketch in the Arduino IDE, you must install the following libraries.  Please read the information at the top of the sketch for 
for more information about the required libaries you must install to compile the code.

  + Get microprocessor / board definitions for setting up in Arduino IDE from: 
    https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#before-installing
     
  + Get Over The Air Updates (OTA) Libaries:
    - Using AsyncElegantOTA to do OTA Updates.
    - Running AsyncWebServer for better webpage handling - https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
    - Need to add libraries below to use these functions (download zip and install in Arduino IDE Libraries):
      ^ ESPAsyncWebServer.h: https://github.com/me-no-dev/ESPAsyncWebServer
      ^ AsyncElegantOTA.h: https://github.com/me-no-dev/AsyncTCP
      
