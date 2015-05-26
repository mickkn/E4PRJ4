/*
 * RecBuf.c
 *
 *  Created on: 19/05/2015
 *      Author: Hedegaard & Boye
 */

//includes
#include "RecBuf.h"

//Variables
fract32 rb_mem0[RB_SIZE];
fract32 rb_mem1[RB_SIZE];
bool rb_currActiveBuffer;
unsigned int rb_index;
bool rb_ready;


void rb_init(void)
{
	rb_currActiveBuffer = false;
	rb_index = 0;
	rb_ready = 0;
	//Initializing memory
	int i;
	for(i=0; i< RB_SIZE; i++)
	{
		rb_mem0[i] = 0;
		rb_mem1[i] = 0;
	}
}

void rb_storeData(fract32 sample)
{
	/*if(rb_ready) return; */


	switch(rb_currActiveBuffer)
	{
	case 0:
		if(rb_index == RB_SIZE)
		{
			rb_index = 0;
			rb_currActiveBuffer = true;
			rb_mem1[rb_index] = sample;
			rb_ready = true;
		}
		else
		{
			rb_mem0[rb_index] = sample;
		}
		rb_index++;
		break;

	case 1:
		if(rb_index == RB_SIZE)
		{
			rb_index = 0;
			rb_currActiveBuffer = 0;
			rb_mem0[rb_index] = sample;
			rb_ready = true;
		}
		else
		{
			rb_mem1[rb_index] = sample;
		}
		rb_index++;
		break;

	default:
		break;

	}
}

//Test funktion - printer indholdet af rb_mem0 og rb_mem1
void rb_print(void)
{
	printf("\n\nContent of rb_mem0: \n");
	int i = 0;
	for(i = 0; i<RB_SIZE; i++)
	{
		printf("Index[%d] = %d \n ", i, rb_mem0[i]);
	}

	printf("\nContent of rb_mem1: \n");
	for(i = 0;i<RB_SIZE; i++)
	{
		printf("Index[%d] = %d \n ", i, rb_mem1[i]);
	}
}


