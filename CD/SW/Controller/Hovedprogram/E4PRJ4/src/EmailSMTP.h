/*
 * EmailSMTP.h
 *
 *  Created on: 26/03/2015
 *      Author: mickkirkegaardnielse
 */

#ifndef EMAILSMTP_H_
#define EMAILSMTP_H_

#include <stdio.h>
#include <stdlib.h>

class EmailSMTP {
public:
	void sendError();
	void sendAlarm();
};



#endif /* EMAILSMTP_H_ */
