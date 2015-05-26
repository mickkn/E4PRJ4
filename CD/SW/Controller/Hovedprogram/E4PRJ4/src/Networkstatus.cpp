/*
 * Networkstatus.cpp
 *
 * 4. Semester projekt forår 2015
 *
 *  Created on: 31/03/2015
 *      Author: Mick Kirkegaard & Poul Overgaard
 */

#include "Networkstatus.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

#define MAX_VALUE 30

bool Networkstatus::statusEth0() {

	char path[] = "/sys/class/net/eth0/operstate";
	char value_str[5];
	int fd = open(path, O_RDONLY);
	if(fd < 0) {
		cout << "Failed to open file for reading" << endl;
		close(fd);
		cout << path << endl;
		return -1;
	}
	int err = read(fd,value_str,5);
	if(err < 0) {
		cout << "Failed to read value!" << endl;
		close(fd);
		return -1;
	}

	close(fd);
	if(value_str[0] == 'u')
		return true;
	else
		return false;
}

bool Networkstatus::statusWlan0() {

	char path[] = "/sys/class/net/wlan0/operstate";
	char value_str[5];
	int fd = open(path, O_RDONLY);
	if(fd < 0) {
		cout << "Failed to open file for reading" << endl;
		close(fd);
		cout << path << endl;
		return -1;
	}
	int err = read(fd,value_str,5);
	if(err < 0) {
		cout << "Failed to read value!" << endl;
		close(fd);
		return -1;
	}

	close(fd);
	if(value_str[0] == 'u')
		return true;
	else
		return false;
}

void* Networkstatus::pingNet(void* arg) {

	usleep(5000000); // Sleep to allow cancel of program

	int ping_ret, status;

	status = system("ping -w 2 8.8.8.8"); // Ping Google DNS

	if (status >= 0)
		ping_ret = WEXITSTATUS(status);

	if(ping_ret == 0)
		return (void*) 1;
	else {
		// Retry another host
		status = system("ping -w 2 4.2.2.2"); // Another public DNS
		if (status >= 0)
			ping_ret = WEXITSTATUS(status);

		if(ping_ret == 0)
			return (void*) 1;
		else
			return (void*) 0;
	}
}

