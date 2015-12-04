/********************************************************************************************************/
#ifndef  __INCLUDES_H
#define  __INCLUDES_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************************************************
  通用数据类型重定义
*********************************************************************************************************/
  
typedef unsigned long           INT32U;                                 /* 无符号32位整型变量           */  
typedef unsigned char           INT8U;                                  /* 无符号8位整型变量            */
typedef unsigned short          INT16U;                                 /* 无符号16位整型变量           */

#if 0
typedef unsigned char           BOOLEAN;                                /* 布尔变量                     */
typedef unsigned char           INT8U;                                  /* 无符号8位整型变量            */
typedef signed   char           INT8S;                                  /* 有符号8位整型变量            */
typedef unsigned short          INT16U;                                 /* 无符号16位整型变量           */
typedef signed   short          INT16S;                                 /* 有符号16位整型变量           */
typedef unsigned long           INT32U;                                 /* 无符号32位整型变量           */
typedef signed   long           INT32S;                                 /* 有符号32位整型变量           */
typedef unsigned long long      INT64U;                                 /* 无符号64位整型变量           */
typedef signed long long        INT64S;                                 /* 有符号64位整型变量           */
typedef float                   FP32;                                   /* 单精度浮点数（32位长度）     */
typedef double                  FP64;                                   /* 双精度浮点数（64位长度）     */

typedef unsigned char		uint8;                                      /* 无符号8位整型变量            */
typedef unsigned short int	uint16;                                     /* 无符号16位整型变量           */
typedef unsigned long int	uint32;                                     /* 无符号32位整型变量           */

typedef char			    int8;                                       /* 有符号8位整型变量            */
typedef short int	        int16;                                      /* 有符号16位整型变量           */
typedef int		            int32;                                      /* 有符号32位整型变量           */

typedef volatile int8		vint8;                                      /*  8 bits */
typedef volatile int16		vint16;                                     /* 16 bits */
typedef volatile int32		vint32;                                     /* 32 bits */

typedef volatile uint8		vuint8;                                     /*  8 bits */
typedef volatile uint16		vuint16;                                    /* 16 bits */
typedef volatile uint32		vuint32;                                    /* 32 bits */
#endif
/*********************************************************************************************************
  Standard header files 标准头文件
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//extern void UART0_IRQHandler(void);
//extern void UART1_IRQHandler(void);
//extern void UART2_IRQHandler(void);

/*********************************************************************************************************
  CMSIS 头文件
*********************************************************************************************************/
/* 
 * Configuration of the Cortex-M0 Processor and Core Peripherals
 */
#define __CM0_REV                 0x0000                                /* Core revision r0p0           */
#define __NVIC_PRIO_BITS          2                                     /* Number of Bits used for      */
                                                                        /* Priority Levels              */
#define __Vendor_SysTickConfig    0                                     /* Set to 1 if different SysTick*/
                                                                        /* Config is used               */

/** Interrupt Number Definitions */
typedef enum IRQn {
  /* Core interrupts */
  NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
  HardFault_IRQn               = -13,              /**< Cortex-M0 SV Hard Fault Interrupt */
  SVCall_IRQn                  = -5,               /**< Cortex-M0 SV Call Interrupt */
  PendSV_IRQn                  = -2,               /**< Cortex-M0 Pend SV Interrupt */
  SysTick_IRQn                 = -1,               /**< Cortex-M0 System Tick Interrupt */

  /* Device specific interrupts */
  DMA0_IRQn                    = 0,                /**< DMA channel 0 transfer complete interrupt */
  DMA1_IRQn                    = 1,                /**< DMA channel 1 transfer complete interrupt */
  DMA2_IRQn                    = 2,                /**< DMA channel 2 transfer complete interrupt */
  DMA3_IRQn                    = 3,                /**< DMA channel 3 transfer complete interrupt */
  Reserved20_IRQn              = 4,                /**< Reserved interrupt 20 */
  FTFA_IRQn                    = 5,                /**< FTFA interrupt */
  LVD_LVW_IRQn                 = 6,                /**< Low Voltage Detect, Low Voltage Warning */
  LLW_IRQn                     = 7,                /**< Low Leakage Wakeup */
  I2C0_IRQn                    = 8,                /**< I2C0 interrupt */
  I2C1_IRQn                    = 9,                /**< I2C0 interrupt 25 */
  SPI0_IRQn                    = 10,               /**< SPI0 interrupt */
  SPI1_IRQn                    = 11,               /**< SPI1 interrupt */
  UART0_IRQn                   = 12,               /**< UART0 status/error interrupt */
  UART1_IRQn                   = 13,               /**< UART1 status/error interrupt */
  UART2_IRQn                   = 14,               /**< UART2 status/error interrupt */
  ADC0_IRQn                    = 15,               /**< ADC0 interrupt */
  CMP0_IRQn                    = 16,               /**< CMP0 interrupt */
  TPM0_IRQn                    = 17,               /**< TPM0 fault, overflow and channels interrupt */
  TPM1_IRQn                    = 18,               /**< TPM1 fault, overflow and channels interrupt */
  TPM2_IRQn                    = 19,               /**< TPM2 fault, overflow and channels interrupt */
  RTC_IRQn                     = 20,               /**< RTC interrupt */
  RTC_Seconds_IRQn             = 21,               /**< RTC seconds interrupt */
  PIT_IRQn                     = 22,               /**< PIT timer interrupt */
  Reserved39_IRQn              = 23,               /**< Reserved interrupt 39 */
  USB0_IRQn                    = 24,               /**< USB0 interrupt */
  DAC0_IRQn                    = 25,               /**< DAC interrupt */
  TSI0_IRQn                    = 26,               /**< TSI0 interrupt */
  MCG_IRQn                     = 27,               /**< MCG interrupt */
  LPTimer_IRQn                 = 28,               /**< LPTimer interrupt */
  Reserved45_IRQn              = 29,               /**< Reserved interrupt 45 */
  PORTA_IRQn                   = 30,               /**< Port A interrupt */
  PORTD_IRQn                   = 31                /**< Port D interrupt */
} IRQn_Type;




/*********************************************************************************************************
  Common's header files  公共头文件 
*********************************************************************************************************/
#include "MKL25Z4.h"
#include "system_MKL25Z4.h"

/* * * * * * * * 暂时使用* * * * * * * * */

#include <core_cm0.h>                                                   /* CMSIS File of Cortex-M0      */

/*********************************************************************************************************
  Driver's header files  驱动头文件 
*********************************************************************************************************/
#include "MKL_uart.h"
#include "MKL_gpio.h"
/*********************************************************************************************************
  User's header files 用户头文件
*********************************************************************************************************/
#include "main.h"




#ifdef __cplusplus
}
#endif

#endif


/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
