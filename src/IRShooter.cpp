/*
 * IRShooter.cpp
 *
 *  Created on: 2015/07/30
 *      Author: f9078010
 */

#include "IRShooter.hpp"
#include "LapTimer.hpp"


int IRShooter::init_gpio() {
	this->ir_led = new mraa::Gpio(this->led_num);
	if (ir_led == NULL) {
		return MRAA_ERROR_UNSPECIFIED;
	}
	mraa_result_t led_response = ir_led->dir(mraa::DIR_OUT);
	if (led_response != MRAA_SUCCESS) {
		mraa::printError(led_response);
		return 1;
	}
	led_response = ir_led->useMmap(true);
	if (led_response != MRAA_SUCCESS) {
		mraa::printError(led_response);
		return 1;
	}

	ir_led->write(0);
	return 0;
}

void IRShooter::shot(uint32_t t, bool aeha) {
	LapTimer myTimer;
	myTimer.start();

	while (myTimer.time() < t) {
		this->ir_led->write(1);
		if (aeha) { //38.02kHz, 50.2%
			busy_wait(13);
		} else { //37.93kHz, 34.6%
			busy_wait(9);
		}
		this->ir_led->write(0);
		if (aeha) {
			busy_wait(13);
		} else {
			busy_wait(17);
		}
	}
}

void IRShooter::control(IRSignal* signal) {
	uint8_t i;
	uint8_t b;

	shot(signal->ldrh, signal->aeha);
	busy_wait(signal->ldrl);

	for (i = 0; i < signal->scnt; i++) {
		for (b = 0; b < 8; b++) {
			shot(signal->turn, signal->aeha);
			if ((signal->sig[i] & (0x80 >> b)))
				busy_wait(signal->sigh);
			else
				busy_wait(signal->sigl);
		}
	}
	shot(signal->turn, signal->aeha);
	busy_wait (IR_STOP);
}
