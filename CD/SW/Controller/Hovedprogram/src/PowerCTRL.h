/*
 * PowerCTRL.h
 *
 *  Created on: 26/03/2015
 *      Author: Mick
 */

#ifndef POWERCTRL_H_
#define POWERCTRL_H_

#include "GPIOsocket.h"

class PowerCTRL
{
public:
	PowerCTRL(int pin);
	~PowerCTRL();
	int power(int value);
private:
	int pin_;
};

#endif /* PowerCTRL_H_ */
