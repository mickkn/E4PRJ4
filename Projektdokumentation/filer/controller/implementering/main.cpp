int main() {

/* initialize wiringPi*/
wiringPiSetup();

/* enable interrupt */
wiringPiISR();

/* internet ping thread */
pthread_t networkThread;

/* turn off all LEDs on startup */
turnOffAllLeds();

/* on status indicator */
bool onStatus = false;

/* system loop */
while(1) {

	/* reset error status in OFF-loop */
	vugge_status = 0;

	/* system on-loop */
	while(on_off == on) {

		/* turn on powersupply */
		powerControl(ON);

		/* create ping thread */
		if(!pingFlag) {
			pthread_create(networkThread);

		/* set on-status and turn on ON/OFF light */
		onStatus = true;
		greenLED(ON);

		/* run manual start if button has been pressed */
		if(manStart)
			manStartFunc();

		/* babycon 3 communication */
		if(babyCon == 3) {
			i2cWrite(on_off_reg,ON); 		// write on
			i2cWrite(frekvens_reg,0);		// write frequency
			i2cWrite(vinkel_reg,0);			// write angle
			i2cRead(status_reg,vugge_status);	// read status
			web.updateToBabyCon3(); 		// update website
		}

		/* babycon 2 communication */
		if(babyCon == 2) {
			web.updateToBabyCon2();

			/* babycon 2a loop */
			while(on_off == on and vugge_status < 128 and babyCon == 2 and !manStart and looptime != done)
			i2cWrite(on_off_reg,ON); 		// write on
			i2cWrite(frekvens_reg,a_frekvens);	// write frequency
			i2cWrite(vinkel_reg,a_vinkel);		// write angle
			i2cRead(status_reg,vugge_status);	// read status
			web.updateToBabyCon2(); 		// update website
			}

			/* babycon 2b loop */
			while(on_off == on and vugge_status < 128 and babyCon == 2 and !manStart and looptime != done)
			i2cWrite(on_off_reg,ON); 		// write on
			i2cWrite(frekvens_reg,b_frekvens);	// write frequency
			i2cWrite(vinkel_reg,b_vinkel);		// write angle
			i2cRead(status_reg,vugge_status);	// read status
			web.updateToBabyCon2(); 		// update website
			}

			/* babycon 2c loop */
			while(on_off == on and vugge_status < 128 and babyCon == 2 and !manStart and looptime != done)
			i2cWrite(on_off_reg,ON); 		// write on
			i2cWrite(frekvens_reg,c_frekvens);	// write frequency
			i2cWrite(vinkel_reg,c_vinkel);		// write angle
			i2cRead(status_reg,vugge_status);	// read status
			web.updateToBabyCon2(); 		// update website
			}
		}

		/* babycon 1 communication */
		if(babyCon == 1) {
			web.updateToBabyCon1();			// update website
			i2cWrite(on_off_reg,ON); 		// write on
			i2cWrite(frekvens_reg,0);		// write frequency
			i2cWrite(vinkel_reg,0);			// write angle
			i2cRead(status_reg,vugge_status);		// read status

			/* send alarm e-mail up to 10 times*/
			int i;
			while(on_off == on and !manStart and i < 10) {
				mail.sendAlarm();
				i++;
			}
		}

		/* error handler if ERR == 1 or babycon == 0 */
		if(babyCon == 0 or vugge_status > 127) {
			vugge_status = 0;			// reset vugge_status
			i2cWrite(on_off_reg,ON); 		// write on
			i2cWrite(frekvens_reg,0);		// write frequency
			i2cWrite(vinkel_reg,0);			// write angle
			i2cRead(status_reg,vugge_status);	// read status

			/* send error e-mail */
			mail.sendError();
			/* wait for hard reset */
			while(on_off == on) {
				i2cWrite(on_off_reg,ON); 	// write on
				i2cWrite(frekvens_reg,0);	// write frequency
				i2cWrite(vinkel_reg,0);		// write angle
				blinkGreenLED();		// error indicator
				errorFlag = true;		// set fejl flag
			}
		}
	}
	/* turn off */
	if(onStatus) {
		do{
			i2cWrite(on_off_reg,ON); 		// write on
			i2cWrite(frekvens_reg,0);		// write frequency
			i2cWrite(vinkel_reg,0);			// write angle
			i2cRead(status_reg,vugge_status);	// read status
			if(errorFlag)break;			// leave loop if error
		}while(vugge_status < 0x10);			// wait for shutdown ready

		powerControl(OFF); 		// power off
		pthread_join(networkThread);	// join thread
		pingFlag = false;		// ready for new ping
		greenLED(OFF); 			// turn off LED
		onStatus = false;		// set ON status
		errorFlag = false;		// set errorFlag
	}
}
return 0;
}

void manStartISR() {
	/* set manStart to true and turn on LED */
	if(on_off == on and babyCon > 0) {
		manStart = true;
		msLed(ON);
	}
}

void manStartFunc() {
	msLed(ON); // turn on LED
	/* "manuel start" 2 min loop */
	while(on_off == on and looptime != done and vugge_status < 128) {
		i2cWrite(on_off_reg,ON); 		// write on
		i2cWrite(frekvens_reg,m_frekvens);	// write frequency
		i2cWrite(vinkel_reg,m_vinkel);		// write angle
		i2cRead(status_reg,vugge_status);	// read status
	}

	/* "manuel start" 3 min loop */
	while(on_off == on and looptime != done and vugge_status < 128 and babyCon != 1) {
		i2cWrite(on_off_reg,ON); 		// write on
		i2cWrite(frekvens_reg,m_frekvens);	// write frequency
		i2cWrite(vinkel_reg,m_vinkel);		// write angle
		i2cRead(status_reg,vugge_status);	// read status
	}

	manStart = false;
	msLed(OFF); // turn off LED
}

void* thread_pingNet(void* arg) {

	/* loop forever */
	while(1){
		delay(5sec); // Sleep to allow cancel of program

		int status;

		status = system("ping -w 2 8.8.8.8"); // Ping Google DNS

		if(status == 0)
			wifiLed(OFF);
		else {
			status = system("ping -w 2 4.2.2.2"); // Ping another public DNS
			if(status == 0)
				wifiLed(OFF);
			else
				wifiLed(ON);
		}
		if(on_off == off) {
			wifiLed(OFF);	// quit loop if turned OFF
		 	break;
		}
	}
	return NULL;
}