/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "fixedMath.h"
#include "stdlib.h"

#define RAD_TO_DEG_SCALE 3754936 // ((360 deg) / (2 * pi rad)) * 2^16

#define COEFF1  51472  // pi/4 * 2^16
#define COEFF2 154416  // COEFF1 * 3

fix16_t fix16abs(fix16_t a)
{
    if(a < 0) return -a; 
    else return a;
}

fix16_t fix16mul(fix16_t a, fix16_t b)
{
    return (fix16_t)(((int64_t) a * (int64_t) b) >> 16);
}

fix16_t fix16div(fix16_t a, fix16_t b)
{
    return (fix16_t) (((int64_t)a << 16) / b);

}

/* atan2 implementation is based on Jim Shima's 1999/04/23 algorithm             *
 * see: http://dspguru.com//dsp/tricks/fixed-point-atan2-with-self-normalization */
fix16_t fix16atan2(fix16_t y, fix16_t x)
{
    fix16_t abs_y = fix16abs(y)+1;      // kludge to prevent 0/0 condition
    fix16_t angle;
    if (x>=0)
    {
        fix16_t r = fix16div((x - abs_y),  (x + abs_y));
        angle = COEFF1 - fix16mul(COEFF1, r);
    }
    else
    {
        fix16_t r = fix16div((x + abs_y), (abs_y - x));
        angle = COEFF2 - fix16mul(COEFF1, r);
    }
    if (y < 0) return(-angle);     // negate if in quad III or IV
    else return(angle);
}

fix16_t fix16rad2deg(fix16_t radAng)
{
    return fix16mul(radAng, RAD_TO_DEG_SCALE);
}


/* [] END OF FILE */
