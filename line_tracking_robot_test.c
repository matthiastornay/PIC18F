/*
Code : LINE TRACKING ROBOT based on a PIC18F252
Author : Matthias Tornay
Date : 05/2018
Software : MPLAB X

Test program of the line following robot
(digital version) of which the board has
been conceived in practical work classes.

PIC is used to compute the sensors data
and generate the PWM signals for the motors.

*/

#include <xc.h>

#pragma config OSC = HS
#pragma config PWRT = ON
#pragma config BOR = OFF
#pragma config WDT = OFF
#pragma config DEBUG = ON
#pragma config LVP = OFF

#define _XTAL_FREQ 10000000 //Quartz 10MHz

#define LOGIC_L_CAPT PORTBbits.RB1
#define LOGIC_R_CAPT PORTBbits.RB0
#define ANALOGIC_L_CAPT PORTAbits.RA1
#define ANALOGIC_R_CAPT PORTAbits.RA0
#define L_MOTOR PORTCbits.RC2
#define R_MOTOR PORTCbits.RC1
#define DIRECT_LOGIC_L_CAPT TRISBbits.TRISB1
#define DIRECT_LOGIC_R_CAPT TRISBbits.TRISB0
#define DIRECT_ANALOGIC_L_CAPT TRISAbits.TRISA1
#define DIRECT_ANALOGIC_R_CAPT TRISAbits.TRISA0
#define DIRECT_L_MOTOR TRISCbits.TRISC2
#define DIRECT_R_MOTOR TRISCbits.TRISC1

#define GO ADCON0bits.GO

unsigned char conversion(unsigned char channel); // Convert the DAC data from the IR LEDs

void main(void) {

	TRISCbits.RC1 = 0;
	TRISCbits.RC2 = 0;

	PORTCbits.RC1 = 0;
	PORTCbits.RC2 = 0;

	// PWM configuration
	CCP1CON = 0x0C;
	CCP2CON = 0x0C;

	PR2 = 255

	T2CON = 0x04;

	ADCON1 = 0x00;

	while(1) {

		CCPR2L = conversion(1);
		CCPR1L = conversion(0);
		
	}

	return;

}

unsigned char conversion(unsigned char channel) {

	(channel) ? ADCON0 = 0x4D : ADCON0 = 0x45; // ADCON0 = 0x4D if channel, 0x45 otherwise
	
	__delay_us(13); // Acquisition time

	GO = 1; // Start the conversion
	while(GO); // Wait for the flag

	__delay_us(10);

	return ADRESH;

}
