/*
Group:4
Eric Santana
Hector Polanco
Kero Samaan
Mason Doan
ORG: CSULB
Class: CECS 347 Embedded System II
--------------------------
Description: Use SW1 to fire a bullet and SW2 to start the game
*/
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "switch.h"

// Initialize the onboard two switches.
void Switch_Init(void){
	
	// Configure PortF
	
	SYSCTL_RCGCGPIO_R |= PORTF; // Start port F clock
	while((SYSCTL_RCGCGPIO_R & PORTF) != PORTF); // wait for clk to initialize
	
	GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock Port F
	GPIO_PORTF_CR_R |= 0x1F;        // allow changes to PF4–PF0
	
	// Configure LEDS
	GPIO_PORTF_DEN_R |= LEDS; // Enable digital mode
	GPIO_PORTF_DIR_R |= LEDS; // set LED's as output
	GPIO_PORTF_AMSEL_R &=~ LEDS;// Disable analog mode
	GPIO_PORTF_AFSEL_R &=~ LEDS;// Disable alternate function mode
	
	// Configure on board Switches
	// Sw pressed | 5v -> 0v
	GPIO_PORTF_DIR_R &=~ SWITCHES; // Set Sw1 & Sw2 as input
	GPIO_PORTF_DEN_R |= SWITCHES;// Enable digital mode
	GPIO_PORTF_PUR_R |= SWITCHES;// Enable pull up resistor
	GPIO_PORTF_AMSEL_R &=~ SWITCHES; // Disable analog mode
	GPIO_PORTF_AFSEL_R &=~ SWITCHES; // Disable alternate functions
	
	// Configure SW1 & SW2 interutps
	
	GPIO_PORTF_IS_R &=~ SWITCHES; // Edge interupt
	GPIO_PORTF_IBE_R &=~ SWITCHES; // Not both edges
	GPIO_PORTF_IEV_R &=~ SWITCHES; // Falling edge
	GPIO_PORTF_ICR_R = SWITCHES;// Clear any prior interupt flags
	GPIO_PORTF_IM_R |= SWITCHES; // Arm interupts
	
	NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | LEVEL1;	// Set priority level 1
	NVIC_EN0_R |= 0x40000000; // Enable PortF Handler interupt
	
	
	
	
	
}
