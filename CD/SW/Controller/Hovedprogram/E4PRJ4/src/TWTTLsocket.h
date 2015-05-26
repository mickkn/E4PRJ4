/*
 * TWTTLsocket.h
 *
 *  Created on: 26/03/2015
 *      Author: Overgaard
 */

#ifndef TWTTLSOCKET_H_
#define TWTTLSOCKET_H_

#include "GPIOsocket.h"

class TWTTLsocket
{
public:
	TWTTLsocket(int msbPin, int lsbPin);
	~TWTTLsocket();
	int getPinValue(int pin) const;
	int getBabyconLevel(void);
	int msbPin_;
	int lsbPin_;
private:
};

#endif /* 2WTTLSOCKET_H_ */
