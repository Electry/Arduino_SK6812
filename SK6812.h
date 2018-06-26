#ifndef SK6812_H_
#define SK6812_H_

#include <util/delay.h>
#include <stdint.h>
#include <Arduino.h>

#ifndef F_CPU
#define  F_CPU 16000000UL
#endif

struct RGBW {
	uint8_t g; // 0
	uint8_t r; // 1
	uint8_t b; // 2
	uint8_t w; // 3
};

class SK6812 {
public: 
	SK6812(uint16_t num_led);
	~SK6812();
	
	void set_output(uint8_t pin);
	
	RGBW get_rgbw(uint16_t index);
	uint8_t set_rgbw(uint16_t index, RGBW px_value);

	void sync();
	
private:
	uint16_t _count_led;
	RGBW *_pixels;

	const volatile uint8_t *_port;
	volatile uint8_t *_port_reg;
	uint8_t _pin_mask;

	void sendarray_mask(uint8_t *array, uint16_t length, uint8_t pinmask, uint8_t *port, uint8_t *portreg);

};

#endif /* SK6812_H_ */
