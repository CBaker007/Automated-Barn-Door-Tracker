/*
Runs a single 28BYJ-48 stepper motors with AccelStepper Library.
NOTES:
 - Stepper Motor
     + Using the library you must download and install if not in contributed libraries: https://www.arduinolibraries.info/libraries/accel-stepper
     + The 28BYJ-48 draws 240mA per https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
     + The microprocessor should be able to support this, but they typically recommend a separate +5V power supply.
     + If we could use the MP power, we could run the whole system from a USB cable.
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
 - OTA Updates
      + Running AsyncWebServer for better webpage handling - https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
      + Following examples from AsyncElegantOTA to do OTA Updates.
      + Need to add libraries below to use these functions (download zip and install in Arduino IDE Libraries):
          ^ ESPAsyncWebServer.h: https://github.com/me-no-dev/ESPAsyncWebServer
          ^ AsyncElegantOTA.h: https://github.com/me-no-dev/AsyncTCP
*/

//GLOBAL DEFINITIONS

// Setup the pins between your MP and motor controller
// Must verify for your particular microprocessor board
// These are digital output pins on your mp
// Using HitLetGo ESP32-WROOM-D2 board
#define motor1Pin1  12    //IN1 UNL2003APG - 28BYJ48 pin 1
#define motor1Pin2  14    //IN2 UNL2003APG - 28BYJ48 pin 2
#define motor1Pin3  27    //IN3 UNL2003APG - 28BYJ48 pin 3
#define motor1Pin4  26    //IN4 UNL2003APG - 28BYJ48 pin 4
                          //Battery 5V     - 28BYJ48 (VCC)
                          //Battery GND    - 28BYJ48 (GND) 

// Must set the max speed of your stepper motor.
// This varies depending on battery, MP, stepper controller, and stepper motor
// If set to high, the lights on the motor controller will flash but the stepper will not move.
// In that case, lower until it starts moving.
// Good starting number is around 500 - 600.  Most low end systems won't get too much higher.
int STEPMAXSPEED = 600;

// Must calculate for your setup.  If using the same parts, should be very close.  
// In our setup, we want 1 revolution of output (3 input revs = 1 output rev) in 1 minute
// Should test before using to make sure correct for your setup.
// NOTE: Don't do any other functions on MP while running it.  Web browser access, LED on/off, etc all affect CPU load and hence RPM
long STEPSIDREAL = 102;   // Inital testing suggest 102 in our setup with a power supply.  How does battery affectd this?


// Global Variables

// Set Initial Stepper Motion
// Typically set to CCW/Up/Run in case user does not have or want to connect to webpage
char chrStepMotion = 'U';  // 'U'=Up/CCW/Run, 'D'=Down/CW, 'S'=Stop

// My IP for WiFi when acting as AP
// No need to change unless a conflict
IPAddress myIP(192,168,4,1); 
IPAddress myGATEWAY(192,168,4,255);
IPAddress mySUBNET(255,255,255,0);
char myHOSTNAME[7+1] = "tracker";  //  Using ESPmDNS to set a local DNS name of http://tracker.local so access via hostname or IP


/////////////////////////////////////////
// Should not have to change below here
/////////////////////////////////////////

// Software Version
char chrSOFTWAREVER[8] = "00.03.A";

// Running gear ratio of 3:1 so output is 3x this number
// Full rotation on stepper is 2038 per specs
// Some motors are not the same spec, so it may be different for a particular motor.  Not using this ATM.
#define FULLRotation 2038

// Stepper can be setup as full or half steps
#define FULLSTEP 4
#define HALFSTEP 8

// NOTE: The sequence 1-3-2-4 is required for proper sequencing of 28BYJ48
// Run in half steps
#include <AccelStepper.h>
AccelStepper stepper1(FULLSTEP, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);


/*
  Parts of WiFi Code....
  Developed from Sample for ExpressIF Docs (https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html#ap-example)

  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.
  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>   // Added for AsyncElegantOTA
#include <ESPAsyncWebServer.h>  // Added for AsyncElegantOTA - Download ZIP of code + add to IDE Libraries: https://github.com/me-no-dev/ESPAsyncWebServer
#include <AsyncElegantOTA.h>  // Added for AsyncElegantOTA - Download ZIP of code + add to IDE Libraries: https://github.com/me-no-dev/AsyncTCP


// Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
// My dev board has built in, not needed
// #define LED_BUILTIN 2   

// Set these to your desired credentials.
const char *ssid = "BarnDoorTracker";
const char *password = "NebulaPhotos";

// Setup Servers
AsyncWebServer server(80);

// Main Loop Counter
unsigned long ulongMainLoopCounter = 0;

void setup()
{
  // Debug Output to Serial
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting (Setup)...");

  
  // For Debugging - Flash Built-In LED during each loop
  // Initialize digital pin LED_BUILTIN as an output for using built-in LED
  pinMode(LED_BUILTIN, OUTPUT);

  //
  // Setup the Stepper Motor
  //
  stepper1.setMaxSpeed(STEPMAXSPEED);     // If set to high, motor will not move
  // stepper1.setAcceleration(50.0);      // Don't set this, we are using constant speed.
  stepper1.setSpeed(-STEPSIDREAL);        // We require neg number for CCW rotation (tracker moves up)
  // stepper1.moveTo(2038);               // For Debugging Only - 1 revolution CW is 2038 steps (neg for CCW) - Some disagreement about this.  Must test

  //
  // Setup the WiFi
  // (already setup above)
  // More info on ESP8266 Soft AP at https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
  
  // Debug Output to Serial
  Serial.println("Configuring WiFi in Soft AP Mode ...");

  // Set the WiFi in Soft AP Mode for the ESP8266
  WiFi.mode(WIFI_AP);
  // Set IP, Subnet, GW
  if (WiFi.softAPConfig(myIP, myGATEWAY, mySUBNET) == false) {
    Serial.println("Setting IP, Subnet, and Gateway failed.");
  }
  // If you remove the password parameter, their will not be a preshared key (WPA2-PSK) and the AP will be "open".  
  // We have a password-psk to secure it for star parties and group sessions.
  // Start WiFi in AP mode.
  WiFi.softAP(ssid, password);
  myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  //Setup Server Webpages
  server.on("/test", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "message received");
  });

  server.on("/LON", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED_BUILTIN, HIGH);                 // GET /H turns the LED on
    Serial.println("LED set to High (on).");         // Debug to serial output
    request->redirect("/");                          // back to homepage
  });

  server.on("/LOFF", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED_BUILTIN, LOW);                  // GET /L turns the LED off
    Serial.println("LED set to Low (off).");         // Debug to serial output
    request->redirect("/");                          // back to homepage
  });

  server.on("/RUN", HTTP_GET, [](AsyncWebServerRequest *request){
    chrStepMotion = 'U';                             // turn stepper to move up / run
    request->redirect("/");                          // back to homepage
  });

  server.on("/DOWN", HTTP_GET, [](AsyncWebServerRequest *request){
    // turn stepper to move down / reset  (BE CAREFUL NO SENSOR TO STOP WHEN ALL THE WAY DOWN - DON'T BURN MOTOR
    chrStepMotion = 'D';                             // turn stepper to move down / reset  
                                                     // (BE CAREFUL NO SENSOR TO STOP WHEN ALL THE WAY DOWN - DON'T BURN MOTOR
    request->redirect("/");                          // back to homepage
  });

  server.on("/STOP", HTTP_GET, [](AsyncWebServerRequest *request){
    chrStepMotion = 'S';                             // stop stepper
    request->redirect("/");                          // back to homepage
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    // set header and body
    response->addHeader("Server","Nebula Photos Barndoor Tracker");
    response->print("<!DOCTYPE html><html>");  
    response->print("<html><head>");
    response->print("<style>");
    response->print("body {background-color: black;}");
    response->print("h1 {color: white; font-size: 50px;}");
    response->print("h5 {color: white; font-size: 30px;}");
    response->print("p {color: white; font-size: 40px;}");
    response->print("a, a:link, a:visited {color:red;}");
    response->print(".f50 {color: white; font-size: 50px;}");
    response->print(".f30 {color: white; font-size: 30px;}");
    response->print(".mytable1{border-collapse:collapse;border-spacing:0;width:100%;table-layout:fixed;display:table}");
    response->print(".mytable1 tr{border-bottom:1px solid #ddd}");
    response->print(".mytable1{border:1px solid black}");
    response->print(".mytable1 tr:nth-child(odd){background-color:black}");
    response->print(".mytable1 tr:nth-child(even){background-color:black}");
    response->print(".mytable1 td,.mytable1 th{font-size: 20px; color: yellow; padding:8px 8px;display:table-cell;text-align:center;vertical-align:middle}");
    response->print(".mytable1 th:first-child,.mytable1 td:first-child{padding-left:16px}");
    response->print(".mytable2 {width: 100%; border:10px solid black;}");
    response->print(".mytable2 tr {background: #2B289E; border-color: black; border: 15px solid black;}");
    response->print(".mytable2 td, .mytable2 th {font-size: 60px; font-color: white; text-align:center; border: 15px solid black;}");
    response->print(".mytable3{border-collapse:collapse;border-spacing:0;width:100%;table-layout:fixed;display:table}");
    response->print(".mytable3{border:1px solid black}");
    response->print(".mytable3 tr{border-bottom:1px solid #ddd}");
    response->print(".mytable3 td,.mytable1 th{font-size: 16px; color: white; padding:8px 8px;display:table-cell;text-align:center;vertical-align:middle}");
    response->print(".mytable3 td a, .mytable3 td a:link, .mytable3 td a:visited {color:white;}");
    response->print("</style><title>Nebula Photos Barndoor Tracker - Main Page</title></head>");
    response->print("<body><br>");
  
    // page title
    response->print("<center>");
    response->print("<div class='f50'>Nebula Photos Barndoor Tracker<br></div>");
    response->print("</center>");
              
    // the main body
    response->print("<table class='mytable1'><tr>");
    response->print("<td>Max Step Speed: ");
    response->printf("%d",STEPMAXSPEED);
    response->print("</td>");
    response->print("<td>Sidreal Speed: ");
    response->printf("%d",STEPSIDREAL);
    response->print("</td>");
    response->print("<td>Motion State: ");
    response->printf("%c",chrStepMotion);
    response->print("</td>");
    response->print("</tr><tr>");
    response->print("<td>WiFi Mode: ");
    response->print("AP");
    response->print("</td>");
    response->print("<td>WiFi SSID: ");
    response->printf("%s",ssid);
    response->print("</td>");
    response->print("<td>Tracker IP: ");
    response->printf("%u.%u.%u.%u",myIP[0],myIP[1],myIP[2],myIP[3]);
    response->print("</td>");
    response->print("</tr></table>");
              
    // the content of the HTTP response follows the header:
    response->print("<table class='mytable2'>");
    response->print("<tr>");
    response->print("<td><a href=\"/LON\">LED On</a></td>");
    response->print("<td><a href=\"/LOFF\">LED Off</a></td>");
    response->print("</tr>");
    response->print("<tr>");
    response->print("<td><a href=\"/RUN\">RUN (CCW)</a></td>");
    response->print("<td><a href=\"/DOWN\">Down (CW)</a></td>");
    response->print("</tr>");
    response->print("<tr>");
    response->print("<td><a href=\"/STOP\">STOP</a></td>");
    response->print("<td><a href=\"/STOP\">STOP</a></td>");
    response->print("</tr>");
    response->print("</table>");

    // footer
    // copyright, update link, version, etc
    response->print("<table class='mytable3'>");
    response->print("<tr>");
    response->printf("<td align=\"left\">Stations Connected: %d</td>", WiFi.softAPgetStationNum());
    response->printf("<td align=\"center\">%s (<a href=\"/update\">Update Software</a>)</td>", chrSOFTWAREVER);
    response->print("<td align=\"right\">Written By / Copyright: <a href=\"mailto:netspec.inc@gmail.com\">Christopher Baker</a></td>");
    response->print("</tr>");
    response->print("</table>");

    // end header and body
    response->print("</body></html>");
    // send the response
    request->send(response);
  });

  server.on("/SET", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    //List all parameters
    int params = request->params();
    for(int i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
//      char *strPName = p->name().c_str();
//      char *strPValue = p->value().c_str();     
      Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
      response->printf("<center>Parameter Name: %s</center>", p->name().c_str());
      response->printf("<center>Parameter Value: %s</center>", p->value().c_str());

      // Figure out what mode we are in and set speed
      if ( strcmp((p->name().c_str()),"sidreal") ) {
        STEPSIDREAL = p->value().toInt();         // Set new sidreal speed.
        response->printf("<center>Set %s to %i</center>", p->value().c_str(), p->value().toInt());
      }
    }
    request->send(response);
  });

//    if(p->isFile()){ //p->isPost() is also true
//      Serial.printf("FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
//      } else if(p->isPost()){
//        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
//        } else {
//          Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
//          }
//    }
//  }

  // Start ElegantOTA for OTA updates via Web - http://<myIP>/update
  AsyncElegantOTA.begin(&server);    // Start ElegantOTA

  // Start the webserver
  server.begin();
  Serial.println("Web Server started");
  
}


void loop()
{

  // Figure out what mode we are in and set speed
  switch (chrStepMotion) {
    case 'U':
      // Move Up Direction / Run - CCW in our setup
      stepper1.setSpeed(-STEPSIDREAL);                         // Set to sidreal speed.
      //Serial.println("Rotate CCW (Run) at Sidreal speed.");  // Debug to serial output
      break;
    case 'D':
      // Move Down Direction - CW in our setup
      stepper1.setSpeed(STEPMAXSPEED);                          // Set to max speed for testing.  Move down.
      //Serial.println("Rotate CW (down) at Max speed.");       // Debug to serial output
      break;
    case 'S':
      // Stop Moving
      stepper1.setSpeed(0);                                     // Set to zero to stop it rotating.
      //Serial.println("Stop all Rotation.");                   // Debug to serial output
      break;
    default:
      // DEFAULT - Move Up Direction / Run - CCW in our setup
      stepper1.setSpeed(-STEPSIDREAL);                          // Set to sidreal speed.
      //Serial.println("DEFAULT TO - CCW (Run) at Sidreal.");   // Debug to serial output
      break;
  }

  // Step/Run stepper motor
  // Ideally move this to its own task / core so these processes don't affect the critical timing of this process.
  stepper1.runSpeed();

  // Check to see if an OTA Update should be initiated
  AsyncElegantOTA.loop();

}
