In order to compile the code, please note the following:
    1) These directions were written based on compiling under Windows 10 using Arduino IDE (ver 1.8.15)
       running on an ExpressIF ESP32 microprocessor with WiFi capabilities.  See the code and Parts List
       for exact processor specifications.
       Newer versions and on other platforms may be possible.
    2) Download the Arduino IDE from https://www.arduino.cc/en/software and follow the installation guide
       (Windows: https://www.arduino.cc/en/Guide/Windows)
    3) In order to compile ESP32 code, you must download and install the ExpressIF board definitions.  See the
       guide below for downloading and install them in Arduino IDE.  Just follow the directions for installing from
       Board Manager and no need to follow any OS specific directions:
       https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#before-installing
    4) The sketch uses Over the Air Updates (OTA), AKA - Updating the code via WiFi.  In particular, we are
       using the AsyncElegantOTA running an AsyncWebServer for better webpage handling. These functions
       requires several prerequisite libraries be installed for the code to compile.
       a) In Arduino IDE choose Sketch/Include Library/Manage Libraries/Filter for "AsyncElegantOTA" and install 
          the latest version.
       b) Download and add these two libraries: Download the zip file (look for Code/Download ZIP) from the 
          links below. Save each ZIP file to your computer (one for each link). Then in Arduino IDE under 
          Sketch, Include Library, Add .ZIP Libary and add each one:
          ^ ESPAsyncWebServer.h: https://github.com/me-no-dev/ESPAsyncWebServer
          ^ AsyncElegantOTA.h: https://github.com/me-no-dev/AsyncTCP

When you download the Automated Barn Door Tracker code, open it in Arduino IDE and it should compile.

