//----------------------------------------------------
// File:	addrLED.h
// Version:  	v0.1.1
// Change date:	23.05.2020
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------
//Inspired by the blog of Josh Levine (https://wp.josh.com/)
#ifndef addrLED_h
#define addrLED_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <arduino.h>
#endif

#define getInternal(a) ((a >= 1000) ? (4) : (3))

#ifndef T0H
#define T0H	(F_CPU / 2500000)	//400 ns
#define T1H	(F_CPU / 1176470)	//850 ns
#define T0L	(F_CPU / 1176470)	//850 ns
#define T1L	(F_CPU / 2500000)	//400 ns
#define PERI (F_CPU / 800000) //1200 ns
#define RES (F_CPU / 20000)	//50.000 ns
#endif

#include "espPortReg.h"


class addrLED
{
  public: 
	enum _ColorOrder	//W=1 R=2 G=3 B=4 first is lowest weight
    {
      RGB = 432,
      GRB = 423,
      RGBW = 1432,
    };
	
  private:
    uint32_t aktivByte;
    uint16_t pixels;
	enum _ColorOrder order;
    uint8_t pin;
    uint8_t* colorBuffer;

    void setPixel( uint8_t, uint8_t, uint8_t);
	void setPixel( uint8_t, uint8_t, uint8_t, uint8_t);


  public:
	addrLED(uint16_t, enum _ColorOrder, uint8_t);

    void Single(uint8_t, uint8_t, uint8_t, uint16_t);
	void Single(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t);
    void Single(uint32_t, uint16_t);
	void Single(uint8_t*, uint16_t);

    void ColorLine(uint8_t, uint8_t, uint8_t);
	void ColorLine(uint8_t, uint8_t, uint8_t, uint8_t);
    void ColorLine(uint8_t*);

    void SpecificColor(uint8_t*);

	void show();

    uint8_t countPixel();
    uint8_t getPin();
    void setPin(uint8_t);

};
#endif
