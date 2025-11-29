/*
Group:4
Eric Santana
Hector Polanco
Kero Samaan
Mason Doan
ORG: CSULB
Class: CECS 347 Embedded System II
--------------------------
Description: ADC1 SS3 setup
*/
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "ADC1SS3.h"

// TODO
#define ADC1_PSSI_SS3 (0x0008)    // start sample sequencer 3
#define ADC1_ISC_SS3  (0x0008)    // acknowledge sample sequencer 3 interrupt
#define ADC1_RIS_SS3  (0x0008)

// This initialization function sets up the ADC1 Sample Sequencer 3 
// Max sample rate: <=125,000 samples/second
// SS3 triggering event: software trigger
// SS3 1st sample source: Ain8 (PE5)
// SS3 interrupts: flag set on completion but no interrupt requested
void ADC1SS3_Init(void){ 
	
	//GPIO setup
	
	SYSCTL_RCGCGPIO_R |= PORTE;
	while((SYSCTL_RCGCGPIO_R & PORTE) != PORTE);
	SYSCTL_RCGCADC_R |= ADC1;
	while((SYSCTL_RCGCADC_R & ADC1)!= ADC1);
	
	GPIO_PORTE_DEN_R &=~ E5_MASK; // Disable digital 
	GPIO_PORTE_DIR_R &=~ E5_MASK; // set as input
	GPIO_PORTE_AMSEL_R |= E5_MASK; // enable analog mode
	GPIO_PORTE_AFSEL_R |= E5_MASK; // enable alternate function
	

	ADC1_ACTSS_R &=~ 0x0008; // disable SS3 for setup
	
	ADC1_PC_R = 0x1; // 125k Sample Rate
	ADC1_SSPRI_R = 0x0123;// SS3 high pri
	ADC1_EMUX_R &=~ 0xF000;// Software trigger
	ADC1_SSMUX3_R = 8;// AIN 8 pin E5
	ADC1_SSCTL3_R = 0x0006;// start and end bits
	ADC1_IM_R &=~ 0x0008;// No interupt
	ADC1_ACTSS_R |= 0x0008;// enable SS3
	
}

//------------ADC1SS3_In------------

uint16_t ADC1SS3_In(void){ 
	// TODO: start ADC1 SS3 and read the ditigal output.
	uint16_t ADC_Value=0;
	
	ADC1_PSSI_R  |= 0x0008;// SS3 software trigger
	while((ADC1_RIS_R & 0x08)==0);//wait until conversion is done
	ADC_Value = ADC1_SSFIFO3_R & 0xFFF;
	
	ADC1_ISC_R = ADC1_ISC_SS3;   // clear completion flag

	return 	ADC_Value;
}

// Convert a ADC value to a value between [0, max_x_axis]
// convert a value range [0,4095] to a range of [0,83]
uint8_t ADCValue_To_X_AXIS(uint16_t ADCValue,uint8_t max_x_axis) {
	uint8_t x_position=0;
	
	x_position = (uint8_t)((ADCValue * max_x_axis) / 4095);
	
	if(x_position > max_x_axis){
		x_position = max_x_axis;
	}
	return x_position;
}
