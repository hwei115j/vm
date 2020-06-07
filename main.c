#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "vm.h"

#define MEM 4096
#define error(...) pferror(__FILE__, __LINE__, __VA_ARGS__)
static inline void pferror(char *file, int line, char *fmt, ...)
{
    fprintf(stderr, "%s:%d: ", file, line);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}

int main(int argc, char *argv[])
{
    int i;
    int min = 4080, max = 4095;
    int flag[256] = {};
    char *file;
    char *cmd1 = "--dump-stack";
    char *cmd2 = "--dump-memory";

    for(i = 0; i < argc && !strstr(argv[i], "vm") ; i++);

    for(i++; i < argc; i++) {
        if(argv[i][0] == '-') {
            if(!strcmp(argv[i], cmd1)) {
                if(i+1 >= argc || !isdigit(argv[i+1][0])) 
                    min = 4080;
                else { 
                    sscanf(argv[i+1], "%d", &min);
                    i++;
                }
                flag['s'] = 1;
            } 
            else if(!strcmp(argv[i], cmd2)) {
                if(i+1 >= argc || !isdigit(argv[i+1][0])) {
                    max = 4095;
                    min = 4080;
                }
                else if(i+2 >= argc || !isdigit(argv[i+2][0])) {
                    sscanf(argv[i+1], "%d", &min);
                    max = min;
                    i++;
                }
                else if(isdigit(argv[i+1][0]) && isdigit(argv[i+2][0])) {
                    sscanf(argv[i+1], "%d", &min);
                    sscanf(argv[i+2], "%d", &max);
                    i+=2;
                }
                flag['m'] = 1;
            }
        }
        else
            file = argv[i];
    }
    if(!file) {
        printf("not file\n");
        return -1;
    }



    uint16_t memory[MEM];
    FILE *input = fopen(file, "rb");

    fread(memory, sizeof(uint16_t), MEM, input);
    virtual(memory);

    if(max < min) {
        int r = min;
        min = max;
        max = r;
    }
    for(i = max; i >= min; i--)
        printf("%d = %d\n",i, memory[i]);
    fclose(input);
    return 0;
}
