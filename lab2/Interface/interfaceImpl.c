#include "interface.h"
#include <math.h>
#include <stdio.h>

void my_init(){;}
void my_cleanup(){;}

double my_f(double a)
{
    double radq;

    radq = sqrt(a);
    printf("%f\n", radq);

    return radq;
}

int my_g(int a)
{
    int c;

    c = a + 1;
    printf("%d\n",c);

    return c;
}

interface mod_interface = {
	.init = &(my_init),
	.cleanup = &(my_cleanup),
	.f = &(my_f),
	.g = &(my_g),
};

interface *get_descriptor(void)
{
    return &(mod_interface);
}
