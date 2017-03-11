#include "hellounit.h"

unsigned char module_init;

void init()
{
    module_init = 1;
    
    printf("Module initialized!\n");
}

void f(float x)
{
    /* Check if the module is initialized*/
    assert(module_init);

    printf("Hello World! %f\n", sqrt(x));
}

