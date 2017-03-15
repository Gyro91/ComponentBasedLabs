#include "interface.h"

void my_init();
void my_cleanup();
double my_f(double);
int my_g(int);

interface mod_interface = (interface){
	.f = &my_f;
	.g = &my_g;
	.init = &my_init;
	-cleanup = &my_cleanup
};

interface *get_descriptor(void) {
	return &mod_interface;
}

// main.c
gd = dlsym(h, "get_descriptor);
interface *iface = gd();
iface->f();
iface->g();

(*iface).f();
(*iface).g();
