#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>

#define DATALEN 1

static char ledOn[] = "0";
static char ledOff[] = "1";

int main() {

char pinOnOff;
char manuel;

while(1) {

int fp_gpio14 = open("/sys/class/gpio/gpio14/value", O_RDWR);
int fp_gpio15 = open("/sys/class/gpio/gpio15/value", O_RDWR);
int fp_gpio17 = open("/sys/class/gpio/gpio17/value", O_RDWR);
int fp_gpio18 = open("/sys/class/gpio/gpio18/value", O_RDWR);
int fp_gpio22 = open("/sys/class/gpio/gpio22/value", O_RDWR);

read(fp_gpio17,&pinOnOff,DATALEN);
read(fp_gpio22 ,&manuel,DATALEN);

if(pinOnOff == '1') 
	write(fp_gpio14,&ledOn[0],DATALEN);
else
	write(fp_gpio14,&ledOff[0],DATALEN);

if(manuel == '1') 
        write(fp_gpio18,&ledOn[0],DATALEN);
else
        write(fp_gpio18,&ledOff[0],DATALEN);

if((manuel == '1') && (pinOnOff == '1')) 
        write(fp_gpio15,&ledOn[0],DATALEN);
else
        write(fp_gpio15,&ledOff[0],DATALEN);

/*
printf("manuel: ");
printf("%c\n",manuel);
printf("pinOnOff: ");
printf("%c\n",pinOnOff);
*/

close(fp_gpio22);
close(fp_gpio14);
close(fp_gpio15);
close(fp_gpio17);
close(fp_gpio18);
}

return 0;

}
