#include<stdint.h>


#define M68KATY_SERIAL_IN            (*(volatile uint8_t *)  0x078000)
#define M68KATY_SERIAL_OUT           (*(volatile uint8_t *)  0x07A000)
#define M68KATY_SERIAL_STATUS_RDF    (*(volatile uint8_t *)  0x07C000)
#define M68KATY_SERIAL_STATUS_TXE    (*(volatile uint8_t *)  0x07D000)

char putchar(char ch)
{
	while((M68KATY_SERIAL_STATUS_TXE & 1 ) != 0) 
		;
	M68KATY_SERIAL_OUT = ch;
	return ch;
}

void myputs(const char *p)
{
	char c;
	while ((c=*(p++)) != 0) {
		if (c == '\n')
			putchar('\r');
		putchar(c);
	}
}

int main() {

	myputs("hello world");
	
	
	return 0;
}
