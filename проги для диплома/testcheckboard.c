#include <stdio.h>
#include <stdlib.h>
//#include <util/delay.h>
#define CHECKERBOARD1 0x55
#define CHECKERBOARD2 0xaa


//testMemory

int test_checkerboard_comparison(char *bufa, size_t count) {

    	char *p = bufa;
    	unsigned int j;
    	char q;
    	size_t i;
	size_t k;

    
    for (j = 0; j < 64; j++) {
        //q = (j % 2) == 0 ? CHECKERBOARD1 : CHECKERBOARD2;
        p = (char *) bufa;
        for (i = 0; i < count; i++) {
            *p++ = 0x55;
        }

	if ((j!=0) && (j % 12) == 0) {
		printf("OK.\n");
	}
//проверка
	for (k = 0; k < count; k++, p++) {
        	if (*p != 0x55) {
			if (k==0)
			printf("Yana dura\n");
               		 printf(
                        "Error: value 0x%x != 0x%x at offset 0x%x.\n",
                        (char) *p, (char) 0x55, i );
            		/* printf("Skipping to next test..."); */
            		return -1;
       	 	}
    	}
//проверка, что тест идёт верно
	
    }
    return 0;
}

int main( void )
{

//testMemory

	size_t bufsize, count;
	bufsize = 3000;
	char *aligned = malloc(bufsize);
	char *bufa;
	count = bufsize;
	bufa = (char *) aligned;
	test_checkerboard_comparison(bufa, count);
}


