#include <stdio.h>
#include <string.h>
#include "ash.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("ERROR!\n");
        return -1;
    }

    int count;
    FILE *input = fopen(argv[1], "r");
    asmcode arr[MAX];
    
    count = first_pass(arr, input);
    second_pass(arr);
//    print_code(arr, count);

    return 0;

}
