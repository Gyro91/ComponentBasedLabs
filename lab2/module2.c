#include "module2.h"

unsigned char module_init2;

void init_module2()
{
    module_init2 = 1;
    
    printf("Module 2 initialized!\n");
}

void clean_up_module2()
{
    assert(module_init2);
    module_init2 = 0;
    printf("Module 2 destructed\n");
}

void f(float x)
{
    /* Check if the module is initialized*/
    assert(module_init2);

    printf("Hello World from module2! %f\n", sqrt(x));
}
