/*
 * IRSignal.hpp
 *
 *  Created on: 2015/07/30
 *      Author: f9078010
 */

#ifndef IRSIGNAL_HPP_
#define IRSIGNAL_HPP_

#include <unistd.h>
#include <stdint.h>

#define IR_MAX 32

class IRSignal {
public:
	IRSignal(void);
	uint32_t lap;
	uint32_t tail;

	bool aeha;
	uint16_t ldrh, ldrl;
	uint16_t turn;
	uint16_t sigh, sigl;
	uint16_t tl, hl, ll;
	uint16_t ts, hs, ls;
	uint8_t scnt;
	uint8_t sig[IR_MAX];

	uint16_t interval;
};

#endif /* IRSIGNAL_HPP_ */
