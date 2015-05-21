#ifndef BETJENINGSPANEL_H_
#define BETJENINGSPANEL_H_

#include "GPIOsocket.h"

class Betjeningspanel{
public:
	Betjeningspanel(int ledOnOff, int ledMan, int ledWifi,int butOnOff, int butMan);
	~Betjeningspanel();
	int setLedValue(int pin, int value);
	int getButValue(int pin) const;
	int ledOnOff_;
	int ledMan_;
	int ledWifi_;
	int butOnOff_;
	int butMan_;
};

#endif /* BETJENINGSPANEL_H_ */
