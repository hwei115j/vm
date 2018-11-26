#include <stdio.h>
#include "vm.h"
#define MEM 4096

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("ERROR!%d", argc);
        return -1;
    }

    uint16_t memory[MEM];
    FILE *input = fopen(argv[1], "rb");
    int i;
    
    fread(memory, sizeof(uint16_t), MEM, input);
    virtual(memory);
    
    for(i = 0x0; i < 0x10; i++)
        printf("%x = %hd\n",i, memory[i]);
    fclose(input);
    return 0;
}
