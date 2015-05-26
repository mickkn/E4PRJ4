/*
 * Statistician.h
 *
 *  Created on: 19/05/2015
 *      Author: Hedegaard & Boye
 */

#ifndef STATISTICIAN_H_
#define STATISTICIAN_H_

#include "Talkthrough.h"

//defines
#define BABYCON1 1
#define BABYCON2 2
#define BABYCON3 3
#define SS_SIZE 100
#define SS_HIST_SIZE 100

//Attributes
extern int ss_bc;
extern int ss_significans;
extern int ss_bbyCon3;
extern int ss_bbyCon2;
extern int ss_bbyCon1;
extern int ss_sigContainer[];
extern int ss_count;
extern int ss_Histogram[];
extern int ss_hist_count;

//Methods
void ss_init(void);
void ss_calcSignificans(int);
void ss_print(void);
void hitRatioTest(int);

#endif /* STATISTICIAN_H_ */
