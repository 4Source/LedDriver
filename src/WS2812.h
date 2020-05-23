//----------------------------------------------------
// File:	WS2812.h
// Version:  	v0.1.0
// Change date:	23.05.2020
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------
#ifndef WS2812_h
#define WS2812_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <arduino.h>
#endif

//WS2812 Timing
#define T0H	(F_CPU / 2500000)	//400 ns
#define T1H	(F_CPU / 1176470)	//850 ns
#define T0L	(F_CPU / 1176470)	//850 ns
#define T1L	(F_CPU / 2500000)	//400 ns
#define PERI (F_CPU / 800000) //1200 ns
#define RES (F_CPU / 20000)	//50.000 ns

#include "addrLED.h"

class WS2812 : public addrLED
{
   public:
	WS2812(uint16_t, uint8_t);
};
#endif
