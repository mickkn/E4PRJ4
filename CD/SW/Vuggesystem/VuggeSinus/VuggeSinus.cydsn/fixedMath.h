#ifndef _FIXEDMATH_H_
#define _FIXEDMATH_H_
/* ========================================
 *
 * This C module contains the necessary 
 * 16.16 fixed point functions.
 * the atan2 implementation is based on 
 * Jim Shima's 1999/04/23 public domain
 * self normalizing atan 2 algorithm. 
 * see: 
 * http://dspguru.com//dsp/tricks/fixed-point-atan2-with-self-normalization
 *
 * ========================================
*/

#include <project.h>

#define half_pi 0x0001921F
typedef int32_t fix16_t;

//get absolute value
fix16_t fix16abs(fix16_t a);
    
//multiplication
fix16_t fix16mul(fix16_t a, fix16_t b);

//division (divide a by b)
fix16_t fix16div(fix16_t a, fix16_t b);

//sine of theta in radians
fix16_t fix16sin(fix16_t theta);

//cosine of theta in radians
fix16_t fix16cos(fix16_t theta);

//arcus tangent returning right quadrant
fix16_t fix16atan2(fix16_t y, fix16_t x);

//convert from radians to deg
fix16_t fix16rad2deg(fix16_t radAng);

//cordic calculations of sine and cosine
void cordic(int theta, int* s, int* c, int n);

#endif
/* [] END OF FILE */
