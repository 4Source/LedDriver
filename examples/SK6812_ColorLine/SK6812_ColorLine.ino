//----------------------------------------------------
// File:		SK6812_ColorLine.ino
// Version:  	v0.1.3
// Change date:	26.05.2020
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------

#include <SK6812.h>
#include <addrLED.h>

//-Led
//DOut MC
uint8_t dataPin = 12;
//Connected Leds on data line
uint8_t ledQuantity = 3;	
//Red Value 0-255
uint8_t red = 0;
//Green Value 0-255
uint8_t green = 50;
//Blue Value 0-255
uint8_t blue = 100;
//White Value 0-255
uint8_t white = 100;

//Object of Addressable Led
SK6812 leds = SK6812(ledQuantity, dataPin);

//Setup
void setup(void) {
	Serial.begin(115200);
	while(!Serial);
	Serial.println();
	Serial.println("Ready!");
	
	leds.ColorLine(red, green, blue, white);
	leds.show();
}
//Loop
void loop() 
{
	
}
