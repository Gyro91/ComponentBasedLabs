#ifndef __module2_h__
#define __module2_h__

#include <assert.h>
#include <stdio.h>
#include <math.h>

#endif

extern void init_module2(void) __attribute((constructor));
extern void clean_up_module2(void) __attribute((destructor));
extern void f(float x);
