/*
 * Networkstatus.h
 *
 *  Created on: 31/03/2015
 *      Author: mickkirkegaardnielse
 */

#ifndef NETWORKSTATUS_H_
#define NETWORKSTATUS_H_

#include <string>

using namespace std;

class Networkstatus {
public:
	void* pingNet(void*);
	bool statusEth0();
	bool statusWlan0();
};



#endif /* NETWORKSTATUS_H_ */
