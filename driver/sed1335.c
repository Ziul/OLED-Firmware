//*****************************************************************************
//
// sed1335.c - Upper driver for SED1335.
//
//
//*****************************************************************************
#include "sed1335.h"

extern void GLCD_InitializePorts(void);

//*****************************************************************************
//
//! Initialize the GLCD
//!
//! This function initialize the ports and start up the GLCD with the default
//! options.
//!
//! \return None.
//
//*****************************************************************************
void GLCD_Initialize(void)
{
GLCD_InitializePorts();

GLCD_WriteCommand(SED1335_SYSTEM_SET); 
GLCD_WriteData(SED1335_SYS_P1);	
GLCD_WriteData(SED1335_SYS_P2);		
GLCD_WriteData(SED1335_FY);		
GLCD_WriteData(SED1335_CR);		
GLCD_WriteData(SED1335_TCR);	
GLCD_WriteData(SED1335_LF);		
GLCD_WriteData(SED1335_APL);	
GLCD_WriteData(SED1335_APH);	
	
GLCD_WriteCommand(SED1335_SCROLL);   
GLCD_WriteData(SED1335_SAD1L);		
GLCD_WriteData(SED1335_SAD1H);		
GLCD_WriteData(SED1335_SL1);		
GLCD_WriteData(SED1335_SAD2L);		
GLCD_WriteData(SED1335_SAD2H);		
GLCD_WriteData(SED1335_SL2);		
GLCD_WriteData(SED1335_SAD3L);		
GLCD_WriteData(SED1335_SAD3H); 		
GLCD_WriteData(SED1335_SAD4L);		
GLCD_WriteData(SED1335_SAD4H);		
	
GLCD_WriteCommand(SED1335_CSRFORM);
GLCD_WriteData(SED1335_CRX);		
GLCD_WriteData(SED1335_CSRF_P2);		
	
GLCD_WriteCommand(SED1335_CGRAM_ADR);       
GLCD_WriteData(SED1335_SAGL);			
GLCD_WriteData(SED1335_SAGH);				
	
GLCD_WriteCommand(SED1335_CSRDIR_R);      

GLCD_WriteCommand(SED1335_HDOT_SCR);       
GLCD_WriteData(SED1335_SCRD);			
	
GLCD_WriteCommand(SED1335_OVLAY);            
GLCD_WriteData(SED1335_OVLAY_P1);			
			
GLCD_WriteCommand(SED1335_DISP_ON);
GLCD_WriteData(SED1335_FLASH);
}

//*****************************************************************************
//
//! Draws a pixel point
//!
//! \param x is the position where the point will be print in X.
//! \param y is the position where the point will be print in Y.
//! \param color is the color of the pixel  printed in (X,Y).
//!
//! This function draws pixel point in position (X,Y) with the color chosen.
//!
//! \return None.
//
//*****************************************************************************
void GLCD_SetPixel(unsigned int x,unsigned int y, int color)
{
unsigned char tmp = 0;
unsigned int address = SED1335_GRAPHICSTART + (40 * y) + (x/8); 
GLCD_SetCursorAddress(address);

GLCD_WriteCommand(SED1335_MREAD);
tmp = GLCD_ReadData();

if(color)
  tmp |= (1 << (SED1335_FX - (x % 8)));
else
  tmp &= ~(1 << (SED1335_FX - (x % 8)));

GLCD_SetCursorAddress(address);
GLCD_WriteCommand(SED1335_MWRITE);
GLCD_WriteData(tmp);
}

//*****************************************************************************
//
//! Print a message on GLCD
//!
//! \param tekst is a string that will be send to the GLCD.
//!
//! This function prints a message on GLCD.
//!
//! \return None.
//
//*****************************************************************************
void GLCD_WriteText(char * tekst)
{
GLCD_WriteCommand(SED1335_MWRITE);
while(*tekst)
	GLCD_WriteData(*tekst++);
}

//*****************************************************************************
//
//! Print a message on GLCD
//!
//! \param tekst is a pointer that will be used to read a message from 
//! the ROM of the GLCD.
//!
//! This function prints a message on GLCD located on local pointed by *teskt
//!
//! \return None.
//
//*****************************************************************************
void GLCD_WriteTextP(char * tekst)
{
GLCD_WriteCommand(SED1335_MWRITE);
while(GLCD_ReadByteFromROMMemory(tekst))
	GLCD_WriteData(GLCD_ReadByteFromROMMemory(tekst++));
}

//*****************************************************************************
//
//! Set the cursor on a address of the ROM
//!
//! \param address is the local where the cursor will point.
//!
//! This function addresses the GLCD's cursor on a specific address.
//!
//! \return None.
//
//*****************************************************************************
void GLCD_SetCursorAddress(unsigned int address)
{
GLCD_WriteCommand(SED1335_CSRW);
GLCD_WriteData((unsigned char)(address & 0xFF));
GLCD_WriteData((unsigned char)(address >> 8));
}

//*****************************************************************************
//
//! Set the text's cursor on a address
//!
//! \param x is the position where the cursor will be send in X.
//! \param y is the position where the cursor will be send in Y.
//!
//! This function addresses the GLCD's text cursor on a specific address.
//!
//! \return None.
//
//*****************************************************************************
void GLCD_TextGoTo(unsigned char x, unsigned char y)
{
GLCD_SetCursorAddress((y * 40) + x);
}

//*****************************************************************************
//
//! Set the graphic's cursor on a address
//!
//! \param x is the position where the cursor will be send in X.
//! \param y is the position where the cursor will be send in Y.
//!
//! This function addresses the GLCD's graphic cursor on a specific address.
//!
//! \return None.
//
//*****************************************************************************
void GLCD_GraphicGoTo(unsigned int x, unsigned int y)
{
GLCD_SetCursorAddress(SED1335_GRAPHICSTART + (y * 40) + x/8);
}

//*****************************************************************************
//
//! Clean the scren
//!
//! This function clean the screen of the GLCD for texts.
//!
//! \return None.
//
//*****************************************************************************
void GLCD_ClearText(void)
{
int i;
GLCD_TextGoTo(0,0);
GLCD_WriteCommand(SED1335_MWRITE);
for(i = 0; i < 1200; i++)
	GLCD_WriteData(' ');
}

//*****************************************************************************
//
//! Clean the scren
//!
//!
//! This function clean the screen of the GLCD for graphics.
//!
//! \return None.
//
//*****************************************************************************
void GLCD_ClearGraphic(void)
{
unsigned int i;
GLCD_SetCursorAddress(SED1335_GRAPHICSTART);
GLCD_WriteCommand(SED1335_MWRITE);
for(i = 0; i < (40 * 240); i++)
	GLCD_WriteData(0x00);
}

//*****************************************************************************
//
//! Draw a bit
//!
//! \param bmp is the pointer that contains the values of the Bitmap
//! \param x is the position where the bitmap will start in X
//! \param y is the position where the bitmap will start in Y.
//! \param width is the width of the Bitmap
//! \param height is the height of the Bitmap
//!
//! This function draw a Bitmap on GLCD, starting from (X,Y)
//!
//! \return None.
//
//*****************************************************************************
void GLCD_Bitmap(char * bmp, int x, int y, int width, int height)
{
unsigned int i, j;
for(i = 0; i < height ; i++)
	{
	GLCD_GraphicGoTo(x, y+i);
	GLCD_WriteCommand(SED1335_MWRITE);
	for(j = 0; j < width/8; j++)
		GLCD_WriteData(GLCD_ReadByteFromROMMemory(bmp+j+(40*i)));
	}
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

