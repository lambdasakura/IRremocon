/*
 * IRReciever.hpp
 *
 *  Created on: 2015/07/30
 *      Author: f9078010
 */

#ifndef IRRECIEVER_HPP_
#include "IRSignal.hpp"
#include "mraa.hpp"
#include "LapTimer.hpp"

#define IRRECIEVER_HPP_

#define IR_DETECT 2000
#define IR_STOP 3360
#define IR_THRESH 805
#define IR_FORM 6500
#define IR_ADJUST 105
#define IR_TIMEOUT 100 //mS

class IRReciever {
private:
	mraa::Gpio* ir_censor;
	int censor_num = 46;

public:

	int init_gpio();
	void analyze(void);
	bool analyze2(void);
	bool IR_on();
	bool IR_off();
};

#endif /* IRRECIEVER_HPP_ */
