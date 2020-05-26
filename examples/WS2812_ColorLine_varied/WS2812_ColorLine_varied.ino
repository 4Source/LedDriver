//----------------------------------------------------
// File:		WS2812_ColorLine_varied.ino
// Version:  	v0.1.3
// Change date:	26.05.2020
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------

#include <WS2812.h>
#include <addrLED.h>

//-Led
//DOut MC
uint8_t dataPin = 12;
//Connected Leds on data line
uint8_t ledQuantity = 3;	
//Number of differnet colors
const uint8_t numb = 5;
//Red Value 0-255
uint8_t red[numb] = 	{0, 100, 0, 0, 100};
//Green Value 0-255
uint8_t green[numb] = 	{0, 0, 100, 0, 100};
//Blue Value 0-255
uint8_t blue[numb] = 	{0, 0, 0, 100, 100};

//Object of Addressable Led
WS2812 leds = WS2812(ledQuantity, dataPin);
//Counter
uint8_t i = 0;


//Setup
void setup(void) {
	Serial.begin(115200);
	while(!Serial);
	Serial.println();
	Serial.println("Ready!");
	
}
//Loop
void loop() 
{
	if(i >= numb)
	{
		i=0;
	}
	leds.ColorLine(red[i], green[i], blue[i]);
	leds.show();
	Serial.print("Frame number: "); Serial.println(i);
	delay(1000);
	i++;
}