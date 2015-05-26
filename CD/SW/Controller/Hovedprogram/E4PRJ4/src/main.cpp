/*
 * main.cpp
 *
 * 4. Semester projekt forår 2015
 *
 *      Author: Mick Kirkegaard & Poul Overgaard
 */

#include "Betjeningspanel.h"
#include "I2Csocket.h"
#include "EmailSMTP.h"
#include "TWTTLsocket.h"
#include "Networkstatus.h"
#include "Website.h"
#include "PowerCTRL.h"

#include <pthread.h>
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

bool manStart = false;
bool errorFlag = false;
bool DEBUG = false;
bool MODULTEST = false;

int modultest_onoff = 1;

#define ERRORDELAY	500000 // 500ms
#define I2CDELAY 	100000
#define I2C_ID		0x00
#define I2C_ONOFF	0x01
#define I2C_FREQ	0x02
#define I2C_ANGLE	0x03
#define I2C_STAT	0x04
#define POWEROFF 0
#define POWERON 1
#define EMAILDELAY 	4000000
#define BC2LOOPTIME 20000 	// 2min=120000ms (Test = 20000ms)
#define MSLOOPTIME2 20000 	//  2min=120000ms (Test = 20000ms)
#define MSLOOPTIME3 30000 	//  3min=180000ms (Test = 30000ms)
unsigned char VSStatus = 0;
unsigned char A_FREQ  = 0x08; 	// 0,08 Hz (8) // afgrænsningsværdi
unsigned char A_ANGLE = 0xC8;	// 10 grader (200)
unsigned char B_FREQ  = 0x10; 	// 0,16 Hz (16) // afgrænsningsværdi
unsigned char B_ANGLE = 0x78;	// 6 grader (120)
unsigned char C_FREQ  = 0x20;	// 0,32 Hz (33) // afgrænsningsværdi
unsigned char C_ANGLE = 0x50;	// 4 grader (80)
unsigned char M_FREQ  = 0x0C;	// 0,12 Hz (12) // afgrænsningsværdi
unsigned char M_ANGLE = 0xA0;	// 8 grader (160)
unsigned char VS_ON  = 0xF0;		// ON
unsigned char VS_OFF = 0x0F;		// OFF

Betjeningspanel panel(14,18,15,22,17);
I2Csocket i2c(0x08,"/dev/i2c-1");
TWTTLsocket tw(10, 9);
PowerCTRL powerControl(23);
Website web;
EmailSMTP mail;

/* function prototypes */
void manStartISR();
void manStartFunc();
void* thread_pingNet(void* arg);
bool pingFlag = false;

int main(int argc, char *argv[]) {

	for(int i=0 ; i < argc ; ++i) {
		if(!strcmp(argv[i], "-m"))MODULTEST =true;
		if(!strcmp(argv[i], "-debug"))DEBUG = true;
	}

	/* initialize wiringPi*/
	wiringPiSetup();

	/* enable interrupt */
	wiringPiISR(0,INT_EDGE_FALLING,manStartISR); // GPIO17 == WiringPi PIN 0

	/* internet ping thread */
	pthread_t networkThread;

	/* turn off all LEDs on startup */
	panel.setLedValue(panel.ledOnOff_,OFF);
	panel.setLedValue(panel.ledMan_  ,OFF);
	panel.setLedValue(panel.ledWifi_ ,OFF);

	/* on status indicator */
	bool onStatus = false;

	/* system loop */
	while(1) {

		if(MODULTEST && modultest_onoff) {
			printf("[OUTSIDE ON LOOP]\n");
			modultest_onoff = 0;
		}

		/* reset error status in OFF-loop */
		VSStatus = 0;

		/* system on-loop */
		while(panel.getButValue(panel.butOnOff_) == 1) {

			if(MODULTEST && !modultest_onoff) {
				printf("[INSIDE ON LOOP]\n");
				modultest_onoff = 1;
			}

			/* turn on powersupply */
			powerControl.power(POWERON);

			/* create ping thread */
			if(!pingFlag) {
				pthread_create(&networkThread ,NULL,thread_pingNet ,NULL);
				pingFlag = true;
			}

			/* set on-status and turn on ON/OFF light */
			onStatus = true;
			panel.setLedValue(panel.ledOnOff_,ON);

			/* run manual start if button has been pressed */
			if(manStart)
				manStartFunc();

			/* babycon 3 communication */
			if(tw.getBabyconLevel() == 3) {
				if(MODULTEST)printf("BABYCON #3\n");
				usleep(I2CDELAY);
				i2c.writeReg(I2C_ONOFF,VS_ON); 	// write on
				if(DEBUG)printf("OnOff : 0xf0\n");
				usleep(I2CDELAY);
				i2c.writeReg(I2C_FREQ,0x00);	// write frequency
				if(DEBUG)printf("Freq  : 0x00\n");
				usleep(I2CDELAY);
				i2c.writeReg(I2C_ANGLE,0x00);	// write angle
				if(DEBUG)printf("Angle : 0x00\n");
				usleep(I2CDELAY);
				i2c.readReg(I2C_STAT,VSStatus);	// read status
				if(DEBUG)printf("Status: 0x%x\n\n", VSStatus);
				web.updateToBabyCon3(); // update website
			}

			/* babycon 2 communication */
			if(tw.getBabyconLevel() == 2) {
				if(MODULTEST)printf("BABYCON #2A\n");
				web.updateToBabyCon2();
				int currentTime = millis();
				int loopBreak = currentTime+BC2LOOPTIME;

				/* babycon 2a loop */
				while((panel.getButValue(panel.butOnOff_) == 1)
						&& (currentTime < loopBreak)
						&& (VSStatus < 128)
						&& (tw.getBabyconLevel() == 2)
						&& !manStart) {
					usleep(I2CDELAY);
					i2c.writeReg(I2C_ONOFF,VS_ON);		// write on
					if(DEBUG)printf("OnOff : 0xf0\n");
					usleep(I2CDELAY);
					i2c.writeReg(I2C_FREQ,A_FREQ);		// write frequency
					if(DEBUG)printf("Freq  : 0x%x\n", A_FREQ);
					usleep(I2CDELAY);
					i2c.writeReg(I2C_ANGLE,A_ANGLE);	// write angle
					if(DEBUG)printf("Angle : 0x%x\n", A_ANGLE);
					usleep(I2CDELAY);
					i2c.readReg(I2C_STAT,VSStatus);		// read status
					if(DEBUG)printf("Status: 0x%x\n\n", VSStatus);
					currentTime = millis();
				}

				currentTime = millis();
				loopBreak = currentTime+BC2LOOPTIME;

				if(MODULTEST)printf("BABYCON #2B\n");

				/* babycon 2b loop */
				while((panel.getButValue(panel.butOnOff_) == 1)
						&& (currentTime < loopBreak)
						&& (VSStatus < 128)
						&& (tw.getBabyconLevel() == 2)
						&& !manStart) {
					usleep(I2CDELAY);
					i2c.writeReg(I2C_ONOFF,VS_ON);		// write on
					if(DEBUG)printf("OnOff : 0xf0\n");
					usleep(I2CDELAY);
					i2c.writeReg(I2C_FREQ,B_FREQ);		// write frequency
					if(DEBUG)printf("Freq  : 0x%x\n", B_FREQ);
					usleep(I2CDELAY);
					i2c.writeReg(I2C_ANGLE,B_ANGLE);	// write angle
					if(DEBUG)printf("Angle : 0x%x\n", B_ANGLE);
					usleep(I2CDELAY);
					i2c.readReg(I2C_STAT,VSStatus);		// read status
					if(DEBUG)printf("Status: 0x%x\n\n", VSStatus);
					currentTime = millis();
				}

				currentTime = millis();
				loopBreak = currentTime+BC2LOOPTIME;

				if(MODULTEST)printf("BABYCON #2C\n");

				/* babycon 2c loop */
				while((panel.getButValue(panel.butOnOff_) == 1)
						&& (currentTime < loopBreak)
						&& (VSStatus < 128)
						&& (tw.getBabyconLevel() == 2)
						&& !manStart) {
					usleep(I2CDELAY);
					i2c.writeReg(I2C_ONOFF,VS_ON);		// write on
					if(DEBUG)printf("OnOff : 0xf0\n");
					usleep(I2CDELAY);
					i2c.writeReg(I2C_FREQ,C_FREQ);		// write frequency
					if(DEBUG)printf("Freq  : 0x%x\n", C_FREQ);
					usleep(I2CDELAY);
					i2c.writeReg(I2C_ANGLE,C_ANGLE);	// write angle
					if(DEBUG)printf("Angle : 0x%x\n", C_ANGLE);
					usleep(I2CDELAY);
					i2c.readReg(I2C_STAT,VSStatus);		// read status
					if(DEBUG)printf("Status: 0x%x\n\n", VSStatus);
					currentTime = millis();
				}
			}

			/* babycon 1 communication */
			if(tw.getBabyconLevel() == 1) {
				if(MODULTEST)printf("BABYCON #1\n");
				web.updateToBabyCon1();			// update website
				usleep(I2CDELAY);
				i2c.writeReg(I2C_ONOFF,VS_ON); 	// write on
				usleep(I2CDELAY);
				i2c.writeReg(I2C_FREQ,0x00);	// write frequency
				usleep(I2CDELAY);
				i2c.writeReg(I2C_ANGLE,0x00);	// write angle

				/* send alarm e-mail up to 10 times*/
				int i = 0;
				while(panel.getButValue(panel.butOnOff_) && !manStart) {
					cout << "Sender alarm e-mail... [" << i++ << "]" << endl;
					mail.sendAlarm();
					cout << "...alarm e-mail sendt" << endl;
					usleep(EMAILDELAY); // delay
					if(i > 9)
						while(panel.getButValue(panel.butOnOff_) && !manStart);
				}
			}

			/* error handler if ERR == 1 or babycon == 0 */
			if(tw.getBabyconLevel() == 0 || VSStatus > 127) {
				if(MODULTEST)printf("BABYCON #0 (ERROR)\n");
				VSStatus = 0;			 		// reset status indicator
				usleep(I2CDELAY);
				i2c.writeReg(I2C_ONOFF,VS_ON); 	// write on
				usleep(I2CDELAY);
				i2c.writeReg(I2C_FREQ,0x00);	// write frequency
				usleep(I2CDELAY);
				i2c.writeReg(I2C_ANGLE,0x00);	// write angle

				/* send error e-mail */
				cout << "Sender fejl e-mail..." << endl;
				mail.sendError();
				cout << "...fejl e-mail sendt" << endl;
				/* wait for hard reset */
				while(panel.getButValue(panel.butOnOff_)) {
					panel.setLedValue(panel.ledOnOff_, OFF); 	// turn off LED
					usleep(I2CDELAY);
					i2c.writeReg(I2C_ONOFF,VS_ON); 	// write on
					usleep(I2CDELAY);
					i2c.writeReg(I2C_FREQ,0x00);	// write frequency
					usleep(I2CDELAY);
					i2c.writeReg(I2C_ANGLE,0x00);	// write angle
					usleep(ERRORDELAY);
					panel.setLedValue(panel.ledOnOff_, ON); 	// turn off LED
					usleep(ERRORDELAY);
					errorFlag = true;
				}
			}
		}
		/* turn off */
		if(onStatus) {
			if(DEBUG)printf("closing down...\n");
			do{
				usleep(I2CDELAY);
				i2c.writeReg(I2C_ONOFF,VS_OFF); 	// write off
				usleep(I2CDELAY);
				i2c.writeReg(I2C_FREQ,0x00);		// write frequency
				usleep(I2CDELAY);
				i2c.writeReg(I2C_ANGLE,0x00);		// write angle
				usleep(I2CDELAY);
				i2c.readReg(I2C_STAT,VSStatus);		// read status
				if(DEBUG)printf("[closing loop]\n");
				if(errorFlag)break;
			}while(VSStatus < 0x10);	// wait for shutdown ready

			if(DEBUG)printf("[turning off power]\n");
			powerControl.power(POWEROFF); 				// power off
			pthread_join(networkThread, NULL);			// join thread
			pingFlag = false;							// ready for new ping
			panel.setLedValue(panel.ledOnOff_, OFF); 	// turn off LED
			onStatus = false;
			errorFlag = false;
		}
	}
	return 0;
}

void manStartISR() {
	/* set manStart to true and turn on LED */
	if(panel.getButValue(panel.butOnOff_) == 1
			&& (tw.getBabyconLevel() > 0)) {
		manStart = true;
		panel.setLedValue(panel.ledMan_,ON);
	}
	if(MODULTEST || DEBUG)printf("[MANUELSTART ISR]\n");

}

void manStartFunc() {

	panel.setLedValue(panel.ledMan_,ON); // turn on LED
	if(MODULTEST || DEBUG)printf("[MANUELSTART RUNNING]\n");
	/* "manuel start" 2 min loop */
	int currentTime = millis();
	int loopBreak = currentTime+MSLOOPTIME2;

	while((panel.getButValue(panel.butOnOff_) == 1)
			&& (currentTime < loopBreak)
			&& (VSStatus < 128)) {
		usleep(I2CDELAY);
		i2c.writeReg(I2C_ONOFF,VS_ON);		// write on
		if(DEBUG)printf("OnOff : 0xf0\n");
		usleep(I2CDELAY);
		i2c.writeReg(I2C_FREQ,M_FREQ);		// write frequency
		if(DEBUG)printf("Freq  : 0x%x\n", M_FREQ);
		usleep(I2CDELAY);
		i2c.writeReg(I2C_ANGLE,M_ANGLE);	// write angle
		if(DEBUG)printf("Angle : 0x%x\n", M_ANGLE);
		usleep(I2CDELAY);
		i2c.readReg(I2C_STAT,VSStatus);		// read status
		if(DEBUG)printf("Status: 0x%x\n\n", VSStatus);
		currentTime = millis();
	}

	/* "manuel start" 3 min loop */
	currentTime = millis();
	loopBreak = currentTime+MSLOOPTIME3;

	while((panel.getButValue(panel.butOnOff_) == 1)
			&& (currentTime < loopBreak)
			&& (VSStatus < 128)
			&& (tw.getBabyconLevel() != 1)) {
		usleep(I2CDELAY);
		i2c.writeReg(I2C_ONOFF,VS_ON);		// write on
		if(DEBUG)printf("OnOff : 0xf0\n");
		usleep(I2CDELAY);
		i2c.writeReg(I2C_FREQ,M_FREQ);		// write frequency
		if(DEBUG)printf("Freq  : 0x%x\n", M_FREQ);
		usleep(I2CDELAY);
		i2c.writeReg(I2C_ANGLE,M_ANGLE);	// write angle
		if(DEBUG)printf("Angle : 0x%x\n", M_ANGLE);
		usleep(I2CDELAY);
		i2c.readReg(I2C_STAT,VSStatus);		// read status
		if(DEBUG)printf("Status: 0x%x\n\n", VSStatus);
		currentTime = millis();
	}

	manStart = false;
	if(MODULTEST || DEBUG)printf("[MANUELSTART DONE]\n");
	panel.setLedValue(panel.ledMan_,OFF);
}

void* thread_pingNet(void* arg) {

	/* loop forever */
	while(1){
		usleep(5000000); // Sleep to allow cancel of program

		int status;

		status = system("ping -w 2 8.8.8.8"); // Ping Google DNS

		if(DEBUG)printf("[STATUS]: %d\n",status);

		if(status == 0) {
			panel.setLedValue(panel.ledWifi_, OFF);
			if(MODULTEST)printf("[INTERNET CONNECTED]\n");
		}
		else {
			status = system("ping -w 2 4.2.2.2"); //
			if(status == 0) {
				panel.setLedValue(panel.ledWifi_, OFF);
				if(MODULTEST)printf("[INTERNET CONNECTED]\n");
			}
			else {
				panel.setLedValue(panel.ledWifi_, ON);
				if(MODULTEST)printf("INTERNET NOT CONNECTED\n");
			}
		}
		if(panel.getButValue(panel.butOnOff_) == 0) {
			panel.setLedValue(panel.ledWifi_, OFF);
			if(MODULTEST)printf("[INTERNET CONNECTED]\n");
		 	break;
		}
	}
	return NULL;
}
