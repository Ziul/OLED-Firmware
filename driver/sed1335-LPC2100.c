#include "build/lpc213x.h"

#define SED1335_SET		IOSET0
#define SED1335_CLR		IOCLR0
#define SED1335_DIR		IODIR0
#define SED1335_PIN		IOPIN0

// control signals
#define SED1335_RD		(1 << 4) 	/* pin PA8 -> E */
#define SED1335_WR		(1 << 5) 	/* pin PA9 -> RW */
#define SED1335_A0		(1 << 6) 	/* pin PA10 -> RS */
#define SED1335_RES  	(1 << 7) 	/* pin PA11 -> RST */
#define SED1335_CS1 	(1 << 8) 	/* pin PA12  -> CS1B */

// first databus bit
#define SED1335_D0      16 /* first databus bit is pin PA0 */

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_InitializePorts(void)
{
volatile int i;

SED1335_SET = (SED1335_RD | SED1335_WR | SED1335_A0 | SED1335_RES | SED1335_CS1);
SED1335_DIR |= (SED1335_RD | SED1335_WR | SED1335_A0 | SED1335_RES | SED1335_CS1);

SED1335_CLR = SED1335_RES;
for(i = 0 ; i < 1000; i++);
SED1335_SET = SED1335_RES;

}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadStatus(void)
{
unsigned char tmp;

SED1335_DIR &= ~(0xFF << SED1335_D0);

SED1335_CLR = (SED1335_RD | SED1335_A0 | SED1335_CS1);
asm("nop");
tmp = (SED1335_PIN >> SED1335_D0);
SED1335_SET = (SED1335_RD | SED1335_A0 | SED1335_CS1);

return tmp;
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadData(void)
{
unsigned char tmp;
SED1335_DIR &= ~(0xFF << SED1335_D0);

//SED1335_CLR = (SED1335_RD | SED1335_CS1);
//asm("nop");
//SED1335_SET = (SED1335_RD | SED1335_CS1);
SED1335_CLR = (SED1335_RD | SED1335_CS1);
asm("nop");asm("nop");asm("nop");asm("nop");
tmp = (SED1335_PIN >> SED1335_D0);
SED1335_SET = (SED1335_RD | SED1335_CS1);

return tmp;
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteData(unsigned char dataToWrite)
{
SED1335_DIR |= (0xFF << SED1335_D0);

SED1335_SET = (dataToWrite << SED1335_D0);
dataToWrite ^= 0xFF;
SED1335_CLR = (dataToWrite << SED1335_D0);

SED1335_CLR = (SED1335_WR | SED1335_A0 | SED1335_CS1);
asm("nop");
SED1335_SET = (SED1335_WR | SED1335_A0 | SED1335_CS1);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteCommand(unsigned char commandToWrite)
{
SED1335_DIR |= (0xFF << SED1335_D0);

SED1335_SET = (commandToWrite << SED1335_D0);
commandToWrite ^= 0xFF;
SED1335_CLR = (commandToWrite << SED1335_D0);

SED1335_CLR = (SED1335_WR | SED1335_CS1);
asm("nop");
SED1335_SET = (SED1335_WR | SED1335_CS1);

}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
char GLCD_ReadByteFromROMMemory(char * ptr)
{
return *(ptr);
}
//
