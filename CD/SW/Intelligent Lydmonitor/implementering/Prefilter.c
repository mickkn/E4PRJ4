/*
 * Prefilter.c
 *
 *  Created on: 19/05/2015
 *      Author: Hedegaard & Boye
 */

#ifndef PREFILTER_C_
#define PREFILTER_C_

#include "Prefilter.h"

/* ATTRIBUTES */
//RecBuf* recBufPtr;
fract32 pf_decima_input[PF_DEC_INSAMPLES];
fract32 pf_decima_output[PF_DEC_OUTSAMPLES];
unsigned int pf_decima_count;
fract32 pf_hp_output[PF_HP_SAMPLES];

/* Coefficients and delay line for the filter functions
 * (use separate memory banks for best performance) */
#pragma section("L1_data_a")
fract32 pf_decima_coeffs[PF_DEC_COEFFS];
#pragma section("L1_data_b")
fract32 pf_decima_delay[PF_DEC_COEFFS];
fir_state_fr32 pf_decima_state;

#pragma section("L1_data_a")
fract32 pf_hp_fir_coeffs[PF_HP_STAGES * 5];
#pragma section("L1_data_b")
fract32 pf_hp_fir_delay[PF_HP_STAGES * 2];
fir_state_fr32 pf_hp_fir_state;

#pragma section("L1_data_a")
fract32 pf_hp_iir_coeffs[PF_HP_STAGES * 5];
#pragma section("L1_data_b")
fract32 pf_hp_iir_delay[PF_HP_STAGES * 2];
iir_state_fr32 pf_hp_iir_state;

/* METHODS */
void pf_initDecima(void)
{
	/* Clear input buffer */
	int i;
	for (i = 0; i < PF_DEC_INSAMPLES; i++) /* clear the buf line */
		pf_decima_input[i] = 0;
	pf_decima_count = 0;

	/* Clear the delay line */

	for (i = 0; i < PF_DEC_COEFFS; i++)
		pf_decima_delay[i] = 0;

	/* Set FIR LP-filter coefficients */
	float FIR_coeffs[PF_DEC_COEFFS] = {
			-0.001515603015026F,-0.001197321235543F,-0.000162377229104F,
			0.002007097428441F, 0.004999844177995F, 0.007169100219368F,
			0.005883929182627F,-0.000946918098159F,-0.012809250681504F,
			-0.025235218667458F,-0.030363789714498F,-0.019735100768254F,
			0.011623756610677F, 0.061726144399357F, 0.120708742345494F,
			0.173377185422071F, 0.204469779623516F, 0.204469779623516F,
			0.173377185422071F, 0.120708742345494F, 0.061726144399357F,
			0.011623756610677F,-0.019735100768254F,-0.030363789714498F,
			-0.025235218667458F,-0.012809250681504F,-0.000946918098159F,
			0.005883929182627F, 0.007169100219368F, 0.004999844177995F,
			0.002007097428441F,-0.000162377229104F,-0.001197321235543F,
			-0.001515603015026F	};

	int k;
	for (k = 0; k < PF_DEC_COEFFS; k++) {
		pf_decima_coeffs[k] = float_to_fr32 (FIR_coeffs[k]);
	}

	fir_init (pf_decima_state, pf_decima_coeffs, pf_decima_delay, PF_DEC_COEFFS, PF_DEC_DECIMATION);
}

void pf_initFIRHighPass(void)
{
	/* Clear the delay line */
	int i;
	for (i = 0; i < PF_HP_COEFFS; i++)
		pf_hp_fir_delay[i] = 0;

	/* Set FIR LP-filter coefficients */
	float FIR_coeffs[PF_HP_COEFFS] = {
			-0.000600551485636F,-0.000689132718503F,-0.000828685971823F,-0.001031054741787F,-0.001307220335541F,-0.001666947547430F,
			-0.002118451803117F,-0.002668097379513F,-0.003320135629459F,-0.004076491201947F,-0.004936603074857F,-0.005897325837906F,
			-0.006952895115395F,-0.008094959342885F,-0.009312678354862F,-0.010592887450048F,-0.011920323826959F,-0.013277910574205F,
			-0.014647091805978F,-0.016008211098379F,-0.017340924147733F,-0.018624635573490F,-0.019838949054830F,-0.020964119543734F,
			-0.021981496151826F,-0.022873944469459F,-0.023626237540202F,-0.024225405470622F,-0.024661034684302F,-0.024925509102958F,
			0.975553293859308F,-0.024925509102958F,-0.024661034684302F,-0.024225405470622F,-0.023626237540202F,-0.022873944469459F,
			-0.021981496151826F,-0.020964119543734F,-0.019838949054830F,-0.018624635573490F,-0.017340924147733F,-0.016008211098379F,
			-0.014647091805978F,-0.013277910574205F,-0.011920323826959F,-0.010592887450048F,-0.009312678354862F,-0.008094959342885F,
			-0.006952895115395F,-0.005897325837906F,-0.004936603074857F,-0.004076491201947F,-0.003320135629459F,-0.002668097379513F,
			-0.002118451803117F,-0.001666947547430F,-0.001307220335541F,-0.001031054741787F,-0.000828685971823F,-0.000689132718503F,
			-0.000600551485636F};


	int k;
	for (k = 0; k < PF_HP_COEFFS; k++) {
		pf_hp_fir_coeffs[k] = float_to_fr32 (FIR_coeffs[k]);
	}

	fir_init (pf_hp_fir_state, pf_hp_fir_coeffs, pf_hp_fir_delay, PF_HP_COEFFS, 0);
}

void pf_initIIRHighPass(void)
{
	/* Zero delay line to start or reset the filter */
	int i;
	for (i = 0; i < (PF_HP_STAGES * 2); i++)
		pf_hp_iir_delay[i] = 0;

	/* Filter coefficients generated by a filter design
	 * tool that uses a direct form II */

	const struct {
		float a0;
		float a1;
		float a2;
	} A_coeffs[PF_HP_STAGES] = {
		0.500000000000000F,  -0.953750813023038F,   0.455797248299980F
		//Insert A_coeffs for second stage here
	};

	const struct {
		float b0;
		float b1;
		float b2;
	} B_coeffs[PF_HP_STAGES] = {
		0.477387015330755F,  -0.954774030661509F,  0.477387015330755F
		//Insert B_coeffs for second stage here
	};

	/*  Transform the A-coefficients and B-coefficients from a
		filter design tool into the form required by iir_fr32
		-> A0 coefficients are assumed to be 1.0, and are not
		passed to the iir function
		-> A1 and A2 coefficients must be scaled against the A0
		coefficient (use the iirdf1_fr32 function instead if
		the A1 and A2 coefficients are larger than A0)
		-> scale the B coefficients to fit into the fractional
		range [-1..1); the scale factor must be a power of 2 	*/

	int k;
	for (k = 0; k < PF_HP_STAGES; k++) {
		pf_hp_iir_coeffs[(5*k)+0] = float_to_fr32 (A_coeffs[k].a2);
		pf_hp_iir_coeffs[(5*k)+1] = float_to_fr32 (A_coeffs[k].a1);
		pf_hp_iir_coeffs[(5*k)+2] = float_to_fr32 (B_coeffs[k].b2);
		pf_hp_iir_coeffs[(5*k)+3] = float_to_fr32 (B_coeffs[k].b1);
		pf_hp_iir_coeffs[(5*k)+4] = float_to_fr32 (B_coeffs[k].b0);
	}

	/* Configure filter state */
	iir_init (pf_hp_iir_state, pf_hp_iir_coeffs, pf_hp_iir_delay, PF_HP_STAGES);
}

void pf_sampleRdy(fract32 sample)
{
	pf_decima_input[pf_decima_count] = sample; //=value in adc
	pf_decima_count = (pf_decima_count+1)%PF_DEC_INSAMPLES;

	/* if full buf */
	if(pf_decima_count == PF_DEC_INSAMPLES-1)
	{
		/* PROCESS DATA */

		/* Decimate */
		fir_decima_fr32 (pf_decima_input, pf_decima_output /*output*/, PF_DEC_INSAMPLES, &pf_decima_state);

		/* Highpass on/off */
		if(PF_HIGHPASS_ON)
		{
			if(PF_HIGHPASS_FIR)
			{
				fir_fr32(pf_decima_output, pf_hp_output, PF_HP_SAMPLES, &pf_hp_fir_state);
			}
			else
			{
				iir_fr32 (pf_decima_output /*hp_input*/, pf_hp_output, PF_HP_SAMPLES, &pf_hp_iir_state);

				int k;
				for (k = 0; k < PF_HP_SAMPLES; k++)
				{
					/* Undo scaling B coefficients */
					pf_hp_output[k] = pf_hp_output[k] << PF_HP_SCALE;
				}
				for (k = 0; k < (PF_HP_STAGES * 2); k++)
					pf_hp_iir_delay[k] = pf_hp_iir_delay[k] << PF_HP_SCALE;
			}
		}
		else
		{
			pf_hp_output[0] = pf_decima_output[0];
		}
		/* Calling RecBuf */
		rb_storeData(pf_hp_output[0]);
	}

	iChannel0LeftOut = pf_hp_output[0];
	iChannel0RightOut = pf_hp_output[0];

}

#endif /* PREFILTER_C_ */
