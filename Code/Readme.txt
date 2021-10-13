Automated Barn Door Tracker - Compling Code Readme.txt

By default, to program an Ardunio microprocessor, you must flashed with code onto it.  Typically, to
flash the code you must either:
    A) Have the code complied by a compiler (Arduino IDE in our case) and then immediately flashed 
       onto the microprocessor by the same compiler, or 
    B) Have special code placed on the microprocessor that allows pre-compiled code to be downloaded 
       and flashed directly onto it. (Flashing pre-complied code on a blank microprocessor without
       this special code already on it, is possible but it takes a bit of effort.

This project has code built into all versions that allows this direct flashing of pre-compiled code,
called "Over the Air" (OTA) flashing via WiFi.  So once you get the first copy flashed onto the 
microprocessor, you don't have to complie and flash future versions.  Instead you can download new
pre-compiled versions from here and flash it directly from the Automated Barn Door Tracker (ABDT) 
webpage on the microprocessor.

But your new microprocessor must have an initial version of the ABDT code flashed onto it and that still
requires compiling / flashing using the Arduino IDE.

In order to compile and flash the ABDT code in the Arduino IDE, please note the following before proceeding:
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
    4) You need to install the stepper library we use.  In Arduino IDE choose Sketch/Include Library/Manage 
       Libraries/Filter for "AccelStepper" and install the latest version.
    5) The sketch uses Over the Air Updates (OTA), AKA - Updating the code via WiFi.  In particular, we are
       using the AsyncElegantOTA running an AsyncWebServer for better webpage handling. These functions
       requires several prerequisite libraries be installed for the code to compile.
       a) In Arduino IDE choose Sketch/Include Library/Manage Libraries/Filter for "AsyncElegantOTA" and install 
          the latest version.
       b) Download and add these two libraries: Download the zip file (look for Code/Download ZIP) from the 
          links below. Save each ZIP file to your computer (one for each link). Then in Arduino IDE under 
          Sketch, Include Library, Add .ZIP Libary and add each one:
          ^ ESPAsyncWebServer.h: https://github.com/me-no-dev/ESPAsyncWebServer
          ^ AsyncElegantOTA.h: https://github.com/me-no-dev/AsyncTCP
     6) You must change the microprocessor we are using in the board definitions.
        In the Arduino IDE, under Tool, Board, select "NodeMCU-32S" (under ExpressIF) if using the recommended
        microprocessor from the parts list.

When you download the Automated Barn Door Tracker code, open it in Arduino IDE and it should compile.

