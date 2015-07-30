/*
 * LapTimer.hpp
 *
 *  Created on: 2015/07/30
 *      Author: f9078010
 */

#ifndef LAPTIMER_HPP_
#define LAPTIMER_HPP_

#include <sys/time.h>

void busy_wait(signed long wait_time);

class LapTimer {
public:
	void start();
	void restart(long);
	unsigned long time();
private:
	long lap;
};

#endif /* LAPTIMER_HPP_ */
