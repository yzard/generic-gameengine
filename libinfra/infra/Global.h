#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <iostream>
#include "Time.h"

// a macro that determine which is the minimal
#define minimal(x,y) ((x) < (y) ? (x) : (y))

/*
 * System specific definitions
 */

// Copied from linux kernel header, for memory synchronization
// used for lock free FIFO algorithm
#define barrier() 	__asm__ __volatile__("": : :"memory")
#define mb()		barrier()
#define rmb()		barrier()
#define wmb()		barrier()


/*
 * Definition of Types and return values
 * Avoid of magical numbers
 */

// definition of return type globaly
#define ReturnValue	int32_t
#define RET_GOOD	0
#define	RET_FAIL	-1

// definition of task
#define TaskId		uint32_t

#endif /*  __GLOBAL_H__ */