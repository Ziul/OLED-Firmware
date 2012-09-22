//******************************************************************************
// Testing code for SED1335 running on ATMEGA128 (AVR) family
//
//	Luiz Oliveira
//	08/17/2012
//
//******************************************************************************

#include <grlib.h>
#include <sed1335.h>


//******************************************************************************
//
// The main routine.
//
//******************************************************************************
int main( void )
{
   tRectangle sRect; 
   int i;
   int x = 0, y = 0;
   unsigned uColor;
   tContext *pContext;
   tDisplay *pDisplay;
   
   // Stop watchdog timer to prevent time out reset
 //  WDTCTL = WDTPW + WDTHOLD;
   
   
   //
   // Initialize the display driver.
   //
   GLCD_Initialize();
   GLCD_ClearGraphic();
   
   //
   // Initialize the graphics context.
   //
   GrContextInit(pContext, pDisplay);
  // GrCircleDraw(pContext, 0, 0,5);
   return 0;
}

