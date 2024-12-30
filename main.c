#include<lpc21xx.h>
void UART0_CONFIG (void);
void UART0_TX(unsigned char);
void UART0_STR(unsigned char*);
unsigned char UART0_RX(void);
#define LED 1<<17

int main()
{
	//IODIR0=LED;
	unsigned char rxbyte;
	UART0_CONFIG();
	UART0_STR("Hello World");
	//IOSET0=LED;
	while(1)
	{
		rxbyte=UART0_RX();
		UART0_TX(rxbyte);
	}
}
void UART0_STR(unsigned char*S)
{
	while(*S)
		UART0_TX(*S++);
}

void UART0_CONFIG(void)
{
	PINSEL0=0X5;
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}
 void UART0_TX(unsigned char d)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=d;
}
unsigned char UART0_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}
