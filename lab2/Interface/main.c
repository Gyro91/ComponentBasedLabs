#include <dlfcn.h>
#include <stdio.h>
#include "interface.h"

interface *(*get_des)(void);


int main()
{
    interface *iface;
    void *handle_dll;
    
    handle_dll = dlopen("libinterfaceImpl.so", RTLD_NOW);
    if (!handle_dll) {
	fprintf(stderr, "%s\n", dlerror());
        return 1;
     }
    
    get_des = dlsym(handle_dll, "get_descriptor");
    
    iface = get_des();

    iface->f(3.14);
    iface->g(1);
    
    dlclose(handle_dll);

    return 0;
}
