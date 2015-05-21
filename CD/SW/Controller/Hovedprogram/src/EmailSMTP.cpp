/*
 * EmailSMTP.cpp
 *
 * 4. Semester projekt forår 2015
 *
 *  Created on: 26/03/2015
 *      Author: Mick Kirkegaard & Poul Overgaard
 */

#include "EmailSMTP.h"

void EmailSMTP::sendError() {
	system("/home/pi/scripts/mail_error.sh");
}

void EmailSMTP::sendAlarm() {
	system("/home/pi/scripts/mail_alarm.sh");
}
