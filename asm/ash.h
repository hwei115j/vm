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

int first_pass(asmcode *);
int second_pass(asmcode *, optab *);
int func(char *);
void clean(char *);
void tabset(asmcode *, char *);
void print_code(asmcode *, int);


int islabel(char *);
int iscode(char *);
int ispara(char *);
int isi(char *);
int isblank_(char *);

void err(void);
