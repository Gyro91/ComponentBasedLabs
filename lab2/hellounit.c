#include "hellounit.h"

unsigned char module_init;

void init()
{
    module_init = 1;
    
    printf("Module initialized!\n");
}

void clean_up()
{
    assert(module_init);
    module_init = 0;
    printf("Module destructed\n");
}

void f(float x)
{
    /* Check if the module is initialized*/
    assert(module_init);

    printf("Hello World! %f\n", sqrt(x));
}

