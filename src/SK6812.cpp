//----------------------------------------------------
// File:	SK6812.cpp
// Version:  	v0.1.5
// Change date:	30.05.2020
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------
#include "SK6812.h"

SK6812::SK6812(uint16_t countPixel, uint8_t gpio_pin) : addrLED(countPixel, addrLED::GRBW, gpio_pin) {}

SK6812::SK6812(uint16_t countPixel, enum _ColorOrder ledOrder, uint8_t gpio_pin) : addrLED(countPixel, ledOrder, gpio_pin) {}


String SK6812::getLedType()
{
	return "SK6812";
}
