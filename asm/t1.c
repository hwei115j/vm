#include<stdio.h>
#define MAX 20

int main()
{
    uint16_t num[MAX] = {1, 1};
    int i;

    for(i = 2; i < MAX; i++)
        num[i] = num[i-1] + num[i-2];
    for(i = 0; i < MAX; i++)
        printf("%d ", num[i]);
    printf("\n");

    return 0;
}
