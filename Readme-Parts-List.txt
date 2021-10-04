Here are list of parts used to build the prototype.   Every part must meet certain specs and substitutes 
will work as long as they meet those specs.  Some parts are more specific (for example the microprocessor)
and while substitutes will work, you must verify every spec or possibly re-write/change the code and recompile
a new binary.

Initial build based on Nico Carver's Barn Door Tracker:
  * Video Here: https://www.youtube.com/watch?v=P_qqLA0WKJg 
  * Build Document Here (as of 2021): https://drive.google.com/file/d/1xJgKvlnahubcNM2y2DRTjEfHE8nX8fVD/view
  * Nico based his on the 'Sky and Telescope' magazine article in the April 1975 by George Haig of Glasgow, Scotland.
  * Since he was from Scotland, it is sometimes referred to as the Scotch Mount.  
  * More recently commonly referred to as a Barn Door Tracker.

NOTES:
1) These parts listed are not necessarily the cheapest place to obtain them.   It was decided to show the parts
   for the most common, easiest to get locations in the US, rather than numerous, smaller speciality stores.
2) It may be possible to find these exact parts or other, same spec parts from other locations like AliExpress,
   eBay, Arduino Speciality stores, etc.  Just make sure the requirements of alternative parts are the same.

////////////
// Amazon //
////////////
=== Please use this affiliate link so Nico Carver gets a small reward from Amazon - doesn't cost you anything! ===
=== Helps support Nico's work and make projects like this possible. Just click on link and then shop / checkout. ===
=== https://amzn.to/31rYb56 ===
* Microprocessor
  HiLetgo ESP-WROOM-32 ESP32 ESP-32S Development Board 2.4GHz Dual-Mode WiFi + Bluetooth Dual Cores
  (Specifically: ESP32, ESP-WROOM-32D chip, WiFi, Dual-Core, 5.0V / not 3.3v, Pre-Solder Pins, Specific pinouts)
  https://www.amazon.com/gp/product/B0718T232Z/
* Stepper Motor with Motor Controller
  You only need a single motor and controller, but it is typically the same price or cheaper to buy a 5 pcs set vs 1
  Additionally, some versions are not as reliable as others.  Elegoo has a good rating.
  28BYJ-48 ULN2003 5V Stepper Motor + ULN2003 Driver Board - 5 sets
  https://www.amazon.com/ELEGOO-28BYJ-48-ULN2003-Stepper-Arduino/dp/B01CP18J4A
* Breadboard and Jumpers Kit (not needed if you can solder and have small guage wire)
  Paxcoo 4 Pieces Breadboards Kit with 120 Pieces Jumper Wires
  https://www.amazon.com/Paxcoo-Breadboards-Arduino-Circboard-Prototyping/dp/B0727X6N9D/
* Battery Holder (with snap connector)
  Only need 1 but snap connector nice feature.  You can get a single with wire or if you can solder, without wires
  4 x 1.5V (6V) AA Battery Holder with 9V Type Snap Connector - 3+3 Pcs
  https://www.amazon.com/Battery-Holder-Connector-Plastic-Housing/dp/B07F43VWRQ/

///////////
// Lowes //
///////////
[NOTE: Or Menards if you have those near you ... NOTE: Home Depot doesn't tend to carry some full length threaded bolts.]

* Drive Bolt - x1 (must be: 1/4-20, Hex Head, Full Thread, and at least 3" long but 5-in better.)
  [NOTE: These are sometimes called Hex Head Tap Bolts.]
  Hillman 1/4-in x 5-in Zinc-Plated Coarse Thread Hex Bolt (2-Count) (Item #214117, Model #883150)
* Drive Nut for Large Gear - x1 (must be 1/4-20 hex)
  https://www.lowes.com/pd/Hillman-1-4-in-x-20-Zinc-Plated-Steel-Hex-Nut/3058547
* Tripod Nut - x1 (Most tripods have a 1/4-20 bolt.  Some might use a 3/8-16.  Verify with yours.)
  [Could buy adapter to use both: https://www.amazon.com/Standard-Adapter-Converter-Camcorder-Ballhead/dp/B07567PHSZ/]
  https://www.lowes.com/pd/Hillman-2-Count-1-4-in-Zinc-Plated-Standard-SAE-3-Prong-Tee-Nuts/3012529
* Hinge (Two Options)
  [Option 1: Buy two 2-inch hinges and mount one on top edge and one on bottom edge.  Must take time to align even with side.]
  https://www.lowes.com/pd/Gatehouse-2-in-Zinc-Mortise-Door-Hinge-2-Pack/50041810
  [Option 2: Buy a single piano hinge and use a hacksaw to cut it to length.  Made to be cut, but need saw to cut it.]
  https://www.lowes.com/pd/Gatehouse-Nickel-Piano-Cabinet-Hinge/1000486043
* Machine Screws for Motor x2 (need screw and nut)
  #6-32 Machine Screw x 1/2"
  https://www.lowes.com/pd/Hillman-6-32-x-1-2-in-Phillips-Drive-Machine-Screws-12-Count/3815411
* Machine Screws for Gear Bracket x4
  #6-32 Machine Screw x 1-1/2"
  https://www.lowes.com/pd/Hillman-6-32-x-1-1-2-in-Phillips-Drive-Machine-Screws-10-Count/3816093
* Machine Screws - #6 Lock Washers - x6 (x2 Motor and x4 Gear Bracket)
  https://www.lowes.com/pd/Hillman-4-Count-6-Standard-SAE-Split-Lock-Washer/999996210
* Barn Door Wood x2 (top and bottom)
  1x6 Pine Board - 6' long
  https://www.lowes.com/pd/Top-Choice-Common-1-in-x-6-in-x-6-ft-Actual-0-75-in-x-5-5-in-x-6-ft-Pine-Board/1000894238
  
  
  ///////////////////
  /// Assumptions ///
  ///////////////////
  * Have AA Batteries x4
  * Have a sturdy tripod to mount the Barn Door Tracker on.
  * Have a ball head for your camera.
    One option if you don't have one:
    https://www.ebay.com/itm/360-Degree-Mini-Tripod-Ball-Head-Ball-head-Compass-with-Quick-release-Plate-BK03-/112014868235
  * Have a camera and wide-field lens (DSLR and sub 100mm FL lens or a cell phone with long exposure capabilites)
  * Have some basic tools:
    - Saw to cut wood.
    - Measuring tape or ruler
    - Drill with some various drill bits
    - Screw drivers
    - Hammer (may not be needed)
    - Pliers (useful but not required)
