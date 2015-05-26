/*
 * Prefilter.h
 *
 *  Created on: 19/05/2015
 *      Author: Lukas
 */

#ifndef PREFILTER_H_
#define PREFILTER_H_

#include "Talkthrough.h"

/* DEFINES */
	#define PF_TEST 1

	/* FIR Decimation defines */
	#define PF_DEC_DECIMATION 2
	#define PF_DEC_COEFFS 34 //67 for DEC = 4
	#define PF_DEC_INSAMPLES PF_DEC_DECIMATION
	#define PF_DEC_OUTSAMPLES (PF_DEC_INSAMPLES / PF_DEC_DECIMATION)

	#define PF_HIGHPASS_ON false

	/* FIR HighPass defines */
	#define PF_HIGHPASS_FIR true	//false for testing IIR filter
	#define PF_HP_COEFFS 61
	#define PF_HP_SAMPLES PF_DEC_OUTSAMPLES

	/* IIR HighPass defines */
	#define PF_HP_STAGES 1
	#define PF_HP_SAMPLES PF_DEC_OUTSAMPLES
	#define PF_HP_SCALE 2		/* to scale B-coeffs into the fract range
							 	 * (must be a power of 2) 	*/

/* METHODS */
	void pf_initDecima(void);
	void pf_initIIRHighPass(void);
	void pf_initFIRHighPass(void);
	void pf_sampleRdy(fract32 sample);

/* ATTRIBUTES */
	//RecBuf* recBufPtr;
	extern fract32 pf_decima_input[PF_DEC_INSAMPLES];
	extern fract32 pf_decima_output[PF_DEC_OUTSAMPLES];
	extern unsigned int pf_decima_count;
	extern fract32 pf_hp_output[PF_HP_SAMPLES];

	/* Coefficients and delay line for the filter functions
	 * (use separate memory banks for best performance) */
	#pragma section("L1_data_a")
	extern fract32 pf_hp_fir_coeffs[PF_HP_STAGES * 5];
	#pragma section("L1_data_b")
	extern fract32 pf_hp_fir_delay[PF_HP_STAGES * 2];
	extern fir_state_fr32 pf_hp_fir_state;

	#pragma section("L1_data_a")
	extern fract32 pf_hp_iir_coeffs[PF_HP_STAGES * 5];
	#pragma section("L1_data_b")
	extern fract32 pf_hp_iir_delay[PF_HP_STAGES * 2];
	extern iir_state_fr32 pf_hp_iir_state;

#endif /* PREFILTER_H_ */
