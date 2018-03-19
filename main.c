#include <stdio.h>
#include "vm.h"

int main()
{
    uint16_t memory[4096] = {};
    int i;

    memory[0] = 0x2100;
    memory[1] = 0x3102;
    memory[2] = 0x7800;
    memory[3] = 0xA102;
    memory[4] = 0x3101;
    memory[5] = 0x2102;
    memory[6] = 0x7020;
    memory[7] = 0x3102;
    memory[8] = 0x2101;
    memory[9] = 0x9102;
    memory[10] = 0x3101;
    memory[11] = 0x2102;
    memory[12] = 0x7020;
    memory[13] = 0x3102;
    memory[14] = 0x2101;
    memory[15] = 0xB102;
    memory[16] = 0x6103;
    memory[17] = 0x4003;
    memory[18] = 0x7001;
    
    memory[0x100] = 1024;
    memory[0x101] = 0;
    memory[0x102] = 0;
    memory[0x103] = -18;

    memory[1024] = 1;
    memory[1025] = 1;
    virtual(memory);
    
    for(i = 1024; i < 1044; i++)
        printf("%u\n", memory[i]);

    return 0;
}
