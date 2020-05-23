//----------------------------------------------------
// File:	SK6812.cpp
// Version:  	v0.1.0
// Change date:	23.05.2020
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------
#include "SK6812.h"

SK6812::SK6812(uint16_t countPixel, uint8_t gpio_pin) : addrLED(countPixel, addrLED::RGBW, gpio_pin) {}

