/* Name: oddebug.h
 * Project: AVR library
 * Author: Christian Starkjohann
 * Creation Date: 2005-01-16
 * Tabsize: 4
 * Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

#ifndef __oddebug_h_included__
#define __oddebug_h_included__

/*
General Description:
This module implements a function for debug logs on the serial line of the
AVR microcontroller. Debugging can be configured with the define
'DEBUG_LEVEL'. If this macro is not defined or defined to 0, all debugging
calls are no-ops. If it is 1, DBG1 logs will appear, but not DBG2. If it is
2, DBG1 and DBG2 logs will be printed.

A debug log consists of a label ('prefix') to indicate which debug log created
the output and a memory block to dump in hex ('data' and 'len').
*/


#ifndef uchar
#   define  uchar   unsigned char
#endif

#ifndef DEBUG_LEVEL
#   define  DEBUG_LEVEL 0
#endif

/* ------------------------------------------------------------------------- */

#if DEBUG_LEVEL > 0
#   define  DBG1(prefix, data, len) odDebug(prefix, data, len)
#else
#   define  DBG1(prefix, data, len)
#endif

#if DEBUG_LEVEL > 1
#   define  DBG2(prefix, data, len) odDebug(prefix, data, len)
#else
#   define  DBG2(prefix, data, len)
#endif

/* ------------------------------------------------------------------------- */

#if DEBUG_LEVEL > 0
extern void odDebug(uchar prefix, uchar *data, uchar len);
#endif

/* ------------------------------------------------------------------------- */

// register allocation for debugging

register unsigned char r4 asm ("r4");
register unsigned char r5 asm ("r5");
register unsigned char r6 asm ("r6");
register unsigned char r7 asm ("r7");
register unsigned char r8 asm ("r8");
register unsigned char r9 asm ("r9");
register unsigned char r10 asm ("r10");
register unsigned char r11 asm ("r11");
register unsigned char r12 asm ("r12");
register unsigned char r13 asm ("r13");

#define UDEBUG(s)       uartPuts(s);


#endif /* __oddebug_h_included__ */
