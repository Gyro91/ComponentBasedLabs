#define _GNU_SOURCE_
#include <math.h>
#include <dlfcn.h>
#include <stdio.h>

void (*f)(float);

int main()
{
    void *handle_dll;
    
    handle_dll = dlopen("libhellounit.so", RTLD_NOW);
    if (!handle_dll) {
	fprintf(stderr, "%s\n", dlerror());
        return 1;
     }
    
    f = dlsym(handle_dll, "f");
    
    f(9.0);
    
    dlclose(handle_dll);

    return 0;
}
