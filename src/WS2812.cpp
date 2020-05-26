//----------------------------------------------------
// File:	WS2812.cpp
// Version:  	v0.1.3
// Change date:	23.05.2020
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------
#include "WS2812.h"

WS2812::WS2812(uint16_t countPixel, uint8_t gpio_pin) : addrLED(countPixel, addrLED::GRB, gpio_pin) {}

WS2812::WS2812(uint16_t countPixel, enum _ColorOrder ledOrder, uint8_t gpio_pin) : addrLED(countPixel, ledOrder, gpio_pin) {}