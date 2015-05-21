/*
 * TWTTLsocket.cpp
 *
 * 4. Semester projekt forår 2015
 *
 *  Created on: 26/03/2015
 *      Author: Mick Kirkegaard & Poul Overgaard
 */

#include "TWTTLsocket.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <unistd.h>

using namespace std;

#define MAX_VALUE 30

TWTTLsocket::TWTTLsocket(int msbPin, int lsbPin)
{
	msbPin_ = msbPin;
	lsbPin_ = lsbPin;

	gpioExport(msbPin_);
	gpioExport(lsbPin_);

	usleep(EXPORTDELAY);	// Sleep for 400ms for the Export function

	gpioDirection(msbPin_, IN);
	gpioDirection(lsbPin_, IN);

}

TWTTLsocket::~TWTTLsocket() {
	gpioUnexport(msbPin_);
	gpioUnexport(lsbPin_);
}

int TWTTLsocket::getPinValue(int pin) const {
	char path[MAX_VALUE];
	char value_str[3];
	snprintf(path,MAX_VALUE,"/sys/class/gpio/gpio%d/value",pin);
	int fd = open(path, O_RDONLY);
	if(fd < 0) {
		printf("Failed to open GPIO value for reading\n");
		close(fd);
		cout << path << endl;
		return -1;
	}
	int err = read(fd,value_str,3);
	if(err < 0) {
		printf("Failed to read value!\n");
		close(fd);
		return -1;
	}

	close(fd);

	return atoi(value_str);
}


int TWTTLsocket::getBabyconLevel(void){

	int babyconLevel;

	int msb = getPinValue(msbPin_);
	int lsb = getPinValue(lsbPin_);

	if ((msb == 0) && (lsb == 0))
		{
		babyconLevel = 0;

		}
	else if ((msb == 0) && (lsb == 1))
		{
		babyconLevel = 1;

		}
	else if ((msb == 1) && (lsb == 0))
		{
		babyconLevel = 2;

		}
	else if ((msb == 1) && (lsb == 1))
		{
		babyconLevel = 3;

		}
	else
		{
		printf("Failed to read babyconLevel!\n");
		return -1;
		}

	return babyconLevel;

}


