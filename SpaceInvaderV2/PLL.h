/*
Group:4
Eric Santana
Hector Polanco
Kero Samaan
Mason Doan
ORG: CSULB
Class: CECS 347 Embedded System II
--------------------------
Description: PLL setup 80Mhz
*/
#define SYSDIV2  4 
// bus frequency is 400MMHz/(SYSDIV+1)

void PLL_Init(void);
