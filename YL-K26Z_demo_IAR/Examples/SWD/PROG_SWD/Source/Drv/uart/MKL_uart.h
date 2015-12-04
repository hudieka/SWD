#ifndef __ZMD_UART_MKL_H
#define __ZMD_UART_MKL_H

//
//-------- <<< Use Configuration Wizard in Context Menu >>> ----------------------------------------------
//
#ifdef __cplusplus
extern "C" {
#endif
/*********************************************************************************************************
  宏定义
*********************************************************************************************************/
#define MKL_UART0               0
#define MKL_UART1               1
#define MKL_UART2               2
  
#define UART_PARITY_EN          1
#define UART_PARITY_DIS         0
  
#define UART_PARITY_EVEN        0
#define UART_PARITY_ODD         1

#define UART_10BIT_LENGTH       10
#define UART_9BIT_LENGTH        9
#define UART_8BIT_LENGTH        8

#define UART_1BIT_STOP          1
#define UART_2BIT_STOP          2
  
#define UART_POLLED             0
#define UART_INTERRUPT          1
#define UART_DMA                2

#define UART_TX_ENABLE          1
#define UART_TX_DISABLE         0

#define UART_RX_ENABLE          1
#define UART_RX_DISABLE         0

// UART初始化默认配置
// <h> UART Configuration(config the status after uart inited.)
//   <h> UART0 Default Configuration 
//     <o0>  	Transport Enable:
//                     <0=> Disable
//                     <1=> Enable
//     <e1>  	UART0 IRQ Enable
//         <o6.0>   Send IRQ Enable    
//         <O7.0>   Receive IRQ Enable   
//     </e1>
//   </h>  
//   <h> UART1 Default Configuration 
//     <o2>  	Transport Enable:
//                     <0=> Disable
//                     <1=> Enable
//     <e3>  	UART1_IRQ_ENABLE:
//         <o8.0>   Send IRQ Enable    
//         <O9.0>   Receive IRQ Enable       
//     </e3>
//   </h>  
//   <h> UART2 Default Configuration 
//     <o4>  	Transport Enable:
//                     <0=> Disable
//                     <1=> Enable
//     <e5>  	UART2_IRQ_ENABLE:
//         <o10.0>   Send IRQ Enable    
//         <O11.0>   Receive IRQ Enable           
//     </e5>
//   </h>  
// </h>
#define UART0_DEFAULT_OPEN      1                                               /* 是否允许传输          */                                
#define UART0_IRQ_ENABLE        0                                               /* 串口中断允许          */    

#define UART1_DEFAULT_OPEN      0                                               /* 是否允许传输          */                               
#define UART1_IRQ_ENABLE        1                                               /* 串口中断允许          */

#define UART2_DEFAULT_OPEN      0                                               /* 是否允许传输          */                              
#define UART2_IRQ_ENABLE        1                                               /* 串口中断允许          */

#define UART0_SEND_IRQ          0                                               
#define UART0_RECEIVE_IRQ       1
#define UART1_SEND_IRQ          0
#define UART1_RECEIVE_IRQ       0
#define UART2_SEND_IRQ          0
#define UART2_RECEIVE_IRQ       0    

#define UART_PARAM_DEBUG        0                                               /* 是否进行参数检查     */
  
#define UART_PARAM_PORTNUM(x)   (x > 3? 1 : 0)                                  /* 端口号检查           */
#define UART_PARAM_MODE(x)      (x > 3? 1 : 0)                                  /* 模式检查             */
#define UART_PARAM_LENGTH(x)    ((x == 8)||(x == 9)||(x == 9) ? 1 : 0)          /* 数据长度检查         */
#define UART_PARAM_STOP(x)      ((x == 1)||(x == 2)? 1 : 0)                     /* 停止位检查           */
#define UART_PARAM_PARITY(x)    ((x == 0)||(x == 1)? 1 : 0)                     /* 校验位检查           */
#define UART_PARAM_LOGIC(x)     ((x == 0)||(x == 1)? 1 : 0)                     /* 逻辑位检查           */
#define UART_CHECK_PARAM(x)     (x? (while (1)):)                               /* 错误处理             */
/*********************************************************************************************************
  函数声明 
*********************************************************************************************************/  
extern void uart0Init(INT32U  ulBaudRate, 
                     INT8U   ucParityEnable,
                     INT8U   ucParityType,
                     INT8U   ucDataLength, 
                     INT8U   ucStopBit) ;
extern void uart1Init(INT32U  ulBaudRate, 
                     INT8U   ucParityEnable,
                     INT8U   ucParityType,
                     INT8U   ucDataLength, 
                     INT8U   ucStopBit) ;
extern void uart2Init(INT32U  ulBaudRate, 
                     INT8U   ucParityEnable,
                     INT8U   ucParityType,
                     INT8U   ucDataLength, 
                     INT8U   ucStopBit) ;


extern void uart0TranControl(INT8U ucTxEnable, 
                            INT8U ucRxEnable);
extern void uart1TranControl(INT8U ucTxEnable, 
                            INT8U ucRxEnable);
extern void uart2TranControl(INT8U ucTxEnable, 
                            INT8U ucRxEnable);

extern INT8U uart0GetChar(void);
extern INT8U uart1GetChar(void);
extern INT8U uart2GetChar(void);

extern void uart0SendChar(INT8U ucData);
extern void uart1SendChar(INT8U ucData);
extern void uart2SendChar(INT8U ucData);

extern void uart0SendString(INT8U *pucBuf);
extern void uart1SendString(INT8U *pucBuf);
extern void uart2SendString(INT8U *pucBuf);
//extern INT32U uartGetStatus(INT8U ucPortNum);

//
extern void UART0_IRQHandler(void);
extern void UART1_IRQHandler(void);
extern void UART2_IRQHandler(void);
#ifdef __cplusplus
}
#endif


#endif


/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/  


