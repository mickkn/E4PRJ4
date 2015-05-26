/*
 * TwoWireCom.h
 *
 *  Created on: 19/05/2015
 *      Author: Hedegaard & Boye
 */

#ifndef TWOWIRECOM_H_
#define TWOWIRECOM_H_

//Includes
#include "Talkthrough.h"

//defines
//Blackfin533 GPIO pins for output //Placed J2 - Datasheet page 84
#define TW_OUTPUT_PIN_MSB PF4
#define TW_OUTPUT_PIN_LSB PF6

//Prototype for send-function;
void tw_init(void);
void tw_send(int);

#endif /* TWOWIRECOM_H_ */
