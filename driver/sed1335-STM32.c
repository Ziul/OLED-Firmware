#include "stm32f10x_lib.h"

#define SED1335_PORT GPIOE

#define SED1335_A0	GPIO_Pin_10
#define SED1335_WR	GPIO_Pin_8
#define SED1335_RD	GPIO_Pin_9
#define SED1335_CS	GPIO_Pin_11
#define SED1335_RES	GPIO_Pin_12

#define SED1335_D0   0

GPIO_InitTypeDef GPIO_InitStructure;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void GLCD_InitPorts(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
GPIO_StructInit(&GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_All;
GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;
GPIO_Init(SED1335_PORT, &GPIO_InitStructure);
GPIO_Write(SED1335_PORT, SED1335_A0 | SED1335_WR | SED1335_RD | SED1335_CS);
asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
GPIO_SetBits(SED1335_PORT, SED1335_RES);
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void GLCD_WriteData(unsigned char dataToWrite)
{
GPIO_SetBits(SED1335_PORT, (dataToWrite << SED1335_D0));
dataToWrite ^= 0xFF;
GPIO_ResetBits(SED1335_PORT, (dataToWrite << SED1335_D0));

GPIO_ResetBits(SED1335_PORT, (SED1335_CS | SED1335_A0 | SED1335_WR));
asm("nop");asm("nop");asm("nop");
GPIO_SetBits(SED1335_PORT, (SED1335_CS | SED1335_A0 | SED1335_WR));
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void GLCD_WriteCommand(unsigned char commandToWrite)
{
GPIO_SetBits(SED1335_PORT, (commandToWrite << SED1335_D0));
commandToWrite ^= 0xFF;
GPIO_ResetBits(SED1335_PORT, (commandToWrite << SED1335_D0));

GPIO_ResetBits(SED1335_PORT, (SED1335_CS | SED1335_WR));
asm("nop");asm("nop");asm("nop");
GPIO_SetBits(SED1335_PORT, (SED1335_CS | SED1335_WR));
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadData(void)
{
unsigned char tmp;
GPIO_StructInit(&GPIO_InitStructure);  
GPIO_InitStructure.GPIO_Pin = 0xFF << SED1335_D0;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
GPIO_Init(SED1335_PORT, &GPIO_InitStructure);

GPIO_ResetBits(SED1335_PORT, (SED1335_CS | SED1335_RD));
asm("nop");
tmp = ((GPIO_ReadInputData(SED1335_PORT) >> SED1335_D0) & 0xFF);
GPIO_SetBits(SED1335_PORT, (SED1335_CS | SED1335_RD));

GPIO_StructInit(&GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin = (0xFF << SED1335_D0);
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(SED1335_PORT, &GPIO_InitStructure);

return tmp;
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadByteFromROMMemory(unsigned char * ptr)
{
return *(ptr);
}
//









