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

//atan2 defines
#define COEFF1  51472  // pi/4 * 2^16
#define COEFF2 154416  // COEFF1 * 3

//cordic defines
// 1.0 = 65536
// 1/k = 0.6072529350088812561694
// pi = 3.1415926536897932384626
//Constants
#define cordic_1K 0x00009B74
#define MUL 65536.000000
#define CORDIC_NTAB 18
int cordic_ctab [] = {0x0000C90F, 0x000076B1, 0x00003EB6, 0x00001FD5, 0x00000FFA,
                    0x000007FF, 0x000003FF, 0x000001FF, 0x000000FF, 0x0000007F, 
                    0x0000003F, 0x0000001F, 0x0000000F, 0x00000007, 0x00000003, 
                    0x00000001, 0x00000000, 0x00000000, };

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

// This is a wrapper function for the cordic implementation of sine calculations.
fix16_t fix16sin(fix16_t rads)
{
    fix16_t s, c;
    cordic(rads, (int*) &s, (int*) &c, 32);
    return s;
}

// This is a wrapper function for the cordic implementation of cosine calculations.
fix16_t fix16cos(fix16_t rads)
{
    fix16_t s, c;
    cordic(rads, (int*) &s, (int*) &c, 32);
    return c;
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

//Cordic sine and cosine calculations

void cordic(int theta, int *s, int *c, int n)
{
  int k, d, tx, ty, tz;
  int x=cordic_1K,y=0,z=theta;
  n = (n>CORDIC_NTAB) ? CORDIC_NTAB : n;
  for (k=0; k<n; ++k)
  {
    d = z>>17;
    //get sign. for other architectures, you might want to use the more portable version
    //d = z>=0 ? 0 : -1;
    tx = x - (((y>>k) ^ d) - d);
    ty = y + (((x>>k) ^ d) - d);
    tz = z - ((cordic_ctab[k] ^ d) - d);
    x = tx; y = ty; z = tz;
  }
 *c = x; *s = y;
}

/* [] END OF FILE */
