/*--------------------------------------------------------------------------------------
Sequencial De leds em C
Felipe Silva
Março / 2015
Sequencial_C.c
/*------------------------------------------------------------------------------------*/
//Configuração
#include <p18f4520.h>
#include <delays.h>
#pragma config OSC=INTIO67, WDT=OFF, PBADEN=OFF, MCLRE=OFF, PWRT=ON, LVP=OFF
/*------------------------------------------------------------------------------------*/
//Definições de Constantes
#define		led		PORTD
#define		D1		PORTDbits.RD0
/*------------------------------------------------------------------------------------*/
//Protótipo das Funções
void Config_Ports(void);
void Config_Int(void);
void Int_Alta(void);
void Int_Baixa(void);
void Seq4 (void);
void Seq3 (void);
void Seq2 (void);
void Seq1 (void);
/*------------------------------------------------------------------------------------*/
//Declaração das Variáveis Globais
int y;
int x;
int temp;
int k;
/*------------------------------------------------------------------------------------*/
//Interrupção de Alta Prioridade
#pragma code isr_alta=0x0008
void ISR_Alta_Prioridade(void)
{
   _asm
      GOTO Int_Alta
   _endasm
}
#pragma code
/*------------------------------------------------------------------------------------*/
//Interrupção de Baixa Prioridade
#pragma code isr_baixa=0x0018
void ISR_Baixa_Prioridade(void)
{
   _asm
      GOTO Int_Baixa
   _endasm	
}
#pragma code
/*------------------------------------------------------------------------------------*/
#pragma code MAIN
void main(void)
{	
   Config_Ports();
   Config_Int();
   while(1)
   {
      if(PORTB == 0b00010000)
	Seq3();
      if(PORTB == 0b00100000)
	Seq2();
      if(PORTB == 0b00000000)
	Seq4();
      else
	Seq1();
   }	
}
#pragma code
/*------------------------------------------------------------------------------------*/
#pragma interrupt Int_Alta
void Int_Alta(void)
{
   
}
/*------------------------------------------------------------------------------------*/
#pragma interruptlow Int_Baixa
void Int_Baixa(void)
{
   
}
/*------------------------------------------------------------------------------------*/
#pragma code CONFIGURA
void Seq1(void)
{
   led = 0;
}
void Seq2(void)
{
   led = 1;
   Delay10KTCYx(20);
   temp = 0;
   
   while(temp < 8 && PORTB == 0b00100000)
     {
	led = led*2;
	temp ++;
	Delay10KTCYx(20);
     }

}
void Seq3(void)
{
   x = 128;
   y = 128;
   while(PORTB == 0b00010000)
   {
      while((PORTB == 0b00010000)&&(y!=0))
      {
	 led=x;
	 y=y/2;
	 x=x+y;
	 Delay10KTCYx(20);
      }
      x=127;
      y=128;
     
      while(PORTB == 0b00010000 && y!=0)
      {
	 led=x;
	 y=y/2;
	 x=x-y;
	 Delay10KTCYx(20);
      }
      x=128;
      y=128;
   }
}
void Seq4(void)
{
   while(PORTB == 0b00000000)
   {
      PORTD = 0b01010101;
      Delay10KTCYx(20);
      PORTD = 0b10101010;
      Delay10KTCYx(20);
   }
}
void Config_Ports(void)
{
   OSCCONbits.IRCF2=1;		//000-31KHz, 001-125KHz, 010-250KHz, 011-500KHz
   OSCCONbits.IRCF1=1;		//100-1MHz, 101-2MHz, 110-4MHz, 111-8MHz
   OSCCONbits.IRCF0=0;
   INTCON2bits.RBPU=0;		//1-Pull-Up's desligados, 0-Pull-Up's ligados
   ADCON1bits.PCFG3=0;		//0111-AN8 a AN12 Digitais, AN0 a AN7 Analógicos
   ADCON1bits.PCFG2=1;		//com PBADEN=OFF.
   ADCON1bits.PCFG1=1;		//se PBADEN=ON - AN0 a AN12 Analógicos
   ADCON1bits.PCFG0=1;
   LATA=0x00;					//Todas os bits do PORTA em 0
   TRISA=0b00000000;			//Todas os bits do PORTA como saídas
   LATB=0x00;					//Todas os bits do PORTB em 0
   TRISB=0b00110000;			//Todas os bits do PORTB como saídas
   LATC=0x00;					//Todas os bits do PORTC em 0
   TRISC=0b00000000;			//Todas os bits do PORTC como saídas
   LATD=0x00;					//Todas os bits do PORTD em 0
   TRISD=0b00000000;			//Todas os bits do PORTD como saídas
   LATE=0x00;					//Todas os bits do PORTE em 0
   TRISE=0b1000;				//RE0 a RE2 como saídas e RE3 como entrada
}
/*------------------------------------------------------------------------------------*/
void Config_Int(void)
{
   //RCONbits.IPEN=1;				;Habilita modo de Dupla Prioridade de Interrupção				
   //INTCONbits.GIEL=1;				;Habilita Interrupções Globais - GIE/GIEH
   //INTCONbits.GIEH=1;				;Habilita Interrupção dos Periféricas - PEIE/GIEL
//-------------------------------
//Timer 0
	//INTCONbits.TMR0IE=1;			;Habilita Interrupção do Timer 0
	//INTCONbits.TMR0IF=1;			;Liga Flag de estouro de contagem do Timer 0
	//INTCON2bits.TMR0IP=0;			;Habilita Interrupção para Baixa Prioridade
   //T0CONbits.TMR0ON=0;			;Desliga Timer
   //T0CONbits.T08BIT=0;			;Habilita Modo de 16 Bit's
   //T0CONbits.T0CS=0;				;Seleciona Clock Interno (Fosc/4). Está via RA4/T0CKI
   //T0CONbits.T0SE=0;				;Seleciona Borda de Subida para o Clock Externo
   //T0CONbits.PSA=0;				;Habilita prescaler do Timer
   //T0CONbits.T0PS2=x;				;Fator de Divisão do Prescaler:
   //T0CONbits.T0PS1=x;				;111-256, 110-128, 101-64, 100-32
   //T0CONbits.T0PS0=x;				;011-16, 010-8, 001-4, 000-2

//-------------------------------
   INTCONbits.INT0IE=0;
   INTCON2bits.INTEDG0=1;
   INTCONbits.INT0IF=0;
//-------------------------------
   INTCON2bits.RBIP=1;
   INTCONbits.RBIE=0;
   INTCONbits.RBIF=0;
//-------------------------------
   IPR1bits.ADIP=1;
   PIE1bits.ADIE=0;
   PIR1bits.ADIF=0;
   ADCON0bits.ADON=1;
   ADCON0bits.GO=1;
   ADCON0bits.CHS3=0;
   ADCON0bits.CHS2=0;
   ADCON0bits.CHS1=0;
   ADCON0bits.CHS0=1;
   ADCON1bits.VCFG1=0;
   ADCON1bits.VCFG0=0;
   ADCON2bits.ADFM=0;
   ADCON2bits.ACQT2=0;
   ADCON2bits.ACQT1=0;
   ADCON2bits.ACQT0=0;
   ADCON2bits.ADCS2=0;
   ADCON2bits.ADCS1=0;
   ADCON2bits.ADCS0=0;
//-------------------------------
//Serial
   IPR1bits.RCIP=1;
   IPR1bits.TXIP=1;
   PIE1bits.RCIE=1;
   PIE1bits.TXIE=0;
   PIR1bits.RCIF=0;
   PIR1bits.TXIF=0;
   
   TXSTAbits.CSRC=0;
   TXSTAbits.TX9=0;
   TXSTAbits.TXEN=1;
   TXSTAbits.SYNC=0;
   TXSTAbits.SENDB=0;
   TXSTAbits.BRGH=1;
   TXSTAbits.TRMT=1;
   TXSTAbits.TX9D=0;
   
   RCSTAbits.SPEN=1;
   RCSTAbits.RX9=0;
   RCSTAbits.SREN=0;
   RCSTAbits.CREN=1;
   RCSTAbits.ADDEN=0;
   RCSTAbits.FERR=0;
   RCSTAbits.OERR=0;
   
   SPBRGH=0x00;
   SPBRG=0x19;
}
#pragma code
/*------------------------------------------------------------------------------------*/
#pragma code SUBROTINAS

/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/
#pragma code
/*------------------------------------------------------------------------------------*/