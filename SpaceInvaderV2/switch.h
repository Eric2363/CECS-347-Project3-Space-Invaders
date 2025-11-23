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

// Port F 
#define PORTF 0x20

// GREEN,BLUE,RED leds
#define LEDS 0x0E
#define GREEN 0x08
#define BLUE 0x04
#define RED	0x02

//Switches
#define SWITCHES 0x11
#define SW1 0x10
#define SW2 0x01

//Interupt Level
#define LEVEL1 0x00200000

// Initialize the onboard two switches.
void Switch_Init(void);
