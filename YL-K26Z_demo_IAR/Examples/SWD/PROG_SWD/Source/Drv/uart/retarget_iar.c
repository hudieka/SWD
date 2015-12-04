/*******************
 *
 * Copyright 1998-2003 IAR Systems.  All rights reserved.
 *
 * $Revision: 39069 $
 *
 * This is a template implementation of the "__write" function used by
 * the standard library.  Replace it with a system-specific
 * implementation.
 *
 * The "__write" function should output "size" number of bytes from
 * "buffer" in some application-specific way.  It should return the
 * number of characters written, or _LLIO_ERROR on failure.
 *
 * If "buffer" is zero then __write should perform flushing of
 * internal buffers, if any.  In this case "handle" can be -1 to
 * indicate that all handles should be flushed.
 *
 * The template implementation below assumes that the application
 * provides the function "MyLowLevelPutchar".  It should return the
 * character written, or -1 on failure.
 *
 ********************/
/**
 * January 12, 2012 modified by xiongyihui
 */

#include <yfuns.h>
#include "includes.h"

#define TRUE      1
#define FALSE     0
//
//-------- <<< Use Configuration Wizard in Context Menu >>> ----------------------------------------------
//
// <e> Printf Retarget Enable
//     <o1>  	Uart Port Select:
//                     <0=> Uart0
//                     <1=> Uart1
//                     <1=> Uart2
// </e>
#define PRINTF_RE_ENABLE 1
#define UART_TO_PRINTF  0

#if PRINTF_RE_ENABLE
_STD_BEGIN
/*
** __backspace must return the last char read to the stream
** fgetc() needs to keep a record of whether __backspace was
** called directly before it
*/
int last_char_read;
int backspace_called;

//#pragma module_name = "?__write"

int MyLowLevelPutchar(int x);
int MyLowLevelGetchar();

/*
 * If the __write implementation uses internal buffering, uncomment
 * the following line to ensure that we are called with "buffer" as 0
 * (i.e. flush) when the application terminates.
 */

size_t __write(int handle, const unsigned char * buffer, size_t size)
{
  size_t nChars = 0;

  if (buffer == 0)
  {
    /*
     * This means that we should flush internal buffers.  Since we
     * don't we just return.  (Remember, "handle" == -1 means that all
     * handles should be flushed.)
     */
    return 0;
  }

  /* This template only writes to "standard out" and "standard err",
   * for all other file handles it returns failure. */
  if (handle != _LLIO_STDOUT && handle != _LLIO_STDERR)
  {
    return _LLIO_ERROR;
  }

  for (/* Empty */; size != 0; --size)
  {
    if (MyLowLevelPutchar(*buffer++) < 0)
    {
      return _LLIO_ERROR;
    }

    ++nChars;
  }

  return nChars;
}


int MyLowLevelPutchar(int x)
{
    #if (UART_TO_PRINTF == 0)
    uart0SendChar(x);  
    #endif  
    #if (UART_TO_PRINTF == 1)
    uart1SendChar(x);
    #endif
    #if  (UART_TO_PRINTF == 2)
    uart2SendChar(x);  
    #endif  

    return x;
}

//_STD_END

//_STD_BEGIN

//#pragma module_name = "?__read"

int MyLowLevelGetchar();

size_t __read(int handle, unsigned char * buffer, size_t size)
{
  int nChars = 0;

  /* This template only reads from "standard in", for all other file
   * handles it returns failure. */
  if (handle != _LLIO_STDIN)
  {
    return _LLIO_ERROR;
  }

  for (/* Empty */; size > 0; --size)
  {
    int c = MyLowLevelGetchar();
    if (c < 0)
      break;

    *buffer++ = c;
    ++nChars;
  }

  return nChars;
}

int MyLowLevelGetchar()
{
    unsigned char tempch;

    /* if we just backspaced, then return the backspaced character */
    /* otherwise output the next character in the stream */
    if (backspace_called == TRUE)
    {
      backspace_called = FALSE;
      return last_char_read;
    }
    #if (UART_TO_PRINTF == 0)
    tempch = (uart0GetChar());
    #endif  
    #if  (UART_TO_PRINTF == 1)
    tempch = (uart1GetChar()); 
    #endif
    #if  (UART_TO_PRINTF == 2)
    tempch = (uart2GetChar()); 
    #endif  

    last_char_read = (int)tempch;       /* backspace must return this value */
    return tempch;
  
  
}

/** The effect of __backspace() should be to return the last character
** read from the stream, such that a subsequent fgetc() will
** return the same character again.
*/

int __backspace()
{
    backspace_called = TRUE;
    return 1;
}


_STD_END

#endif