/*
 * Categorizer.h
 *
 *  Created on: 19/05/2015
 *      Author: Hedegaard & Boye
 */

#ifndef CATEGORIZER_H_
#define CATEGORIZER_H_

//includes
#include "Talkthrough.h"

//defines
#define CG_FS 24000
#define CG_BABYCON1 1
#define CG_BABYCON2 2
#define CG_BABYCON3 3
#define CG_FREQ_FAC ((1.0)/(1/(AN_NFFT/2+1)*(CG_FS/2)))
#define CG_TPR_THRESH 4000.0

extern float cg_freq_fac;

//attributes
extern int cg_babyCon;
extern float cg_dBroadThreshHighBC1;
extern float cg_dBroadThreshLowBC2;
extern float cg_dBroadThreshHighBC2;
extern int cg_broadFreqLow;
extern int cg_broadFreqHigh;
extern int cg_firstPeakFreqBC1;
extern int cg_secondPeakFreqBC1;
extern int cg_freqMargin;
extern int cg_margin;
extern int cg_broadStart;
extern int cg_broadEnd;
extern int cg_BC1First;
extern int cg_BC1Second;
extern float cg_dBroad;


//prototypes
void cg_init(void);
void cg_categorize(void);
bool cg_checkBC1(void);
bool cg_checkBC2(void);

#endif /* CATEGORIZER_H_ */
