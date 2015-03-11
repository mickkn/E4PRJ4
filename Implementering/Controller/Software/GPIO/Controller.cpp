#include "Controller.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define MAX_VALUE 30

int Controller::setValue(int ledPin, int value) {
	char path[MAX_VALUE];
	snprintf(path,MAX_VALUE,"/sys/class/gpio/gpio%d/value",ledPin);
	int fd = open(path, O_WRONLY);
	if(fd < 0) {
		fprintf(stderr, "Failed to open GPIO value for writing\n");
		cout << path << endl;
		return -1;
	}

	close(fd);
}

int Controller::getValue(int ledPin) const {
        char path[MAX_VALUE];
        snprintf(path,MAX_VALUE,"/sys/class/gpio/gpio%d/value",ledPin);
        int fd = open(path, O_RDONLY);
        if(fd < 0) {
                fprintf(stderr, "Failed to open GPIO value for reading\n");
		cout << path << endl;
                return -1;
        }
	int err = read(fd,value_str,3);
	if(err < 0)
		fprintf(stderr, "Failed to read value!\n");
		close(fd);
		return -1;

	close(fd);

	return atoi(value_str); 
}

int Controller::getWifi() const {}
