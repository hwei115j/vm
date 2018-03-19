#include <stdbool.h>
#include <stdint.h>

#define AND 0
#define ADD 1
#define LDA 2
#define STA 3
#define BUN 4
#define BSA 5
#define ISZ 6
#define CLA 7
#define CLE 8
#define CMA 9
#define CME 10
#define CIR 11
#define CIL 12
#define INC 13
#define SPA 14
#define SNA 15
#define SZA 16
#define SZE 17
#define HLT 18
#define INP 19
#define OUT 20
#define SKI 21
#define SKO 22
#define ION 23
#define IOF 24

#define GET_HIGH4 12
#define BK_HIGH4  0x0FFF
#define BK_MSB    0x7FFF
#define MSB       0x8000
#define LSB       0x0001
void virtual(uint16_t *);
