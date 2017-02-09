//#include <avr/io.h>
//#include <util/setbaud.h>
//#define F_CPU 16000000

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <light_ws2812.h>
//#include </home/yana/usr/include/unistd.h>
#define CHECKERBOARD1 0x55
#define CHECKERBOARD2 0xaa
#define FOSC 16000000
#define BAUD 57600
#define MYUBRR FOSC/16/BAUD-1 //скорость передачи

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

//testMemory

int compare_regions(char *bufa, char *bufb, size_t count) {
    int r = 0;
    size_t i;
    char *p1 = bufa;
    char *p2 = bufb;

    for (i = 0; i < count; i++, p1++, p2++) {
        if (*p1 != *p2) {
                printf(
                        "FAILURE: 0x%x != 0x%x at offset 0x%x.\n",
                        (char) *p1, (char) *p2, (char) (i * sizeof(char)));
            /* printf("Skipping to next test..."); */
            r = -1;
        }
    }
    return r;
}

int test_checkerboard_comparison(char *bufa, char *bufb, size_t count) {
    char *p1 = bufa;
    char *p2 = bufb;
    unsigned int j;
    char q;
    size_t i;

    
    for (j = 0; j < 64; j++) {
        q = (j % 2) == 0 ? 0x55 : 0xaa;
        p1 = (char *) bufa;
        p2 = (char *) bufb;
        for (i = 0; i < count; i++) {
            *p1++ = *p2++ = (i % 2) == 0 ? q : ~q;
        }
        if (compare_regions(bufa, bufb, count)) {
            return -1;
        }
	if ((j%12)==0)
	printf("Test goes without errors \n");
	
    }
	printf("testing is successful \n");
    return 0;
}

#define BUFSIZE 128
	//struct cRGB led[3];
int main( void )
{

	//led[0].r=255;
	//led[1].g=255;
	//led[2].b=255;
	//ws2812_setleds(led, 1);

	USART_Init(MYUBRR);
	stdin = &mystdin;
	stdout = &mystdout;
	long pointCounter = 0;
	//size_t halflen, count;
	//char aligned[BUFSIZE];
	//char *bufa, *bufb;
	//halflen = BUFSIZE / 2;
	//count = halflen / sizeof(char);
	//bufa = (char *) aligned;
	//bufb = (char *) ((size_t) aligned + halflen);

while(1){
	//req - то, что приходит от джавы
	char req;
	//принимаем req
    	fscanf(stdin, "%c", &req);

	_delay_ms(200);
 	//if (req != '\0')
	//printf("%c",req);

	if (req =='V'){
		printf("%c",req);
		printf("Version 0.0.1\n");
	}
	else

	//график с АЦП линии D1
	if (req =='A'){
		printf("%c",req);
      		//long val = rand() % 2048;


		long val = 1204;
      		printf("%lu \n",val);
		_delay_ms(2000);
		long val_1 = 1220;
		printf("%lu \n",val_1);
      		pointCounter += 1;
	}

	//график с АЦП линии D0
	else if (req =='B'){
		printf("%c",req);
      		//long val = rand() % 2048;
      		long val = 1304;
      		printf("%lu \n",val);
		_delay_ms(2000);
		long val_1 = 1320;
		printf("%lu \n",val_1);
      		pointCounter += 1;
	}
	else if (req == 'R')
	pointCounter = 0;
	//else if (req == 'T')
	//printf("OK\n");
	//else if (req == 'E')
	//printf("Ошибка в ячейке = %d, по адресу = %d \n", 3, 74);
//D1
	else if (req == '0'){
	//посылаем значение при 0мА
		printf("%c",req);
		printf("%d \n", 12);
		
	}
	//посылаем значение при 100мА
	else if (req == '1'){
		printf("%c",req);
		printf("%d \n", 1024);
	}
	//посылаем значение при текущем входном токе
	else if (req == '2')
		{printf("%c",req);
		printf("%d \n", 128);
	}
//D0
	else if (req == '3'){
	//посылаем значение при 0мА
		printf("%c",req);
		printf("%d \n", 6);
	}
	//посылаем значение при 100мА
	else if (req == '4'){printf("%c",req);
		printf("%d \n", 37);
	}
	//посылаем значение при текущем входном токе
	else if (req == '5'){printf("%c",req);
		printf("%d \n", 97);
	}

//testMemory
	else if (req == '6') {
		printf("%c",req);
		//printf("Обнаружено 2 сбоя\n");
		//printf("В ячейке 4 по адресу 0x15 одиночный сбой\n");
		//printf("CCCXCCCC\n");
		//printf("В ячейке 10 по адресу 0x39 залипание бита\n");
		//printf("CCCCCCCX\n");
		//printf("Testing completed");
		//printf("Test goes");
		//printf(" without errors");
		test_checkerboard_comparison(bufa, bufb, count);
	}
}
}


