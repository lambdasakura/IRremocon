/*
 * IRShotter.hpp
 *
 *  Created on: 2015/07/30
 *      Author: f9078010
 */

#ifndef IRSHOOTER_HPP_
#define IRSHOOTER_HPP_

#include "IRSignal.hpp"
#include "mraa.hpp"

#define IR_STOP 3360

class IRShooter {
private:
	static const int led_num = 45;

	mraa::Gpio* ir_led;
	void shot(uint32_t, bool);

public:

	int init_gpio();
	void control(IRSignal*);
};

#endif /* IRSHOOTER_HPP_ */
