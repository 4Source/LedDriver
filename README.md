# Addressable LED Library 
## Supported MicroControllers
At the time of creation, the following micro controllers are supported/tested:
 * ESP8266
 * ESP32 (Planned)
 * Arduino (Planned)
 
If there are problems with your chipset contact me.

## Supported Led Comunication
### Pulse-Width Encoding 'WS2812 Protocol'
A type of PWM signal with a fixed timing. Which represents binary '0' or '1' using different on/off timings. 

### SPI (Planed)

## Planned Features

## Structure
### Enums
#### EOrder
``` c++
enum EOrder {
   RGB,
   RBG,
   GRB,
   GBR,
   BRG,
   BGR,
   RGBW,
   RGWB,
   RBGW,
   RBWG,
   RWGB,
   RWBG,
   GRBW,
   GRWB,
   GBRW,
   GBWR,
   GWRB,
   GWBR,
   BRGW,
   BRWG,
   BGRW,
   BGWR,
   BWRG,
   BWGR,
   WRGB,
   WRBG,
   WGRB,
   WGBR,
   WBRG,
   WBGR,
};
```
#### EBitSignificance
``` c++
enum EBitSignificance {
   LSB_First,
   MSB_First,
};
```
#### ELedType
``` c++
enum ELedType {
   RGB,
   RGBW,
   CCT,
   RGB_CCT,
};
```

### Classes
#### FrameController
``` c++
AddrLed *addrLed;
```

#### AddrLedController
``` c++
AddrLed *addrLed;
uint_8 *values;

// Pushes the cached values for the LEDs out to display them.
void show();
// Turns the LEDs off but keep the cached values.
void off();
// Clears the cached values and turn all LEDs off.
void clear();
// Set the Values for an specific LED, or an Set of LEDs in the cache.
void setColor();
// Clears the cached values.
void clearColor();
// Sets the Brightness of the LEDs to an Percentage value.
// percentage The value the brightness should be set to. 0-100
// nLed The number of LED witch should be changed. 0-n(maxNumbLeds - 1) Default = -1 (all LEDs)
// clampColorRatio Clamps the ratio between the color values.
// clampLedRatio Clamps the ratio between the LEDs
void setBrightness(uint8 percentage, int nLed = -1, bool clampColorRatio = true, bool clampLedRatio = true);
// Get Brightness of Color or LEDs as percentage.
// nLed The number of LED witch should be changed. 0-n(maxNumbLeds - 1) Default = -1 (all LEDs)
uint8 getBrightness(int nLed = -1);
```

#### virtual AddrLed
``` c++
EOrder colorOrder;
EBitSignificance bitOrder;
ELedType type;
uint8 dataPin;
uint8 clkPin;
```

#### virtual core
``` c++

```



















