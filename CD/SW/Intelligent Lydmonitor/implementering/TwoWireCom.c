/*
 * TwoWireCom.c
 *
 *  Created on: 19/05/2015
 *      Author: Hedegaard & Boye
 */

#include "TwoWireCom.h"
#include "adi_initialize.h"
#include <sys\exception.h>
#include <cdefBF533.h>
#include "sysreg.h"
#include "ccblkfn.h"

void tw_init(void)
{
	/* Set pin direction */
	*pFIO_DIR |= TW_OUTPUT_PIN_LSB;
	*pFIO_DIR |= TW_OUTPUT_PIN_MSB;

	/* Set to babycon 3*/
	tw_send(3);
}

void tw_send(int bc)
{
	switch(bc)
	{
	case 1:	//babycon_level = 1, must set GPIO OUTPUT_PIN_MSB = 0, OUTPUT_PIN_LSB = 1.
		*pFIO_FLAG_S = TW_OUTPUT_PIN_LSB; // Pointer to BANKS' GPIO write to set register (Set high)
		*pFIO_FLAG_C = TW_OUTPUT_PIN_MSB; //Pointer to BANKS' GPIO Write to Clear register (set low)
		break;

	case 2:
		//babycon_level = 2, must set GPIO OUTPUT_PIN_MSB = 1, OUTPUT_PIN_LSB = 0.
		*pFIO_FLAG_S = TW_OUTPUT_PIN_MSB;
		*pFIO_FLAG_C = TW_OUTPUT_PIN_LSB;
		break;

	case 3:
		//babycon_level = 3, must set GPIO OUTPUT_PIN_MSB = 1, OUTPUT_PIN_LSB = 1.
		*pFIO_FLAG_S = TW_OUTPUT_PIN_LSB;
		*pFIO_FLAG_S = TW_OUTPUT_PIN_MSB;
		break;
	default:
		//babycon_level != 1-3, must set GPIO OUTPUT_PIN_MSB = 0, OUTPUT_PIN_LSB = 0 for error
		*pFIO_FLAG_C = TW_OUTPUT_PIN_MSB;
		*pFIO_FLAG_C = TW_OUTPUT_PIN_LSB;
		break;
	}
}

