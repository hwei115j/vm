#include <stdio.h>
#include "vm.h"

int main()
{
    uint16_t memory[4096] = {};
    int i;

    memory[0] = 0x2100;
    memory[1] = 0x1101;
    memory[2] = 0x3102;
    memory[3] = 0x7001;
    memory[0x100] = 0xa;
    memory[0x101] = 0x14;
    memory[0x102] = 0x0;

    virtual(memory);
    
    for(i = 0x100; i < 0x105; i++)
        printf("%x = %u\n",i, memory[i]);

    return 0;
}
