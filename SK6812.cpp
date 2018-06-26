#include "SK6812.h"
#include <stdlib.h>

SK6812::SK6812(uint16_t num_leds)
{
	_count_led = num_leds;
	_pixels = (RGBW *)malloc(_count_led * sizeof(RGBW));
}

SK6812::~SK6812()
{
	free(_pixels);
}

void SK6812::set_output(uint8_t pin)
{
	_pin_mask = digitalPinToBitMask(pin);
	_port = portOutputRegister(digitalPinToPort(pin));
	_port_reg = portModeRegister(digitalPinToPort(pin));
}

RGBW SK6812::get_rgbw(uint16_t index)
{
	RGBW px_value;

	if (index < _count_led) {
		px_value.r = _pixels[index].r;
		px_value.g = _pixels[index].g;
		px_value.b = _pixels[index].b;
		px_value.w = _pixels[index].w;
	}

	return px_value;
}

uint8_t SK6812::set_rgbw(uint16_t index, RGBW px_value)
{
	if (index < _count_led) {
		_pixels[index].r = px_value.r;
		_pixels[index].g = px_value.g;
		_pixels[index].b = px_value.b;
		_pixels[index].w = px_value.w;

		return 0;
	}

	return 1;
}

void SK6812::sync()
{
	*_port_reg |= _pin_mask;
	sendarray_mask((uint8_t *)_pixels, _count_led * sizeof(RGBW), _pin_mask, (uint8_t *)_port, (uint8_t *)_port_reg);
}