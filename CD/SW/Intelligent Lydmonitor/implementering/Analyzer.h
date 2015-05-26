/*
 * Analyzer.h
 *
 *  Created on: 19/05/2015
 *      Author: Lukas
 */

#ifndef ANALYZER_H_
#define ANALYZER_H_

#include "Talkthrough.h"

/* DEFINES */
#define AN_NFFT	1024 /* Must be power of two. 4096 creates errors */
#define AN_TWID_SIZE AN_NFFT/2
#define AN_SPLTHRESH -28.0 /* [dBV] */
#define AN_MAXVOLT 1.65
#define AN_M_SMOOTH 35
#define AN_TPR_SCALING 3;

/* METHODS */
void an_init(void);
void an_analyze(bool curBufRdy);
float an_calcSPL(void);
void an_calcFFT(void);
float an_calcTPR(void);
void an_g2dB(void);
void an_smooth(unsigned int m);

/* ATTRIBUTES */
extern bool an_curBufRdy;
extern float an_spl;
extern fract32 an_freqSpec[AN_NFFT];		/* array with size recSize */
extern float an_freqSpecdB[AN_NFFT];
extern float an_freqSpecSmooth[AN_NFFT];
extern float an_tpr;
extern float an_smooth_delay[2];

#endif /* ANALYZER_H_ */
