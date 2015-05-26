/*
 * Betjeningspanel.cpp
 *
 * 4. Semester projekt forår 2015
 *
 *  Created on: 17/03/2015
 *      Author: Mick Kirkegaard & Poul Overgaard
 */

#include "Betjeningspanel.h"
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

Betjeningspanel::Betjeningspanel(int ledOnOff, int ledMan, int ledWifi, int butOnOff, int butMan) {

	ledOnOff_ = ledOnOff;
	ledMan_ = ledMan;
	ledWifi_ = ledWifi;
	butOnOff_ = butOnOff;
	butMan_ = butMan;

	gpioExport(ledOnOff_);
	gpioExport(ledMan_);
	gpioExport(ledWifi_);
	gpioExport(butOnOff_);
	gpioExport(butMan_);

	usleep(EXPORTDELAY);	// Sleep for 400ms for the Export function

	gpioDirection(ledOnOff_, OUT);
	gpioDirection(ledMan_, OUT);
	gpioDirection(ledWifi_, OUT);
	gpioDirection(butOnOff_, IN);
	gpioDirection(butMan_, IN);
}

Betjeningspanel::~Betjeningspanel() {
	gpioUnexport(ledOnOff_);
	gpioUnexport(ledMan_);
	gpioUnexport(ledWifi_);
	gpioUnexport(butOnOff_);
	gpioUnexport(butMan_);
}

int Betjeningspanel::setLedValue(int pin, int value) {
	char path[MAX_VALUE];
	static const char s_values_str[] = "01";
	snprintf(path,MAX_VALUE, "/sys/class/gpio/gpio%d/value",pin);
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

int Betjeningspanel::getButValue(int pin) const {
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

