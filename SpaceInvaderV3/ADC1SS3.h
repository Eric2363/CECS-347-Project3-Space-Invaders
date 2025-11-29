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
#include <stdint.h>


//GPIO Setup Port E

#define PORTE 0x10
#define E5_MASK 0x20

//ADC Setup
#define ADC1 0x00000002
#define SR_125k 0x1

// This initialization function sets up the ADC1 Samplw Sequencer 3 
// Max sample rate: <=125,000 samples/second
// SS3 triggering event: software trigger
// SS3 1st sample source: Ain9 (PE5)
// SS3 interrupts: flag set on completion but no interrupt requested
void ADC1SS3_Init(void); 

//------------ADC1SS3_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion

uint16_t ADC1SS3_In(void); 

uint8_t ADCValue_To_X_AXIS(uint16_t ADCValue, uint8_t max_x_axis);
