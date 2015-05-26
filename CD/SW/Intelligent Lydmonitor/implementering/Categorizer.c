/*
 * Categorizer.c
 *
 *  Created on: 19/05/2015
 *      Author: Hedegaard & Boye
 */

#include "Categorizer.h"

float cg_freq_fac;

int cg_babyCon;
float cg_dBroadThreshHighBC1;
float cg_dBroadThreshLowBC2;
float cg_dBroadThreshHighBC2;
int cg_broadFreqLow;
int cg_broadFreqMid;
int cg_broadFreqHigh;
int cg_firstPeakFreqBC1;
int cg_secondPeakFreqBC1;
int cg_freqMargin;
int cg_margin;
int cg_broadStart;
int cg_broadEnd;
int cg_BC1First;
int cg_BC1Second;
float cg_dBroad;

void cg_init(void)
{
	cg_freq_fac = 0.04275; //((1.0)/(1/(AN_NFFT/2+1)*(CG_FS/2)));
	cg_babyCon = CG_BABYCON3; //Set cg_babyCon default 3
	cg_dBroadThreshHighBC1 = 26;
	cg_dBroadThreshLowBC2 = 14;
	cg_dBroadThreshHighBC2 = 24;
	cg_broadFreqLow = 1000;
	cg_broadFreqHigh = 5500;
	cg_firstPeakFreqBC1 = 1400;
	cg_secondPeakFreqBC1 = 4000;
	cg_freqMargin = 600;

	cg_broadStart = (int)floor(cg_broadFreqLow*cg_freq_fac);
	cg_broadEnd = (int)floor(cg_broadFreqHigh*cg_freq_fac);

	cg_margin = (int)floor(cg_freqMargin*cg_freq_fac);
	cg_BC1First = (int)floor(cg_firstPeakFreqBC1*cg_freq_fac);
	cg_BC1Second = (int)floor(cg_secondPeakFreqBC1*cg_freq_fac);
}

void cg_categorize(void)
{
	cg_babyCon = CG_BABYCON3; //Set cg_babyCon default 3

	if(true /*an_tpr > CG_TPR_THRESH*/)
	{
		cg_dBroad = an_freqSpecSmooth[cg_broadStart]-an_freqSpecSmooth[cg_broadEnd];

		if(cg_checkBC2())
			cg_babyCon= CG_BABYCON2;

		if(cg_checkBC1())
			cg_babyCon= CG_BABYCON1;

		ss_calcSignificans(cg_babyCon);
	}
}


bool cg_checkBC2(void)
{
	if((cg_dBroad > cg_dBroadThreshLowBC2) &&
		(cg_dBroad < cg_dBroadThreshHighBC2))
	{
		return true;
	}
	else
		return false;
}

bool cg_checkBC1(void)
{
	if((cg_dBroad < cg_dBroadThreshHighBC1) &&
	  (an_freqSpecSmooth[cg_BC1First] > an_freqSpecSmooth[cg_BC1First - cg_margin]) &&
	  (an_freqSpecSmooth[cg_BC1First] > an_freqSpecSmooth[cg_BC1First + cg_margin]) &&
	  (an_freqSpecSmooth[cg_BC1Second] > an_freqSpecSmooth[cg_BC1Second - cg_margin]) &&
	  (an_freqSpecSmooth[cg_BC1Second] > an_freqSpecSmooth[cg_BC1Second + cg_margin]))
	{
		return true;
	}
	else
		return false;
}




