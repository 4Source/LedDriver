//----------------------------------------------------
// File:	SK6812.h
// Version:  	v0.1.3
// Change date:	23.05.2020
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------
#ifndef SK6812_h
#define SK6812_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <arduino.h>
#endif

//SK6812 Timing
#define T0H	(F_CPU / 3333333)	//300 ns
#define T1H	(F_CPU / 1666666)	//600 ns
#define T0L	(F_CPU / 1111111)	//900 ns
#define T1L	(F_CPU / 1666666)	//600 ns
#define PERI (F_CPU / 800000) //1200 ns
#define RES (F_CPU / 12500)	//80.000 ns

#include "addrLED.h"

class SK6812 : public addrLED
{
  private:

  public:
	SK6812(uint16_t, uint8_t);
	SK6812(uint16_t, enum _ColorOrder, uint8_t);

};
#endif
