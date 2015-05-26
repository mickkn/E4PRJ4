/*
 * GPIOsocket.cpp
 *
 * 4. Semester projekt forår 2015
 *
 *  Created on: 17/03/2015
 *      Author: Mick Kirkegaard & Poul Overgaard
 */

#include "GPIOsocket.h"
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

int gpioExport(int pin) {

	// Export
	//--------------
	#define BUFFER_MAX 3
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open export for writing!\n");
		close(fd);
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return 0;
}

int gpioUnexport(int pin) {
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open unexport for writing!\n");
		close(fd);
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

int gpioDirection(int pin, int dir) {
	static const char s_directions_str[]  = "in\0out";

	#define DIRECTION_MAX 35
	char path[DIRECTION_MAX];

	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	int fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio direction for writing!\n");
		close(fd);
		return(-1);
	}

	int err = write(fd, &s_directions_str[IN == dir ? 0 : 3], (IN == dir ? 2 : 3));
	if(err < 0) {
		fprintf(stderr, "Failed to set direction!\n");
		close(fd);
		return(-1);
	}

	close(fd);
	return(0);
}

