#ifndef __INTERFACE_H__
#define __INTERFACE_H__

typedef struct {
	void (*init)(void);
	void (*cleanup)(void);
	double (*f)(double);
	int (*g)(int);
} interface;

extern interface *get_descriptor(void);

#endif
