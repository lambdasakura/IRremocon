/*
 * LapTimer.cpp
 *
 *  Created on: 2015/07/30
 *      Author: f9078010
 */

#include <unistd.h>
#include <sys/time.h>
#include "LapTimer.hpp"

void busy_wait(signed long wait_time) {
	timeval tv;
	gettimeofday(&tv, NULL);
	signed long start_time = tv.tv_usec;
	signed long current_time = start_time;
	while (current_time - start_time < wait_time) {
		current_time = gettimeofday(&tv, NULL);
	};
}

void LapTimer::start() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	this->lap = tv.tv_usec;
}

void LapTimer::restart(long t) {
	this->lap += t;
}

unsigned long LapTimer::time() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_usec - this->lap);
}
