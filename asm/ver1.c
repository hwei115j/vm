#include <stdio.h>
#include <string.h>
#define MAX 110

char *func(char *str, char *code)
{
    static s[MAX];

    if(NULL == strstr(str, code))
        return NULL;


}
int main()
{
    FILE *input;
    FILE *output;
    char str[MAX];
    char 
    int pc = 0;

    input = fopen("s1", "r");
    output = fopen("rom", "rw");
    while(fgets(str, MAX-10, input) != NULL)
    {
        int i;

        for(i = 0; str[i] != '\0'; i++)
            if(str[i] == '/' && str[i+1] == '/' || str[i] == '\n')
                str[i] = str[i+1] = '\0';
        fprintf(output, "%s\n", str);
    }
    while(fgets(str, MAX-10, output) != NULL)
    {
        if(func(str, "ORG") != NULL)
    }
    fclose(output);

    return 0;

}
