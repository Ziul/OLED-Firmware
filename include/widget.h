//*****************************************************************************
//
// widget.h - Prototypes for the widget base "class".
//
// Copyright (c) 2008-2009 Luminary Micro, Inc.  All rights reserved.
// Software License Agreement
// 
// Luminary Micro, Inc. (LMI) is supplying this software for use solely and
// exclusively on LMI's microcontroller products.
// 
// The software is owned by LMI and/or its suppliers, and is protected under
// applicable copyright laws.  All rights are reserved.  You may not combine
// this software with "viral" open-source software in order to form a larger
// program.  Any use in violation of the foregoing restrictions may subject
// the user to criminal sanctions under applicable laws, as well as to civil
// liability for the breach of the terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 5228 of the Stellaris Graphics Library.
//
//*****************************************************************************

#ifndef __WIDGET_H__
#define __WIDGET_H__


//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! The structure that describes a generic widget.  This structure is the base
//! ``class'' for all other widgets.
//
//*****************************************************************************
typedef struct __Widget
{
    //
    //! The size of this structure.  This will be the size of the full
    //! structure, not just the generic widget subset.
    //
    long lSize;

    //
    //! A pointer to this widget's parent widget.
    //
    struct __Widget *pParent;

    //
    //! A pointer to this widget's first sibling widget.
    //
    struct __Widget *pNext;

    //
    //! A pointer to this widget's first child widget.
    //
    struct __Widget *pChild;

    //
    //! A pointer to the display on which this widget resides.
    //
    const tDisplay *pDisplay;

    //
    //! The rectangle that encloses this widget.
    //
    tRectangle sPosition;

    //
    //! The procedure that handles messages sent to this widget.
    //
    int (*pfnMsgProc)(struct __Widget *pWidget, unsigned ulMessage,
                       unsigned ulParam1, unsigned ulParam2);
}
tWidget;

//*****************************************************************************
//
//! The widget at the root of the widget tree.  This can be used when
//! constructing a widget tree at compile time (used as the pParent argument to
//! a widget declaration) or as the pWidget argument to an API (such as
//! WidgetPaint() to paint the entire widget tree).
//
//*****************************************************************************
#define WIDGET_ROOT             &g_sRoot

//*****************************************************************************
//
//! This message is sent to indicate that the widget should draw itself on the
//! display.  Neither \e ulParam1 nor \e ulParam2 are used by this message.
//! This message is delivered in top-down order.
//
//*****************************************************************************
#define WIDGET_MSG_PAINT        0x0001

//*****************************************************************************
//
//! This message is sent to indicate that the pointer is now down.  \e ulParam1
//! is the X coordinate of the location where the pointer down event occurred,
//! and \e ulParam2 is the Y coordinate.  This message is delivered in
//! bottom-up order.
//
//*****************************************************************************
#define WIDGET_MSG_PTR_DOWN     0x0002

//*****************************************************************************
//
//! This message is sent to indicate that the pointer has moved while being
//! down.  \e ulParam1 is the X coordinate of the new pointer location, and
//! \e ulParam2 is the Y coordinate.  This message is delivered in bottom-up
//! order.
//
//*****************************************************************************
#define WIDGET_MSG_PTR_MOVE     0x0003

//*****************************************************************************
//
//! This message is sent to indicate that the pointer is now up.  \e ulParam1
//! is the X coordinate of the location where the pointer up event occurred,
//! and \e ulParam2 is the Y coordinate.  This message is delivered in
//! bottom-up order.
//
//*****************************************************************************
#define WIDGET_MSG_PTR_UP       0x0004

//*****************************************************************************
//
//! Requests a redraw of the widget tree.
//!
//! \param pWidget is a pointer to the widget tree to paint.
//!
//! This function sends a \b #WIDGET_MSG_PAINT message to the given widgets,
//! and all of the widget beneath it, so that they will draw or redraw
//! themselves on the display.  The actual drawing will occur when this message
//! is retrieved from the message queue and processed.
//!
//! \return Returns 1 if the message was added to the message queue and 0 if it
//! cound not be added (due to the queue being full).
//
//*****************************************************************************
#define WidgetPaint(pWidget)                                         \
        WidgetMessageQueueAdd(pWidget, WIDGET_MSG_PAINT, 0, 0, 0, 0)

//*****************************************************************************
//
// Prototypes for the generic widget handling functions.
//
//*****************************************************************************
extern tWidget g_sRoot;
extern int WidgetDefaultMsgProc(tWidget *pWidget, unsigned ulMessage,
                                 unsigned ulParam1,
                                 unsigned ulParam2);
extern void WidgetAdd(tWidget *pParent, tWidget *pWidget);
extern void WidgetRemove(tWidget *pWidget);
extern int WidgetMessageSendPreOrder(tWidget *pWidget,
                                               unsigned ulMessage,
                                               unsigned ulParam1,
                                               unsigned ulParam2,
                                               int bStopOnSuccess);
extern int WidgetMessageSendPostOrder(tWidget *pWidget,
                                                unsigned ulMessage,
                                                unsigned ulParam1,
                                                unsigned ulParam2,
                                                int bStopOnSuccess);
extern int WidgetMessageQueueAdd(tWidget *pWidget, unsigned ulMessage,
                                  unsigned ulParam1,
                                  unsigned ulParam2,
                                  unsigned bPostOrder,
                                  int bStopOnSuccess);
extern void WidgetMessageQueueProcess(void);
extern int WidgetPointerMessage(unsigned ulMessage, unsigned lX, unsigned lY);
extern void WidgetMutexInit(int *pcMutex);
extern int  WidgetMutexGet(int *pcMutex);
extern void WidgetMutexPut(int *pcMutex);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __WIDGET_H__
