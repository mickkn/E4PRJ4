/*
 * Analyzer.c
 *
 *  Created on: 19/05/2015
 *      Author: Lukas
 */

#include "Analyzer.h"

/* ATTRIBUTES */
bool an_curBufRdy;
float an_spl;
fract32 an_freqSpec[AN_NFFT];		/* array with size recSize */
float an_freqSpecdB[AN_NFFT];
float an_freqSpecSmooth[AN_NFFT];
float an_tpr;
float an_smooth_delay[2];

void an_init(void)
{
	float an_spl = 0;
	float an_tpr = 0;
	int i;
	for(i = 0; i<AN_NFFT; i++)
	{
		an_freqSpec[i] = 0;
		an_freqSpecdB[i] = 0;
	}
}

void an_analyze(bool curBufRdy)
{
	an_curBufRdy = curBufRdy;

	an_spl = an_calcSPL();
	if(an_spl > AN_SPLTHRESH)
	{
		an_calcFFT();
		//an_tpr = an_calcTPR();
		an_g2dB();
		an_smooth(AN_M_SMOOTH);

		cg_categorize();
	}
	else
		ss_calcSignificans(BABYCON3);
}

float an_calcSPL(void)
{
	/* Find max-value */
	fract32 maxFr = 0.0;
	fract32* bufPtr = NULL;
	if(an_curBufRdy == 0) 	bufPtr = rb_mem0;
	else					bufPtr = rb_mem1;

	int i;
	for(i = 0; i < AN_NFFT; i++)
	{
		if(bufPtr[i] > maxFr)
			maxFr = bufPtr[i];
	}

	/* Convert to volts */
	float curVolt = fr32_to_float(maxFr)*AN_MAXVOLT;

	/* Calc and return SPL i dBV */
	return 20*log10f(curVolt);
}

void an_calcFFT(void)
{
	/* REAL RADIX-2 FFT */

	/* Input is the RecBuf memory-bank currently ready.*/
	fract32* inPtr = NULL;
	if(an_curBufRdy == 0) 	inPtr = rb_mem0;
	else					inPtr = rb_mem1;

	complex_fract32 out_rfft[AN_NFFT];
	complex_fract32 twiddle_table[AN_TWID_SIZE];
	twidfftrad2_fr32 (twiddle_table, AN_NFFT);
	int twiddle_stride = 1;	/*twid_table set for fft of size AN_NFFT */
	int block_exponent	;	/*set in rfft_fr32 */
	int scale_method = 2; 	/*dynamic scaling*/

	rfft_fr32(inPtr, out_rfft, twiddle_table, twiddle_stride,
			AN_NFFT, &block_exponent, scale_method);

	/* FFT MAGNITUDE */
	int mode = 1; 	/*input generated from time-domain real signal*/

	fft_magnitude_fr32(out_rfft, an_freqSpec, AN_NFFT, block_exponent, mode);

}

float an_calcTPR(void)
{
	fract32 sum = 0;		//Total sum af spektrum
	fract32 delay[3] = {0};	//Energy delay taps. delay[0] equals current sample
	fract32 e_T = 0;		//Sum of peaks
	fract32 g_T = 0;		//Threshold value

	int i;
	for(i = 0; i<AN_NFFT; i++)
	{
		delay[2] = delay[1];
		delay[1] = delay[0];
		delay[0] = an_freqSpec[i]*an_freqSpec[i];

		if(delay[1] > g_T)
			if((delay[2] < delay[1]) && (delay[1]< delay[0]))
				e_T += delay[1]>>AN_TPR_SCALING;

		sum = sum + delay[1]>>AN_TPR_SCALING;
	}

	return fr32_to_float(e_T)/fr32_to_float(sum);
}

void an_g2dB(void)
{
	int i;
	for(i = 0; i<AN_NFFT; i++)
	{
		an_freqSpecdB[i] = 20*log10f(fr32_to_float(an_freqSpec[i]));
	}
}

void an_smooth(unsigned int m)
{
	/* RECURSIVE FILTER*/
	float scaling = 1.0/m;
	float verticalShift = -an_freqSpecdB[430];	// [430] roughly equals 10 kHz
	int n;
	for(n = 0; n<AN_NFFT; n++)
	{
		an_freqSpecdB[n]+=verticalShift;	//raise level.
		an_freqSpecSmooth[n]=0;				//reset
	}

	/* First round */
	an_freqSpecSmooth[0]=scaling*an_freqSpecdB[0];

	for(n = 1; n<AN_NFFT; n++)
	{
		if(n<m)	/* Next M rounds */
		{
			an_freqSpecSmooth[n]=scaling*an_freqSpecdB[n]+an_freqSpecSmooth[n-1];
		}
		else if(n<AN_NFFT)
		{
			an_freqSpecSmooth[n]=scaling*(an_freqSpecdB[n]-an_freqSpecdB[n-m])+an_freqSpecSmooth[n-1];
		}
	}
}

