//----------------------------------------------------
// File:	espPortReg.h
// Version:  	v0.1.0
// Change date:	22.05.2020
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------
#ifndef espPortReg_h
#define espPortReg_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <arduino.h>
#endif

//GPIO
#define PIN_OUT(n) (WRITE_PERI_REG( 0x60000300, (n)))
#define PIN_OUT_SET(n) (WRITE_PERI_REG( 0x60000304, (1<<(n)) ))
#define PIN_OUT_CLEAR(n) (WRITE_PERI_REG( 0x60000308, (1<<(n)) ))


#endif
