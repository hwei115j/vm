#include <stdio.h>
#define MAX 110
#define STR 20
typedef struct 
{
    char label[STR], code[STR], para[STR];
    int lc, i;
}asmcode;

typedef struct 
{
    char op[STR];
    int num;
}optab;

int first_pass(asmcode *, FILE *);
int second_pass(asmcode *);
int func(char *);
void clean(char *);
void tabset(asmcode *, char *);
void print_code(asmcode *, int);


int islabel(char *);
int iscode(char *);
int ispara(char *);
int isi(char *);
int isblank_(char *);

int decode(char *);
int depara(asmcode *, char *);
int16_t hex(int , int);
void err(void);