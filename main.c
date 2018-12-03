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
   
    printf("\n");
    for(i = 0x3ED; i < 0x3F7; i++)
        printf("%x = %hd\n",i, memory[i]);
    fclose(input);
    return 0;
}
