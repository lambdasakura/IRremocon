/*
 * IRSignal.cpp
 *
 *  Created on: 2015/07/30
 *      Author: f9078010
 */

#include "IRSignal.hpp"

IRSignal::IRSignal() {
	this->tl = this->hl = this->ll = 0;
	this->ts = this->hs = this->ls = 65535;
}
