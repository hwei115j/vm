#include <stdio.h>
#define MAX 110

int main()
{
    FILE *input;
    FILE *output;
    char str[MAX];

    input = fopen("./s1", "r");
    output = fopen("./rom", "w");
    while(fgets(str, MAX-10, input) != NULL)
    {
        int i;

        for(i = 0; str[i] != '\0'; i++)
            if(str[i] == '/' && str[i+1] == '/' || str[i] == '\n')
                str[i] = str[i+1] = '\0';
        fprintf(output, "%s\n", str);
    }
    fclose(output);

    return 0;

}
