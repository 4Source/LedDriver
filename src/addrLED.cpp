//----------------------------------------------------
// File:	addrLED.cpp
// Version:  	v0.1.5
// Change date:	30.05.2020
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------
#include "addrLED.h"

static uint32_t _getCycleCount(void) __attribute__((always_inline));
static inline uint32_t _getCycleCount(void) {
  uint32_t ccount;
  __asm__ __volatile__("rsr %0,ccount":"=a" (ccount));
  return ccount;
}
addrLED::addrLED(uint16_t countPixel, enum _ColorOrder ledOrder, uint8_t gpio_pin)
{
	#if defined (__AVR_ATtiny85__)
	if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
	#endif
	
	pixels = countPixel;
	pin = gpio_pin;
	aktivByte = 0;
	order = ledOrder;
	
	uint16_t bytes = pixels * Internal(order);
	
	colorBuffer = (uint8_t*)calloc(bytes, sizeof(uint8_t));
	pinMode(pin, OUTPUT);
}

void addrLED::setPixel( uint8_t r, uint8_t g , uint8_t b )  
{	
	uint32_t orderbuffer = order;
	for(uint8_t i = 0; i < Internal(order); i++)
	{
		uint8_t rest = orderbuffer % 10;
		orderbuffer /= 10;
		
		if(rest == 2)	//Red
		{
			colorBuffer[aktivByte + i] = r;
			// Serial.print("red: "); Serial.println(r);
		}
		else if(rest == 3)	//Green
		{
			colorBuffer[aktivByte + i] = g;
			// Serial.print("green: "); Serial.println(g);
		}
		else if(rest == 4)	//Blue
		{
			colorBuffer[aktivByte + i] = b;
			// Serial.print("blue: "); Serial.println(b);
		}
		else if(rest == 1)		//White
		{
			colorBuffer[aktivByte + i] = 0;
			// Serial.print("white: "); Serial.println(0);
		}
		else 	
		{
			colorBuffer[aktivByte + i] = 0;
			// Serial.println("-");
		}
	}
}
void addrLED::setPixel(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{	
	uint32_t orderbuffer = order;
	for(uint8_t i = 0; i < Internal(order); i++)
	{
		uint8_t rest = orderbuffer % 10;
		orderbuffer /= 10;
		
		if(rest == 2)	//Red
		{
			colorBuffer[aktivByte + i] = r;
			// Serial.print("red: "); Serial.println(r);
		}
		else if(rest == 3)	//Green
		{
			colorBuffer[aktivByte + i] = g;
			// Serial.print("green: "); Serial.println(g);
		}
		else if(rest == 4)	//Blue
		{
			colorBuffer[aktivByte + i] = b;
			// Serial.print("blue: "); Serial.println(b);
		}
		else if(rest == 1)		//White
		{
			colorBuffer[aktivByte + i] = w;
			// Serial.print("white: "); Serial.println(w);
		}
		else 	
		{
			colorBuffer[aktivByte + i] = 0;
			// Serial.println("-");
		}
	}
}

//Color for one Pixel
void addrLED::Single(uint8_t r , uint8_t g , uint8_t b, uint16_t pixelNr) 
{ 
	if(pixelNr < pixels)
	{
		aktivByte = pixelNr * Internal(order);
		setPixel( r , g , b );
	}
}
void addrLED::Single( uint8_t r , uint8_t g , uint8_t b, uint8_t w, uint16_t pixelNr ) 
{ 
	if(pixelNr < pixels)
	{
		aktivByte = pixelNr * Internal(order);
		setPixel( r , g , b , w);
	}
}
void addrLED::Single(uint32_t pixel, uint16_t pixelNr)
{
	if(Internal(order) == 4 )
	{
		uint8_t w = (uint8_t)pixel;
		uint8_t b = (uint8_t)(pixel>>=8);
		uint8_t g = (uint8_t)(pixel>>=8);
		uint8_t r = (uint8_t)(pixel>>=8);
				
		Single(r, g, b, w, pixelNr);
	}
	else
	{
		uint8_t b = (uint8_t)pixel;
		uint8_t g = (uint8_t)(pixel>>=8);
		uint8_t r = (uint8_t)(pixel>>=8);
		
		Single(r, g, b, pixelNr);
	}
}
void addrLED::Single(uint8_t *buffer, uint16_t pixelNr)
{
	uint8_t r = *buffer;
	uint8_t g = *(buffer + 1);
	uint8_t b = *(buffer + 2);
	if(Internal(order) == 4)
	{
		uint8_t w = *(buffer + 3);
		Single(r, g, b, w, pixelNr);
	}
	else
	{
		Single(r, g, b, pixelNr);
	}
}

//Color for all pixels
void addrLED::ColorLine( uint8_t r , uint8_t g , uint8_t b ) 
{ 
	for(aktivByte = 0; aktivByte < pixels * 3; aktivByte += 3)
	{
		setPixel(r, g, b);
	}
}
void addrLED::ColorLine(uint8_t r , uint8_t g , uint8_t b, uint8_t w) 
{ 
	for(aktivByte = 0; aktivByte < pixels * 4; aktivByte += 4)
	{
		setPixel(r, g, b, w);
	}
}
void addrLED::ColorLine(uint8_t *buffer)
{
	uint8_t r = *buffer;
	uint8_t g = *(buffer + 1);
	uint8_t b = *(buffer + 2);
	if(Internal(order) == 4)
	{
		uint8_t w = *(buffer + 3);
		ColorLine(r, g, b, w);
	}
	else
	{
		ColorLine(r, g, b);
	}
}

// specific Color for each pixel
void addrLED::SpecificColor(uint8_t *buffer)
{
	uint8_t internals = Internal(order);
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t w;
	
	for(aktivByte = 0; aktivByte < pixels * internals; aktivByte += internals)
	{
		r = *buffer;
		buffer++;
		g = *buffer;
		buffer++;
		b = *buffer;
		buffer++;
		if(internals == 4)
		{
			w = *buffer;
			buffer++;
			
			setPixel(r, g, b, w);
		}
		else
		{
			setPixel(r, g, b);
		}
	}
}
void addrLED::show() 
{
	noInterrupts();
	uint32_t timeH;
	uint32_t timeL;
	uint32_t time_ret = RES;
	uint32_t time_peri = PERI; 
	uint32_t cycle_start = 0; 
	uint32_t cycle_now = 0;
	uint8_t mask = 0x80;
	uint32_t index = 0;
	uint32_t max = pixels * Internal(order);
	
	while(index < max)
	{
		while(mask > 0)
		{
			if((colorBuffer[index] & mask)== mask)
			{
				timeH = T1H;
				timeL = T1L;
			}
			else
			{
				timeH = T0H;
				timeL = T0L;
	
			}
			while(((cycle_now = _getCycleCount()) - cycle_start) < time_peri);
			
			PIN_OUT_SET(pin);
			cycle_start = cycle_now;
			while(((cycle_now = _getCycleCount()) - cycle_start) < timeH);
			PIN_OUT_CLEAR(pin);
			while(((cycle_now = _getCycleCount()) - cycle_start) < timeL);
			
			mask >>= 1;
		}
		mask = 0x80;
		index++;
	}
	PIN_OUT_CLEAR(pin);
	cycle_start = cycle_now;
	while(((cycle_now = _getCycleCount()) - cycle_start) < time_ret);
	interrupts();
}
void addrLED::showSerial() 
{
	uint32_t index = 0;
	uint32_t max = pixels;
	
	while(index < max)
	{
		Serial.print(" val="); Serial.print(colorBuffer[index]);
		index++;

		
	}
	Serial.println(" Reset");
}

uint8_t addrLED::countPixel()
{
	return pixels;
}
uint8_t addrLED::getPin()
{
	return pin;
}
uint16_t addrLED::getOrder()
{
	return order;
}
void addrLED::setPin(uint8_t gpio_pin)
{
	pin = gpio_pin;
	pinMode(pin, OUTPUT);
}
String addrLED::getLedType()
{
	return "Basic Addressable LED";
}
