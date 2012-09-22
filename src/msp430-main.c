//******************************************************************************
// Testing code for SED1335 running on MSP430 family
//
//	Luiz Oliveira
//	08/17/2012
//
//******************************************************************************

//#include "io430.h"
#include <iomacros.h>
#include <in430.h>
//#include "intrinsics.h"
#include <msp430.h>
#include <grlib.h>
#include <sed1335.h>
#include <isr_compat.h>



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
   WDTCTL = WDTPW + WDTHOLD;
   
   
   //
   // Initialize the display driver.
   //
   GLCD_Initialize();
   GLCD_ClearGraphic();
   
   //
   // Initialize the graphics context.
   //
   GrContextInit(pContext, pDisplay);
   GrCircleDraw(pContext, 0, 0,5);
   return 0;
}

