/*
Group:4
Eric Santana
Hector Polanco
Kero Samaan
Mason Doan
ORG: CSULB
Class: CECS 347 Embedded System II
--------------------------
Description: 10Hz screen update
*/

#include "Systick.h"
#include "tm4c123gh6pm.h"

#define RELOADVALUE 8000000 // 100ms delay


void SysTick_Init(void){
	 NVIC_ST_CTRL_R = 0;             // disable SysTick
   NVIC_ST_RELOAD_R = 8000000 - 1; // 0.1 sec at 80 MHz (10 Hz)
   NVIC_ST_CURRENT_R = 0;          // any write clears current
   NVIC_ST_CTRL_R = 0x07;          // enable SysTick with core clock and interrupts
}


void SysTickDelay3s(void){
	
		//30 x 100ms = 3000ms = 3s
	
    for(int i = 0; i < 30; i++){
        while(!time_to_draw) { }  // wait for 100 ms tick
        time_to_draw = false;     // consume the tick
    }
}

