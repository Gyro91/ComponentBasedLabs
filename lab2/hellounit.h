
#ifndef __hellounit_h__
#define __hellounit_h__

#include <assert.h>
#include <stdio.h>
#include <math.h>

#endif

extern void init(void) __attribute((constructor));
extern void clean_up(void) __attribute((destructor));
extern void f(float x)__attribute__((weak));
