# Automated-Barn-Door-Tracker

Astrophotography typically starts with a mount or tracker that can counteract the Earth's rotation to allow long exposure photography. The price for an entry level, commercial tracker capable of holding a DSLR camera can be $350+ USD. DIY trackers (typically called Barn Door Trackers) made of two pieces of wood, a bolt, and hand power to rotate a nut to drive the tracker have been developed. Nico Carver (YouTube Nebula Photos) has such a device with plans and how-to use it here: https://www.youtube.com/watch?v=P_qqLA0WKJg.

The goal of this project is to create a DIY Barn Door Tracker based on Nico's general design and power it with an inexpensive set of electronics (microcontroller, stepper motor, and a motor controller). Additionally, use WiFi to help control the device via a web browser. The end goal would be to create reliable, wide-field DIY Automated Barn Door Tracker for under $50 USD.

Current / near future plans are:
1) Utilize dual core microprocessors to off-load all tracking functions to a dedicated core.
2) Allow for customization and user-defined settings for fine tuning the tracking rates, WiFi settings, and UI. 
3) Use an inexpensive accelerometer to further refine the speed of the motor to more precisely match the Earth's rotation (closed loop system).
4) Utilize an inexpensive ESP32 camera to aid in polar alignment.
