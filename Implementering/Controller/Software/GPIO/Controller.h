#pragma once

class Controller {
public:
	int setValue(int ledPin,int value);
	int getValue(int ledPin) const;
	int getWifi() const;
};
