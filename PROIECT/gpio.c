#include "gpio.h"
#include "Uart.h"
#define SWITCH_PIN (12) // PORT A

#define LED_1 (1) // Segmentul de sus cu PTC1   
#define LED_2 (2) // Segmentul din dreapta-sus cu PTC2  
#define LED_3 (4)	// Segmentul din dreapta-jos cu PTD4       
#define LED_4 (4) // Segmentul de jos cu PTA4       
#define LED_5 (5) // Segmentul din stanga jos cu PTA5
#define LED_6 (8) // Segmentul din stanga sus cu PTC8
#define LED_7 (9) // Segemtul mijloc cu PTC9               

uint8_t state;

void Switch_Init(void) {
	
	// Activarea semnalului de ceas pentru a putea folosi GPIO cu ajutorul pinului 1 de pe portul C
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	// Utilizarea GPIO impune selectarea variantei de multiplexare cu valorea 1
	PORTA->PCR[SWITCH_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[SWITCH_PIN] |= PORT_PCR_MUX(1);
	
	// Activare întreruperi pe rising edge
	PORTA->PCR[SWITCH_PIN] |= PORT_PCR_IRQC(0x09) | PORT_PCR_PE_MASK;
	
	state = 0;
	
	// Activare întrerupere pentru a folosi switch-u
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	NVIC_SetPriority(PORTA_IRQn, 128);
	NVIC_EnableIRQ(PORTA_IRQn);
}
void PORTA_IRQHandler() {
	
	
	// Prin utilizarea variabilei state, putem realiza un FSM
	// si sa configuram fiecare tranzitie in parte prin 
	// stingerea ledului anterior si aprinderea ledului curent
	
	if(state == 0) {					// aprinde segment-ul de sus de la cifra 0
		LED_turn_off(4);				//stinge led stanga jos de la F
		LED_Init(1);						//aprinde led sus de la 0
		state = 1;
	} else if (state == 1) {	// aprinde segment-ul dreapta sus de la cifra 0
		LED_turn_off(1);
		LED_Init(2);
		state = 2;
	} else if (state == 2) {	// aprinde segment-ul dreapta jos de la cifra 0
		LED_turn_off(2);
		LED_Init(3);
		state = 3;
	} else if (state == 3) {	// aprinde segment-ul de jos de la cifra 0
		LED_turn_off(3);
		LED_Init(4);
		state = 4;
	} else if( state == 4)		// aprinde segment-ul stanga jos de la cifra 0
	{
		LED_turn_off(4);
		LED_Init(5);
		state = 5;
	}else if( state ==5)			// aprinde segment-ul stanga sus de la cifra 0
	{
		LED_turn_off(5);
		LED_Init(6);
		state = 6;
	}else if( state ==6)			// aprinde segment-ul dreapta sus de la cifra 1
	{
		LED_turn_off(6);
		LED_Init(2);
		state = 7;
	}else if( state ==7)			// aprinde segment-ul dreapta jos de la cifra 1
	{
		LED_turn_off(2);
		LED_Init(3);
		state = 8;
	}else if( state ==8)			// aprinde segment-ul de sus de la cifra 2
	{
		LED_turn_off(3);
		LED_Init(1);
		state = 9;
	}else if( state ==9)			// aprinde segment-ul dreapta sus de la cifra 2
	{
		LED_turn_off(1);
		LED_Init(2);
		state = 10;
	}else if( state ==10)			// aprinde segment-ul din centru de la cifra 2 
	{
		LED_turn_off(2);
		LED_Init(7);
		state = 11;
	}else if( state ==11)			// aprinde segment-ul stanga jos de la cifra 2
	{
		LED_turn_off(7);
		LED_Init(5);
		state = 12;
	}else if( state ==12)			// aprinde segment-ul de jos de la cifra 2
	{
		LED_turn_off(5);
		LED_Init(4);
		state = 13;
	}else if( state ==13)			// aprinde segment-ul de sus de la cifra 3
	{
		LED_turn_off(4);
		LED_Init(1);
		state = 14;
	}else if( state ==14)			// aprinde segment-ul dreapta sus de la cifra 3
	{
		LED_turn_off(1);
		LED_Init(2);
		state = 15;
	}else if( state ==15)			// aprinde segment-ul din centru de la cifra 3
	{
		LED_turn_off(2);
		LED_Init(7);
		state = 16;
	}else if( state ==16)			// aprinde segment-ul din dreapta jos de la cifra 3
	{
		LED_turn_off(7);				
		LED_Init(3);
		state = 17;
	}else if( state ==17)			// aprinde segment-ul de jos de la cifra 3
	{
		LED_turn_off(3);
		LED_Init(4);
		state = 18;
	}else if( state ==18)			// aprinde segment-ul din stanga sus de la cifra 4
	{
		LED_turn_off(4);
		LED_Init(6);
		state = 19;
	}else if( state ==19)			// aprinde segment-ul din centru de la cifra 4
	{
		LED_turn_off(6);
		LED_Init(7);
		state = 20;
	}else if( state ==20)			// aprinde segment-ul din dreapta sus de la cifra 4
	{
		LED_turn_off(7);
		LED_Init(2);
		state = 21;
	}else if( state ==21)
	{
		LED_turn_off(2);
		LED_Init(3);
		state = 22;
	}else if( state ==22)
	{
		LED_turn_off(3);
		LED_Init(1);
		state = 23;
	}else if( state ==23)
	{
		LED_turn_off(1);
		LED_Init(6);
		state = 24;
	}else if( state ==24)			// aprinde segment-ul din centru de la cifra 5
	{
		LED_turn_off(6);
		LED_Init(7);
		state = 25;
	}else if( state ==25)			// aprinde segment-ul din dreapta jos de la cifra 5
	{
		LED_turn_off(7);
		LED_Init(3);
		state = 26;
	}else if( state ==26)			// aprinde segment-ul de jos de la cifra 5
	{
		LED_turn_off(3);
		LED_Init(4);
		state = 27;
	}else if( state ==27)			// aprinde segment-ul de sus de la cifra 6
	{
		LED_turn_off(4);
		LED_Init(1);
		state = 28;
	}else if( state ==28)			// aprinde segment-ul din stanga sus de la cifra 6
	{
		LED_turn_off(1);
		LED_Init(6);
		state = 29;
	}
	//biltan
	else if( state ==29)			//  de la cifra 6
	{
		LED_turn_off(6);
		LED_Init(5);
		state = 30;
	}
	else if( state ==30)			//  de la cifra 6
	{
		LED_turn_off(5);
		LED_Init(4);
		state = 31;
	}
	else if( state ==31)			//  de la cifra 6
	{
		LED_turn_off(4);
		LED_Init(3);
		state = 32;
	}
	else if( state ==32)			//  ultimul de la cifra 6
	{
		LED_turn_off(3);
		LED_Init(7);
		state = 33;
	}
	else if( state ==33)			//  primul de la cifra 7
	{
		LED_turn_off(7);
		LED_Init(1);
		state = 34;
	}
		else if( state ==34)			//   de la cifra 7
	{
		LED_turn_off(1);
		LED_Init(2);
		state = 35;
	}
	
	else if( state ==35)			//   de la cifra 7
	{
		LED_turn_off(2);
		LED_Init(3);
		state = 36;
	}
	else if( state ==36)			//   primul de la cifra 8
	{
		LED_turn_off(3);
		LED_Init(1);
		state = 37;
	}
	else if( state ==37)			//   de la cifra 8
	{
		LED_turn_off(1);
		LED_Init(2);
		state = 38;
	}
	else if( state ==38)			//   de la cifra 8
	{
		LED_turn_off(2);
		LED_Init(3);
		state = 39;
	}
	else if( state ==39)			//   de la cifra 8
	{
		LED_turn_off(3);
		LED_Init(4);
		state = 40;
	}
	else if( state ==40)			//   de la cifra 8
	{
		LED_turn_off(4);
		LED_Init(5);
		state = 41;
	}
	else if( state ==41)			//   de la cifra 8
	{
		LED_turn_off(5);
		LED_Init(6);
		state = 42;
	}
	else if( state ==42)			//   de la cifra 8
	{
		LED_turn_off(6);
		LED_Init(7);
		state = 43;
	}
	else if( state ==43)			//  primul de la cifra 9 
	{
		LED_turn_off(7);
		LED_Init(7);        ///aici?
		state = 44;
	}
	else if( state ==44)			//   de la cifra 9
	{
		LED_turn_off(7);
		LED_Init(6);
		state = 45;
	}
	else if( state ==45)			//   de la cifra 9
	{
		LED_turn_off(6);
		LED_Init(1);
		state = 46;
	}
	else if( state ==46)			//   de la cifra 9
	{
		LED_turn_off(1);
		LED_Init(2);
		state = 47;
	}
	else if( state ==47)			//   de la cifra 9
	{
		LED_turn_off(2);
		LED_Init(3);
		state = 48;
	}
	else if( state ==48)			//   de la cifra 9
	{
		LED_turn_off(3);
		LED_Init(4);
		state = 49;
	}
		else if( state ==49)			//   de la A
	{
		LED_turn_off(4);
		LED_Init(5);
		state = 50;
	}
			else if( state ==50)			//   de la A
	{
		LED_turn_off(5);
		LED_Init(6);
		state = 51;
	}
			else if( state ==51)			//   de la A
	{
		LED_turn_off(6);
		LED_Init(1);
		state = 52;
	}
			else if( state ==52)			//   de la A
	{
		LED_turn_off(1);
		LED_Init(2);
		state = 53;
	}
			else if( state ==53)			//   de la A
	{
		LED_turn_off(2);
		LED_Init(7);
		state = 54;
	}
			else if( state ==54)			//   de la A
	{
		LED_turn_off(7);
		LED_Init(3);
		state = 55;
	}
	
			else if( state ==55)			//   de la B
	{
		LED_turn_off(3);
		LED_Init(4);
		state = 56;
	}
				else if( state ==56)			//   de la B
	{
		LED_turn_off(4);
		LED_Init(5);
		state = 57;
	}
				else if( state ==57)			//   de la B
	{
		LED_turn_off(5);
		LED_Init(6);
		state = 58;
	}
				else if( state ==58)			//   de la B
	{
		LED_turn_off(6);
		LED_Init(1);
		state = 59;
	}
				else if( state ==59)			//   de la B
	{
		LED_turn_off(1);
		LED_Init(2);
		state = 60;
	}
				else if( state ==60)			//   de la B
	{
		LED_turn_off(2);
		LED_Init(7);
		state = 61;
	}
					else if( state ==61)			//   de la B
	{
		LED_turn_off(7);
		LED_Init(3);
		state = 62;
	}
	
					else if( state ==62)			//   de la C
	{
		LED_turn_off(3);
		LED_Init(4);
		state = 63;
	}
						else if( state ==63)			//   de la C
	{
		LED_turn_off(4);
		LED_Init(5);
		state = 64;
	}
						else if( state ==64)			//   de la C
	{
		LED_turn_off(5);
		LED_Init(6);
		state = 65;
	}
						else if( state ==65)			//   de la C
	{
		LED_turn_off(6);
		LED_Init(1);
		state = 66;
	}
	
						else if( state ==66)			//   de la D
	{
		LED_turn_off(1);
		LED_Init(2);
		state = 67;
	}
							else if( state ==67)			//   de la D
	{
		LED_turn_off(2);
		LED_Init(3);
		state = 68;
	}
							else if( state ==68)			//   de la D
	{
		LED_turn_off(3);
		LED_Init(4);
		state = 69;
	}
							else if( state ==69)			//   de la D
	{
		LED_turn_off(4);
		LED_Init(5);
		state = 70;
	}
							else if( state ==70)			//   de la D
	{
		LED_turn_off(5);
		LED_Init(6);
		state = 71;
	}
							else if( state ==71)			//   de la D
	{
		LED_turn_off(6);
		LED_Init(1);
		state = 72;
	}
	
							else if( state ==72)			//   de la E
	{
		LED_turn_off(1);
		LED_Init(4);
		state = 73;
	}
								else if( state ==73)			//   de la E
	{
		LED_turn_off(4);
		LED_Init(5);
		state = 74;
	}
								else if( state ==74)			//   de la E
	{
		LED_turn_off(5);
		LED_Init(6);
		state = 75;
	}
								else if( state ==75)			//   de la E
	{
		LED_turn_off(6);
		LED_Init(1);
		state = 76;
	}
	
								else if( state ==76)			//   de la F
	{
		LED_turn_off(1);
		LED_Init(5);
		state = 77;
	}
									else if( state ==77)			//   de la F
	{
		LED_turn_off(5);
		LED_Init(6);
		state = 78;
	}
									else if( state ==78)			//   de la F
	{
		LED_turn_off(6);
		LED_Init(7);
		state = 79;
	}
									else if( state ==79)			//   de la F
	{
		LED_turn_off(7);
		LED_Init(1);
		state = 0;
	}
	
	PORTA_ISFR = (1<<SWITCH_PIN);
}

	
void LED_turn_off(int number) {
	
	// Activarea semnalului de ceas pentru a putea folosi GPIO cu ajutorul pinului 1 de pe portul A
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; //DACA FOLOSESC PORTUL d TREBUIE SA FAC LA FEL SI PENTRU EL
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	//PSOR PENTRU SINGERE
	//PCOR PENTRU APRINDERE
	
	if(number == 1) {
			PORTC->PCR[LED_1] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[LED_1] |= PORT_PCR_MUX(1);
			GPIOC_PDDR |=(1<<LED_1); 
			GPIOC_PSOR |=(1<<LED_1); //APRINDEM
		
		}
		else if(number == 2) {
			PORTC->PCR[LED_2] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[LED_2] |= PORT_PCR_MUX(1);
			GPIOC_PDDR |=(1<<LED_2); 
			GPIOC_PSOR |=(1<<LED_2);
			
		}
		else if(number == 3) {
			PORTD->PCR[LED_3] &= ~PORT_PCR_MUX_MASK;
			PORTD->PCR[LED_3] |= PORT_PCR_MUX(1);
			GPIOD_PDDR |=(1<<LED_3); 
			GPIOD_PSOR |=(1<<LED_3);
		}
		else if(number == 4) {
			PORTA->PCR[LED_4] &= ~PORT_PCR_MUX_MASK;
			PORTA->PCR[LED_4] |= PORT_PCR_MUX(1);
			GPIOA_PDDR |=(1<<LED_4); 
			GPIOA_PSOR |=(1<<LED_4);
		}
		else if(number == 5) {
			PORTA->PCR[LED_5] &= ~PORT_PCR_MUX_MASK;
			PORTA->PCR[LED_5] |= PORT_PCR_MUX(1);
			GPIOA_PDDR |=(1<<LED_5); 
			GPIOA_PSOR |=(1<<LED_5);
			
		}
		else if(number ==6) {
			PORTC->PCR[LED_6] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[LED_6] |= PORT_PCR_MUX(1);
			GPIOC_PDDR |=(1<<LED_6); 
			GPIOC_PSOR |=(1<<LED_6);
			
		}
		else if(number == 7) {
			PORTC->PCR[LED_7] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[LED_7] |= PORT_PCR_MUX(1);
			GPIOC_PDDR |=(1<<LED_7); 
			GPIOC_PSOR |=(1<<LED_7);
		}
}
	


void LED_Init(int number) {
	
	// Activarea semnalului de ceas pentru a putea folosi GPIO cu ajutorul pinului 1 de pe portul A
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; //DACA FOLOSESC PORTUL d TREBUIE SA FAC LA FEL SI PENTRU EL
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	//PSOR PENTRU SINGERE
	//PCOR PENTRU APRINDERE
	
	if(number == 1) {
			PORTC->PCR[LED_1] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[LED_1] |= PORT_PCR_MUX(1);
			GPIOC_PDDR |=(1<<LED_1); 
			GPIOC_PCOR |=(1<<LED_1); //APRINDEM
			UART0_Transmit('1');
		
		}
		else if(number == 2) {
			PORTC->PCR[LED_2] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[LED_2] |= PORT_PCR_MUX(1);
			GPIOC_PDDR |=(1<<LED_2); 
			GPIOC_PCOR |=(1<<LED_2);
			UART0_Transmit('2');
			
		}
		else if(number == 3) {
			PORTD->PCR[LED_3] &= ~PORT_PCR_MUX_MASK;
			PORTD->PCR[LED_3] |= PORT_PCR_MUX(1);
			GPIOD_PDDR |=(1<<LED_3); 
			GPIOD_PCOR |=(1<<LED_3);
			UART0_Transmit('3');
		}
		else if(number == 4) {
			PORTA->PCR[LED_4] &= ~PORT_PCR_MUX_MASK;
			PORTA->PCR[LED_4] |= PORT_PCR_MUX(1);
			GPIOA_PDDR |=(1<<LED_4); 
			GPIOA_PCOR |=(1<<LED_4);
			UART0_Transmit('4');
		}
		else if(number == 5) {
			PORTA->PCR[LED_5] &= ~PORT_PCR_MUX_MASK;
			PORTA->PCR[LED_5] |= PORT_PCR_MUX(1);
			GPIOA_PDDR |=(1<<LED_5); 
			GPIOA_PCOR |=(1<<LED_5);
			UART0_Transmit('5');
			
		}
		else if(number ==6) {
			PORTC->PCR[LED_6] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[LED_6] |= PORT_PCR_MUX(1);
			GPIOC_PDDR |=(1<<LED_6); 
			GPIOC_PCOR |=(1<<LED_6);
			UART0_Transmit('6');
			
		}
		else if(number == 7) {
			PORTC->PCR[LED_7] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[LED_7] |= PORT_PCR_MUX(1);
			GPIOC_PDDR |=(1<<LED_7); 
			GPIOC_PCOR |=(1<<LED_7);
			UART0_Transmit('7');
		}
}

