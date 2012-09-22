#include "build/AT91SAM7S256.h"

// data bus
#define SED1335_DATA_SET 	(*AT91C_PIOA_SODR)
#define SED1335_DATA_CLR 	(*AT91C_PIOA_CODR)
#define SED1335_DATA_OUT 	(*AT91C_PIOA_OER)
#define SED1335_DATA_INP 	(*AT91C_PIOA_ODR)
#define SED1335_DATA_PIN 	(*AT91C_PIOA_PDSR)
#define SED1335_DATA_IO_EN 	(*AT91C_PIOA_PER)

#define SED1335_D0		16
		
#define SED1335_CTRL_SET 	(*AT91C_PIOA_SODR)
#define SED1335_CTRL_CLR 	(*AT91C_PIOA_CODR)
#define SED1335_CTRL_OUT 	(*AT91C_PIOA_OER)
#define SED1335_CTRL_INP 	(*AT91C_PIOA_ODR)
#define SED1335_CTRL_PIN 	(*AT91C_PIOA_PDSR)
#define SED1335_CTRL_IO_EN 	(*AT91C_PIOA_PER)

#define SED1335_WR			(1 << 8)
#define SED1335_RD			(1 << 9)
#define SED1335_A0			(1 << 10)
#define SED1335_CS			(1 << 11)
#define SED1335_RES			(1 << 12)

extern void Init(void);

void GLCD_InitializePorts(void)
{
volatile unsigned int i;
Init();
*AT91C_PMC_PCER = (1 << AT91C_ID_PIOA);

SED1335_CTRL_OUT |= (SED1335_WR | SED1335_RD | SED1335_A0 | SED1335_CS | SED1335_RES);
SED1335_CTRL_SET = (SED1335_WR | SED1335_RD | SED1335_A0 | SED1335_CS | SED1335_RES);

SED1335_CTRL_CLR = SED1335_RES;
for(i = 0 ; i < 1000; i++);
SED1335_CTRL_SET = SED1335_RES;
}
//
void GLCD_WriteCommand(unsigned char commandToWrite)
{
SED1335_DATA_OUT |= (0xFF << SED1335_D0);

SED1335_DATA_SET = (commandToWrite << SED1335_D0);
commandToWrite ^= 0xFF;
SED1335_DATA_CLR = (commandToWrite << SED1335_D0);

SED1335_CTRL_CLR = (SED1335_WR | SED1335_CS);
asm("nop");
SED1335_CTRL_SET = (SED1335_WR | SED1335_CS);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteData(unsigned char dataToWrite)
{
SED1335_DATA_OUT |= (0xFF << SED1335_D0);

SED1335_DATA_SET = (dataToWrite << SED1335_D0);
dataToWrite ^= 0xFF;
SED1335_DATA_CLR = (dataToWrite << SED1335_D0);

SED1335_CTRL_CLR = (SED1335_WR | SED1335_A0 | SED1335_CS);
asm("nop");
SED1335_CTRL_SET = (SED1335_WR | SED1335_A0 | SED1335_CS);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadData(void)
{
unsigned char tmp;
SED1335_DATA_INP |= (0xFF << SED1335_D0);

//SED1335_CLR = (SED1335_RD | SED1335_CS1);
//asm("nop");
//SED1335_SET = (SED1335_RD | SED1335_CS1);
SED1335_CTRL_CLR = (SED1335_RD | SED1335_CS);
asm("nop");asm("nop");asm("nop");asm("nop");
tmp = (SED1335_DATA_PIN >> SED1335_D0);
SED1335_CTRL_SET = (SED1335_RD | SED1335_CS);

return tmp;
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
char GLCD_ReadByteFromROMMemory(char * ptr)
{
return *(ptr);
}
//
