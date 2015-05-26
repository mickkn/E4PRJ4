/*
 * Statistician.c
 *
 *  Created on: 19/05/2015
 *      Author: Hedegaard & Boye
 */

#include "Statistician.h"

//Variables
int ss_bc;
int ss_significans;
int ss_bbyCon3;
int ss_bbyCon2;
int ss_bbyCon1;
int ss_sigContainer[SS_SIZE];
int ss_count;
int ss_Histogram[SS_HIST_SIZE];
int ss_hist_count;

void ss_init(void)
{
	ss_bc = 3;
	ss_significans = 1;
	ss_bbyCon3 = 0;
	ss_bbyCon2 = 0;
	ss_bbyCon1 = 0;

	int i;
	for(i=0; i< SS_SIZE; i++)
	{
		ss_sigContainer[i] = BABYCON3;
	}

	for(i=0; i< SS_HIST_SIZE; i++)
	{
		ss_Histogram[i] = BABYCON3;
	}


	ss_count = 0;
	ss_hist_count = 0;
}

void ss_calcSignificans(int bc)
{
	int temp[SS_SIZE];
	//Copying into a temporary array
	int i = 0;
	for(i = 0; i<SS_SIZE; i++)
	{
		temp[i] = ss_sigContainer[i];
	}
	ss_sigContainer[0] = bc;

	for(i = 0; i<SS_SIZE-2;i++)
	{
		ss_sigContainer[i+1] = temp[i];
	}

	ss_count++;
	if(ss_count == SS_SIZE)
	{
		ss_count = 0;
		ss_bbyCon1 = 0;
		ss_bbyCon2 = 0;
		ss_bbyCon3 = 0;
		ss_significans = 1;

		for (int i=0; i<SS_SIZE; i++)
		{
			switch(ss_sigContainer[i])
			{
			case BABYCON1:
				ss_bbyCon1+=11;
				break;

			case BABYCON2:
				ss_bbyCon2+=6;
				break;

			case BABYCON3:
				ss_bbyCon3+=1;
				break;
			}
		}

		if(ss_bbyCon1> ss_significans)
		{
			ss_significans = ss_bbyCon1;
			ss_bc = BABYCON1;
		}
		if(ss_bbyCon2> ss_significans)
		{
			ss_significans = ss_bbyCon2;
			ss_bc = BABYCON2;
		}
		if(ss_bbyCon3 > ss_significans)
		{
			ss_significans = ss_bbyCon3;
			ss_bc = BABYCON3;
		}

		printf("\nCURRENT BABYCON: %d\n",ss_bc);
		tw_send(ss_bc);
		hitRatioTest(ss_bc);

	}
}

void ss_print(void)
{
	printf("Current BABYCON level is: %d\n", ss_bc);
	printf("Stat contend: ss_bbyCon1: %d, ss_bbyCon2: %d, ss_bbyCon3: %d \n", ss_bbyCon1, ss_bbyCon2, ss_bbyCon3);
}

void hitRatioTest(int bc)
{
	ss_Histogram[ss_hist_count++] = bc;
	if(ss_hist_count == SS_HIST_SIZE)
	{
		ss_hist_count = 0;
		printf("Statistician: Histogram ready\n");
	}
}




