#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define T 1300          // Time(ns) Period min. required for full '0' or '1' bit code
#define T0H 300         // Time(ns) 'HIGH' min. required for '0' bit code
// #define T0L 800         // Time(ns) 'LOW' min. required for '0' bit code
#define T1H 600         // Time(ns) 'HIGG' min. required for '1' bit code
// #define T1L 200         // Time(ns) 'LOW' min. required for '1' bit code
#define TRST 80000      // Time(ns) 'LOW' min. required for Reset code

// Convert from nanoseconds to number of clock cycles 
#define NS(_NS) (((_NS * CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ) + 999) / 1000)

#define PIN 21
#define GPIO_OUTPUT_PIN_SEL  (1ULL<<PIN)
#define LEDS_COUNT 1
#define LED_TYPE 4 // RGBW

#define GPIO_OUT_REG 0x4 
#define GPIO_OUT_W1TS_REG 0x8
#define GPIO_OUT_W1TC_REG 0xC

void setColor(uint8_t *colorBuffer, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    colorBuffer[0] = g;
    colorBuffer[1] = r;
    colorBuffer[2] = b;
    colorBuffer[3] = w;
}

void show(uint8_t *colorBuffer)
{
    printf("show\n");

    uint32_t cycles_H;
    uint32_t cycles_T0H = NS(T0H);
	uint32_t cycles_T1H = NS(T1H);
	uint32_t cycles_TRST = NS(TRST);
	uint32_t cycles_T = NS(T); 
	uint32_t cycle_start = 0; 
    uint8_t mask = 0x80;
    uint32_t index = 0;
    uint32_t max = LEDS_COUNT * LED_TYPE;

    printf("cycles_T0H %li \n", cycles_T0H);
    printf("cycles_T1H %li \n", cycles_T1H);
    printf("cycles_TRST %li \n", cycles_TRST);
    printf("cycles_T %li \n", cycles_T);

    // Cycle throw the LED Colors
    while(index < max)    // !!!TEST CONDITION!!!
	{
        // Go throw each bit for one color byte
		while(mask > 0)
		{
            // Set Timeing depending should be '1' or '0' bit code
			if((colorBuffer[index] & mask)== mask)
			{
				cycles_H = cycles_T1H;
			}
			else
			{
				cycles_H = cycles_T0H;	
			}

            // Check enought cycles left for full period
            while((0xFFFFFFFF - esp_cpu_get_cycle_count()) < cycles_T){};
			
            // High Period
            // Set Pin High 
            gpio_set_level(PIN, 1);
            // Set the Cycle count start point
			cycle_start = esp_cpu_get_cycle_count();

            // Wait till High time cycle count get reached
			while((esp_cpu_get_cycle_count() - cycle_start) < cycles_H){};
            // Low Period
            // Set Pin Low 
			gpio_set_level(PIN, 0);
            // Wait till Period time cycle count get reached
            while((esp_cpu_get_cycle_count() - cycle_start) < cycles_T){};
			
            // Shift Mask for Next bit
			mask >>= 1;
		}
        // Reset Mask
		mask = 0x80;
        // Increace index to next color
		index++;
	}
    // Reset Period
    // Set pin Low
	gpio_set_level(PIN, 0);
    // Set the Cycle count start point
	cycle_start = esp_cpu_get_cycle_count();
    // Wait till Reset time cycle count get reached
    while((esp_cpu_get_cycle_count() - cycle_start) < cycles_TRST){};

}

void app_main(void)
{
    // Delay
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    // Setup Buffer
    uint8_t *colorBuffer;   // Buffer where colors stored 
    uint16_t bytes = LEDS_COUNT * LED_TYPE; // Bytes requierd 
	
	colorBuffer = (uint8_t*)calloc(bytes, sizeof(uint8_t));

    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t w = 0;

    // Fill Buffer
    setColor(colorBuffer, r, g, b, w);
	
    // Set GPIO as Output
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    // Console out that Setup is Finished
    printf("Setup Finish!\n");
    printf("v.0.0.1\n");
    // Log the Color
    printf("R: %i G: %i B: %i W: %i\n", colorBuffer[1], colorBuffer[0], colorBuffer[2], colorBuffer[3]);

    // Show the Color
    show(colorBuffer);

    // Delay
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
}
