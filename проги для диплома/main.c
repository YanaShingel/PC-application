//#include <avr/io.h>
//#include <util/setbaud.h>
//#define F_CPU 16000000

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
//#include </home/yana/usr/include/unistd.h>

#define FOSC 16000000
#define BAUD 57600
#define MYUBRR FOSC/16/BAUD-1 //скорость передачи
#define CHECKERBOARD1 0x55555555
#define CHECKERBOARD2 0xaaaaaaaa

static FILE mystdin = FDEV_SETUP_STREAM(NULL, fgetc,
_FDEV_SETUP_READ);
static FILE mystdout = FDEV_SETUP_STREAM(fputc, NULL,
_FDEV_SETUP_WRITE);

//void sleep (unsigned int sec); 
void USART_Init( unsigned int ubrr)
{
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (char)ubrr;
//Enable receiver and transmitter
UCSR0B = (1<<RXEN0)|(1<<TXEN0); //разрешить приём и передачу данных
UCSR0C = (1<<USBS0)|(3<<UCSZ00); //установка формата посылки: 8 бит данных, 2 стоп бита
}

int fputc(int c, FILE *_stream)
{
if (c == '\n')
fputc('\r', _stream);
while (!(UCSR0A & (1<<UDRE0)) );//UDREO - флаг опустошения регистра UDR0 (пока в регистре данных нет значений, записываем в UDR0 бит
UDR0 = c;
return 0;
}

int fgetc(FILE *_stream)
{
while ( !(UCSR0A & (1<<RXC0)) );//ожидание окончания приёма данных, RXC - флаг завершения приёма (пока есть данные в регистре UDR0, принимаем их)
return UDR0;
}

int main( void )
{

USART_Init(MYUBRR);
stdin = &mystdin;
stdout = &mystdout;
long pointCounter = 0;

while(1){
	

	char req;

    	fscanf(stdin, "%c", &req);

	_delay_ms(200);

	if (req =='V')
	printf("Version 0.0.1\n");
	else
	if (req =='A'){
		printf("%lu",pointCounter);
		printf("%c",' ');
      		long val = rand() % 2048;
      		printf("%lu",val);
      		pointCounter += 1;
	}
	else if (req == 'R')
	pointCounter = 0;
	//printf("Patent\n");
}


return 0;
}
