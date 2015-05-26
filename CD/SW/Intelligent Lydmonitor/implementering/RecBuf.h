/*
 * RecBuf.h
 *
 *  Created on: 18/05/2015
 *      Author: Kristian
 */

#ifndef RECBUF_H_
#define RECBUF_H_

//includes
#include "Talkthrough.h"

//defines
#define RB_SIZE 2048 /* Must be power of two. 4096 creates errors */
#define RB_MEM_0 0
#define RB_MEM_1 1

//Attributes
extern fract32 rb_mem0[RB_SIZE];
extern fract32 rb_mem1[RB_SIZE];
extern bool rb_currActiveBuffer;
extern unsigned int rb_index;
extern bool rb_ready;

//Prototypes
void rb_init(void);
void rb_storeData(fract32 sample);
void rb_print(void); //for test

#endif /* RECBUF_H_ */
