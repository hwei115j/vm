#include <stdio.h>
#include <string.h>
#include "ash.h"

int main()
{
    int count;
    asmcode arr[MAX];
//    optab   *tab = init_tab();
    
    count = first_pass(arr);
    print_code(arr, count);

    return 0;

}
