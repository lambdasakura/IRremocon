/*
 * IRReciever.cpp
 *
 *  Created on: 2015/07/30
 *      Author: f9078010
 */

#include "mraa.hpp"
#include "LapTimer.hpp"


#include "IRReciever.hpp"
#include "IRSignal.hpp"


int IRReciever::init_gpio() {

	this->ir_censor = new mraa::Gpio(this->censor_num);
	if (ir_censor == NULL) {
		return MRAA_ERROR_UNSPECIFIED;
	}
	mraa_result_t censor_response = ir_censor->dir(mraa::DIR_IN);
	if (censor_response != MRAA_SUCCESS) {
		mraa::printError(censor_response);
		return 1;
	}
	censor_response = ir_censor->useMmap(true);
	if (censor_response != MRAA_SUCCESS) {
		mraa::printError (censor_response);
		return 1;
	}
	return 0;
}

inline bool IRReciever::IR_on() {
	return (this->ir_censor->read() == 0);
}
inline bool IRReciever::IR_off() {
	return (this->ir_censor->read() == 1);
}

void IRReciever::analyze() {
	uint8_t i, b;
	uint16_t sp;
	IRSignal* signal = new IRSignal();
	LapTimer timer;

	timer.start();

	while (timer.time() < IR_DETECT) {
		if (IR_off()) {
			timer.start();
		}
	}
	while (IR_on())
		;

	signal->ldrh = timer.time() - IR_ADJUST;

	while (IR_off())
		;
	signal->ldrl = timer.time() - signal->ldrh;

	timer.restart(signal->ldrh + signal->ldrl);
	for (i = 0; i < IR_MAX; i++)
		for (b = 0; b < 8; b++) {

			while (IR_on())
				;
			signal->turn = timer.time() - IR_ADJUST;
			if (signal->turn > signal->tl)
				signal->tl = signal->turn;
			else if (signal->turn < signal->ts)
				signal->ts = signal->turn;

			while (IR_off()) {
				sp = timer.time() - signal->turn;
				if (sp > IR_STOP)
					goto EXIT;
			}
			timer.restart(signal->turn + sp);
			signal->sig[i] <<= 1;

			if (sp > IR_THRESH) {
				signal->sig[i] |= 1;
				if (sp > signal->hl)
					signal->hl = sp;
				else if (sp < signal->hs)
					signal->hs = sp;
			} else {
				signal->sig[i] &= 0xfe;
				if (sp > signal->ll)
					signal->ll = sp;
				else if (sp < signal->ls)
					signal->ls = sp;
			}
		}
	EXIT: signal->tail = 0; //millis();
	signal->scnt = i;
	signal->turn = (signal->tl + signal->ts) / 2;
	signal->sigh = (signal->hl + signal->hs) / 2;
	signal->sigl = (signal->ll + signal->ls) / 2;

	signal->aeha = (signal->ldrh < IR_FORM);
}
/*
 boolean IRReciever::analyze2() {
 uint8_t i, b;
 uint16_t sp;

 LAP_START();
 while (LAP_TIME < IR_DETECT) {
 if (IR_OFF)
 LAP_START();
 if (millis() - tail > IR_TIMEOUT)
 return false;
 }
 interval = (millis() - tail);
 interval -= IR_DETECT / 1000;

 while (IR_ON)
 ;
 while (IR_OFF)
 ;

 for (i = 0; i < IR_MAX; i++) {
 for (b = 0; b < 8; b++) {
 while (IR_ON)
 ;
 LAP_START();
 while (IR_OFF) {
 sp = LAP_TIME;
 if (sp > IR_STOP)
 goto EXIT;
 }
 sig[i] <<= 1;
 sig[i] |= (sp > IR_THRESH);
 }
 }
 EXIT: tail = millis();
 scnt = i;
 return true;
 }
 */
