
#include <stdlib.h>
#include <msp430.h>


#define SED1335_DIR		P1DIR
#define SED1335_PIN		P1OUT

// control signals
#define SED1335_RD		BIT0 	/* pin 0 -> E */
#define SED1335_WR		BIT1 	/* pin 1 -> RW */
#define SED1335_A0		BIT2 	/* pin 2 -> RS */
#define SED1335_RES  	BIT3 	/* pin 3 -> RST */
#define SED1335_CS1 	BIT4 	/* pin 4  -> CS1B */

// first databus bit
#define SED1335_D0			0	/* first databus bit is pin P2.0 */
#define SED1335_DATA		P2OUT 	/* port databus is pin P2 */
#define SED1335_DATA_DIR	P2DIR 	/* port databus dir */

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_InitializePorts(void)
{
register int i;

SED1335_PIN |= (SED1335_RD | SED1335_WR | SED1335_A0 | SED1335_RES | SED1335_CS1);
SED1335_DIR |= (SED1335_RD | SED1335_WR | SED1335_A0 | SED1335_RES | SED1335_CS1);

SED1335_PIN &= ~SED1335_RES;
for(i = 0 ; i < 1000; i++);
SED1335_PIN |= SED1335_RES;

}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadStatus(void)
{
unsigned char tmp;

SED1335_DATA_DIR &= ~(0xFF << SED1335_D0); //TODO:Verificar

SED1335_PIN |= (SED1335_RD | SED1335_A0 | SED1335_CS1);
asm("nop");
tmp = SED1335_DATA;
SED1335_PIN |= (SED1335_RD | SED1335_A0 | SED1335_CS1);

return tmp;
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadData(void)
{
unsigned char tmp;
SED1335_DATA_DIR &= ~(0xFF << SED1335_D0);//TODO:Verificar

SED1335_PIN &= ~(SED1335_RD | SED1335_CS1);
asm("nop");asm("nop");asm("nop");asm("nop");
tmp = (SED1335_DATA);
SED1335_PIN |= (SED1335_RD | SED1335_CS1);

return tmp;
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteData(unsigned char dataToWrite)
{
SED1335_DATA_DIR |= (0xFF << SED1335_D0);//TODO:Verificar

SED1335_DATA |= (dataToWrite << SED1335_D0);
dataToWrite ^= 0xFF;
SED1335_DATA &= ~(dataToWrite << SED1335_D0);

SED1335_PIN &= ~(SED1335_WR | SED1335_A0 | SED1335_CS1);
asm("nop");
SED1335_PIN |= (SED1335_WR | SED1335_A0 | SED1335_CS1);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteCommand(unsigned char commandToWrite)
{
SED1335_DATA_DIR |= (0xFF << SED1335_D0);

SED1335_DATA = (commandToWrite << SED1335_D0);
commandToWrite ^= 0xFF;
SED1335_DATA &= ~(commandToWrite << SED1335_D0);

SED1335_PIN &= ~(SED1335_WR | SED1335_CS1);
asm("nop");
SED1335_PIN |= (SED1335_WR | SED1335_CS1);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
char GLCD_ReadByteFromROMMemory(char * ptr)
{
return *(ptr);
}
//
