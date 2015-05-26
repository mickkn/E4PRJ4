#ifndef GPIOSOCKET_H_
#define GPIOSOCKET_H_

#define EXPORTDELAY 500000

#define IN 		0
#define OUT 	1
#define DOWN 	0
#define UP 		1
#define LOW 	0
#define HIGH 	1
#define ON		0
#define OFF		1

int gpioExport(int pin);
int gpioUnexport(int pin);
int gpioDirection(int pin, int dir);

#endif /* GPIOSOCKET_H_ */
