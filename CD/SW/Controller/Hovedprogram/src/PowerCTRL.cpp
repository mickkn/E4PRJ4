/*
 * PowerCTRL.cpp
 *
 * 4. Semester projekt forår 2015
 *
 *  Created on: 26/03/2015
 *      Author: Mick Kirkegaard & Poul Overgaard
 */

#include "PowerCTRL.h"

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

PowerCTRL::PowerCTRL(int pin)
{
	pin_ = pin;
	gpioExport(pin_);
	usleep(EXPORTDELAY);	// Sleep for 400ms for the Export function
	gpioDirection(pin_, OUT);
}

PowerCTRL::~PowerCTRL() {
	gpioUnexport(pin_);
}

int PowerCTRL::power(int value) {
	char path[MAX_VALUE];
	static const char s_values_str[] = "01";
	snprintf(path,MAX_VALUE, "/sys/class/gpio/gpio%d/value",pin_);
	int fd = open(path, O_WRONLY);
	if(fd < 0) {
		printf("Failed to open GPIO value for writing\n");
		close(fd);
		cout << path << endl;
		return -1;
	}
	int err = write(fd,&s_values_str[0 == value ? 0 : 1],1);
	if(err < 0) {
		printf("Failed to write value!\n");
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}


