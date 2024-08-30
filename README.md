COMPONENTS
1.	ESP32-C3 with 0.42 OLED
a.	Link for product
2.	Lipo Battery Rechargeable Lithium Polymer ion Battery 
a.	I like to buy the gas station disposable vapes, and steal the battery out of it
3.	Switch 3 prong
4.	Button – button cap
5.	Flash light led and reflector
6.	Battery Charging Board with Battery Protection BMS 5V Micro USB 1A 186 50 Charge Module
7.	Connection wires

3D PRINTING STUFF
1.	Elagoo PLA+
2.	Top half –
 
3.	Rail Connection base left side clamp –
 
4.	right side clamp –
 

HARDWARE
1.	4  m2 screws
2.	2 bolts and nuts m4
3.	USBC cable 
4.	Botton cap – you can print this too

SOFTWARE
1.	Arduino IDE
a.	Libraries for ESP32-C3 dev module
b.	U8g2lib
2.	https://lopaka.app/ - this is to make graphics 
3.	Slicer software
	


STEP ONE: PRINT IT
Bring the STL files into your preferred slicer program, I Used Anycubic Slicer as I have a Anycubic Kobra 3 printer. 

My Print Setting:
60 to 100% infill – this is up to you, more infill = more durability. 
Normal PLA+ settings for your printer
I use organic supports from build plate only
Print orientation 
-leave it as it is in the STL it should be in the proper rotation see images for reference. You can change the base/rail connection orientation, as I have not yet found the best one. 

 
STEP TWO: ASSEMBLY
I like to place my components in the frame without securing them. 

From here I measure my wires to cut proper lengths and so as not to have too much wire inside. 

Follow this Diagram  

Rechargeable battery :
Solder the batter + to recharge board bat+

Solder battery – to recharge board bat-

Battery power to ESP32-C3:
Solder wire to out + on the recharge board 

Solder the other side of that wire to the left side of the Switch
Solder a wire to the middle prong of the Switch
The other side of the middle prong wire, Solder to the BAT pin on the esp32 

Solder wire to the Out- on the recharge board

Solder a black wire onto the Grnd Pin on the Esp32. This is so we can add multiple connections to the grnd pin. 

Slice the black wire so you have 3 open connection points

Solder the other side of that wire to the black grnd wire at the connection point closest to the ESP32

Now it’s a rechargeable battery powered esp32!

Lets Add a button and a Flashlight!
First lets add a wire coming off the 3V pin on the ESP32. This will allow for multiple connection points.

Next, solder a 10kOhm resistor to one pin on your button. 
Solder a wire to the other side of the resistor.
Solder the other side of the resistor wire to the second connection on the ground wire. 
Solder a wire on the same button pin as the resistor
solder that wire to pin 1 on the ESP 32
Now, the pin diagonally across from the button pin the resistor and wire are connected to…
Solder a red wire
Connect the other side of the red wire to one connection point of the 3.3V pin
Voila you have a button on a rechargeable Esp32 c3

If you want a flashlight follow this, if not skip ahead to the next section.
Flashlight;
This one about the same as the button. If you don’t have a flashlight light with a little board connected to it, just add a 10kohm resistor to your led + leg
Connect a red wire to the + pin, usually the one in the middle of the board
Connect the other side to a connection point of the Pin 7
Now connect the – pin of the led to a black wire, usually the post on a board or the outside circle.
Connect the other side to a connection point on the ground wire on the esp32.
Now you have a flashlight that will be able to be toggled on and off via Bluetooth

All right that’s everything Time to Code!






