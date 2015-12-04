/****************************************Copyright (c)****************************************************
**               Copyright © 2003~2009 Shenzhen uCdragon Technology Co.,Ltd. All Rights Reserved 
**
**                                 http://www.ucdragon.com
**
**      ÉîÛÚÊÐÓÅÁú¿Æ¼¼ÓÐÏÞ¹«Ë¾ËùÌá¹©µÄËùÓÐ·þÎñÄÚÈÝÖ¼ÔÚÐ­Öú¿Í»§¼ÓËÙ²úÆ·µÄÑÐ·¢½ø¶È£¬ÔÚ·þÎñ¹ý³ÌÖÐËùÌá¹©
**  µÄÈÎºÎ³ÌÐò¡¢ÎÄµµ¡¢²âÊÔ½á¹û¡¢·½°¸¡¢Ö§³ÖµÈ×ÊÁÏºÍÐÅÏ¢£¬¶¼½ö¹©²Î¿¼£¬¿Í»§ÓÐÈ¨²»Ê¹ÓÃ»ò×ÔÐÐ²Î¿¼ÐÞ¸Ä£¬±¾¹«Ë¾²»
**  Ìá¹©ÈÎºÎµÄÍêÕûÐÔ¡¢¿É¿¿ÐÔµÈ±£Ö¤£¬ÈôÔÚ¿Í»§Ê¹ÓÃ¹ý³ÌÖÐÒòÈÎºÎÔ­ÒòÔì³ÉµÄÌØ±ðµÄ¡¢Å¼È»µÄ»ò¼ä½ÓµÄËðÊ§£¬±¾¹«Ë¾²»
**  ³Ðµ£ÈÎºÎÔðÈÎ¡£
**                                                                        ¡ªÉîÛÚÊÐÓÅÁú¿Æ¼¼ÓÐÏÞ¹«Ë¾
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               MKL_uart.c
** Last modified date:      
** Last version:            V1.0
** Descriptions:            uartÇý¶¯³ÌÐò
**
-------------------------------------------------------------------------------------------------------
** Modified by:        
** Modified date:      
** Version:            
** Descriptions:       
**
*********************************************************************************************************/
#include "includes.h"

/*********************************************************************************************************
** Function name:           uart0Init
** Descriptions:            UART0µÄ³õÊ¼»¯
** input parameters:        ucBaudRate:²¨ÌØÂÊ£»ucParityEnable:Ð£ÑéÎ»Ñ¡Ôñ£»
**                          ucParityType:Ð£ÑéÀàÐÍ£»ucDataLength:Êý¾Ý³¤¶È£»ucStopBit:Í£Ö¹Î»£»
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:         
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart0Init (INT32U  ulBaudRate, 
                 INT8U   ucParityEnable,
                 INT8U   ucParityType,
                 INT8U   ucDataLength, 
                 INT8U   ucStopBit) 
{
    UART0_MemMapPtr uartPtr     = UART0_BASE_PTR;
    register INT16U usBaudRate  = 0;  
    
#if UART_PARAM_DEBUG
    UART_CHECK_PARAM(UART_PARAM_LENGTH(ucDataLength)); 
    UART_CHECK_PARAM(UART_PARAM_STOP(ucStopBit));
    UART_CHECK_PARAM(UART_PARAM_LOGIC(ucParityEnable));
    UART_CHECK_PARAM(UART_PARAM_PARITY(ucParityType));   
#endif 
    
    SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; 
    SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);                                 /* Ñ¡ÔñPLLÊ±ÖÓ                  */  
    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;                                  /* ÔÊÐíÍâÉèÊ±ÖÓ                 */

    uart0TranControl(UART_TX_DISABLE, UART_RX_DISABLE);                 /* Ê×ÏÈ½ûÖ¹Í¨ÐÅ                 */

    #if 1
    PORTA_PCR1 = PORT_PCR_MUX(0x2);                                     /* UART0_TXD                    */
    PORTA_PCR2 = PORT_PCR_MUX(0x2);                                     /* UART0_RXD                    */
    #endif
    #if 0
    PORTA_PCR14 = PORT_PCR_MUX(0x3);                                    /* UART0_TXD                    */
    PORTA_PCR15 = PORT_PCR_MUX(0x3);                                    /* UART0_RXD                    */
    #endif  
    #if 0
    PORTD_PCR7 = PORT_PCR_MUX(0x3);                                     /* UART0_TXD                    */
    PORTD_PCR6 = PORT_PCR_MUX(0x3);                                     /* UART0_RXD                    */
    #endif              
    #if 0
    PORTE_PCR20 = PORT_PCR_MUX(0x4);                                    /* UART0_TXD                    */
    PORTE_PCR21 = PORT_PCR_MUX(0x4);                                    /* UART0_RXD                    */
    #endif       
    #if 0
    PORTE_PCR17 = PORT_PCR_MUX(0x3);                                    /* UART0_TXD                    */
    PORTE_PCR16 = PORT_PCR_MUX(0x3);                                    /* UART0_RXD                    */
    #endif        
    
    UART0_C1_REG(uartPtr) &= ~(UART0_C1_M_MASK |                        /* Êý¾Ý³¤¶È                     */
                              UART0_C1_PT_MASK |                        /* Ð£ÑéÎ»ÀàÐÍ                   */
                              UART0_C1_PE_MASK);                        /* Ð£ÑéÎ»                       */
    UART0_C4_REG(uartPtr) &= ~UART0_C4_M10_MASK; 

    
    if (ucDataLength == 10) {
        UART0_C1_REG(uartPtr) |= (ucParityEnable << UART0_C1_PE_SHIFT)|
                                 (ucParityType << UART0_C1_PT_SHIFT);   
        UART0_C4_REG(uartPtr) |= UART0_C4_M10_MASK;   
    } else {
        UART0_C1_REG(uartPtr) |= ((ucDataLength - 8UL) << UART0_C1_M_SHIFT)|
                                 (ucParityEnable << UART0_C1_PE_SHIFT)|
                                 (ucParityType << UART0_C1_PT_SHIFT);                
    }
    
    usBaudRate = SystemBusClock/(ulBaudRate * 16);
    UART0_BDH_REG(uartPtr)  = (usBaudRate & 0x1F00) >> 8;               /* ²¨ÌØÂÊ                       */
    UART0_BDL_REG(uartPtr)  = (INT8U)(usBaudRate & UART0_BDL_SBR_MASK);
    UART0_BDH_REG(uartPtr) &= ~UART0_BDH_SBNS_MASK;                     /* Í£Ö¹Î»                       */
    UART0_BDH_REG(uartPtr) |= (ucStopBit - 1) << UART0_BDH_SBNS_SHIFT;
    UART0_C2_REG(uartPtr)  &= ~(UART0_C2_TIE_MASK | UART0_C2_TCIE_MASK |       
                              UART0_C2_RIE_MASK | UART0_C2_ILIE_MASK);  /* Çå³ýÖÐ¶ÏÉèÖÃ                 */

    while ((UART0_S1_REG(uartPtr) & UART0_S1_RDRF_MASK) &&
           (UART0_D_REG(uartPtr)));                                     /* Çå½ÓÊÕ»º³åÇø                 */
    #if UART0_DEFAULT_OPEN   
    uart0TranControl(UART_TX_ENABLE, UART_RX_ENABLE);                   /* ÅäÖÃÍê³ÉÔÊÐíÍ¨ÐÅ             */
    #endif
    
    #if UART0_IRQ_ENABLE    
        #if UART0_SEND_IRQ
        UART0_C2_REG(uartPtr) |= UART0_C2_TCIE_MASK;
        #endif
        #if UART0_RECEIVE_IRQ
        UART0_C2_REG(uartPtr) |= UART0_C2_RIE_MASK;
        #endif                
    NVIC_EnableIRQ(UART0_IRQn);
    NVIC_SetPriority(UART0_IRQn,3);                                     /* ÓÃ»§×Ô¼º¶¨Òå                 */                    
    #endif            
      
}

/*********************************************************************************************************
** Function name:           uart1Init
** Descriptions:            UART1µÄ³õÊ¼»¯
** input parameters:        ucBaudRate:²¨ÌØÂÊ£»ucParityEnable:Ð£ÑéÎ»Ñ¡Ôñ£»
**                          ucParityType:Ð£ÑéÀàÐÍ£»ucDataLength:Êý¾Ý³¤¶È£»ucStopBit:Í£Ö¹Î»£»
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:           
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart1Init (INT32U  ulBaudRate, 
                 INT8U   ucParityEnable,
                 INT8U   ucParityType,
                 INT8U   ucDataLength, 
                 INT8U   ucStopBit) 
{
    UART_MemMapPtr uartPtr     = UART1_BASE_PTR;
    register INT16U usBaudRate  = 0;  

#if UART_PARAM_DEBUG
    UART_CHECK_PARAM(UART_PARAM_LENGTH(ucDataLength)); 
    UART_CHECK_PARAM(UART_PARAM_STOP(ucStopBit));
    UART_CHECK_PARAM(UART_PARAM_LOGIC(ucParityEnable));
    UART_CHECK_PARAM(UART_PARAM_PARITY(ucParityType));   
#endif  
    
    SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;                                  /* ÔÊÐíÍâÉèÊ±ÖÓ                 */       
    uart1TranControl(UART_TX_DISABLE, UART_RX_DISABLE);                 /* Ê×ÏÈ½ûÖ¹Í¨ÐÅ                 */
 
    #if 0
    PORTC_PCR4 = PORT_PCR_MUX(0x3);                                     /* UART1_TXD                    */
    PORTC_PCR3 = PORT_PCR_MUX(0x3);                                     /* UART1_RXD                    */  
    #endif            
    #if 0
    PORTC_PCR4 = PORT_PCR_MUX(0x3);                                     /* UART1_TXD                    */
    PORTC_PCR3 = PORT_PCR_MUX(0x3);                                     /* UART1_RXD                    */  
    #endif
    #if 0
    PORTE_PCR0 = PORT_PCR_MUX(0x3);                                     /* UART1_TXD                    */
    PORTE_PCR1 = PORT_PCR_MUX(0x3);                                     /* UART1_RXD                    */   
    #endif          
     

    UART_C1_REG(uartPtr) &= ~(UART_C1_M_MASK |                           /* Êý¾Ý³¤¶È                    */
                              UART_C1_PT_MASK |                          /* Ð£ÑéÎ»ÀàÐÍ                  */
                              UART_C1_PE_MASK);                          /* Ð£ÑéÎ»                      */
    
    UART_C1_REG(uartPtr) |= ((ucDataLength - 8UL) << UART_C1_M_SHIFT)|
                            (ucParityEnable << UART_C1_PE_SHIFT)|
                            (ucParityType << UART_C1_PT_SHIFT);                

    
    usBaudRate = SystemBusClock/(ulBaudRate * 16);    
    UART_BDH_REG(uartPtr) = (usBaudRate & 0x1F00) >> 8;                 /* ²¨ÌØÂÊ                       */
    UART_BDL_REG(uartPtr) = (INT8U)(usBaudRate & UART_BDL_SBR_MASK);
    UART_BDH_REG(uartPtr) &= ~UART_BDH_SBNS_MASK;                       /* Í£Ö¹Î»                       */
    UART_BDH_REG(uartPtr) |= (ucStopBit - 1) << UART_BDH_SBNS_SHIFT;
    UART_C2_REG(uartPtr) &= ~(UART_C2_TIE_MASK | UART_C2_TCIE_MASK|     /* Çå³ýÖÐ¶ÏÉèÖÃ                 */
                              UART_C2_RIE_MASK | UART_C2_ILIE_MASK);  

    while ((UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK) && 
           (UART_D_REG(uartPtr)));                                      /* Çå½ÓÊÕ»º³åÇø                 */
   
    #if UART0_DEFAULT_OPEN   
    uart1TranControl(UART_TX_ENABLE, UART_RX_ENABLE);                   /* ÅäÖÃÍê³ÉÔÊÐíÍ¨ÐÅ             */
    #endif

    #if UART1_IRQ_ENABLE        
        #if UART1_SEND_IRQ
        UART_C2_REG(uartPtr) |= UART_C2_TCIE_MASK;
        #endif
        #if UART1_RECEIVE_IRQ
        UART_C2_REG(uartPtr) |= UART_C2_RIE_MASK;
        #endif                   
    NVIC_EnableIRQ(UART1_IRQn);
    NVIC_SetPriority(UART1_IRQn,3);                                     /* ÓÃ»§×Ô¼º¶¨Òå                 */                 
    #endif            
            
}

/*********************************************************************************************************
** Function name:           uart2Init
** Descriptions:            UART2µÄ³õÊ¼»¯
** input parameters:        ucBaudRate:²¨ÌØÂÊ£»ucParityEnable:Ð£ÑéÎ»Ñ¡Ôñ£»
**                          ucParityType:Ð£ÑéÀàÐÍ£»ucDataLength:Êý¾Ý³¤¶È£»ucStopBit:Í£Ö¹Î»£»
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart2Init (INT32U  ulBaudRate, 
                 INT8U   ucParityEnable,
                 INT8U   ucParityType,
                 INT8U   ucDataLength, 
                 INT8U   ucStopBit) 
{
    UART_MemMapPtr uartPtr     = UART2_BASE_PTR;
    register INT16U usBaudRate  = 0;  
    
#if UART_PARAM_DEBUG
    UART_CHECK_PARAM(UART_PARAM_LENGTH(ucDataLength)); 
    UART_CHECK_PARAM(UART_PARAM_STOP(ucStopBit));
    UART_CHECK_PARAM(UART_PARAM_LOGIC(ucParityEnable));
    UART_CHECK_PARAM(UART_PARAM_PARITY(ucParityType));   
#endif  
    
    SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;                                  /* ÔÊÐíÍâÉèÊ±ÖÓ                 */       
    uart2TranControl(UART_TX_DISABLE, UART_RX_DISABLE);                 /* Ê×ÏÈ½ûÖ¹Í¨ÐÅ                 */


    #if 0                                                               
    PORTD_PCR3 = PORT_PCR_MUX(0x3);                                     /* UART2_TXD                    */
    PORTD_PCR2 = PORT_PCR_MUX(0x3);                                     /* UART2_RXD                    */
    #endif
    #if 0                                                               
    PORTD_PCR5 = PORT_PCR_MUX(0x3);                                     /* UART2_TXD                    */
    PORTD_PCR4 = PORT_PCR_MUX(0x3);                                     /* UART2_RXD                    */
    #endif
    #if 0                                                               
    PORTE_PCR22 = PORT_PCR_MUX(0x4);                                    /* UART2_TXD                    */
    PORTE_PCR23 = PORT_PCR_MUX(0x4);                                    /* UART2_RXD                    */
    #endif           
    
     

    UART_C1_REG(uartPtr) &= ~(UART_C1_M_MASK |                          /* Êý¾Ý³¤¶È                     */
                              UART_C1_PT_MASK |                         /* Ð£ÑéÎ»ÀàÐÍ                   */
                              UART_C1_PE_MASK);                         /* Ð£ÑéÎ»                       */
    
    UART_C1_REG(uartPtr) |= ((ucDataLength - 8UL) << UART_C1_M_SHIFT)|
                            (ucParityEnable << UART_C1_PE_SHIFT)|
                            (ucParityType << UART_C1_PT_SHIFT);                

    
    usBaudRate = SystemBusClock/(ulBaudRate * 16);    
    UART_BDH_REG(uartPtr) = (usBaudRate & 0x1F00) >> 8;                 /* ²¨ÌØÂÊ                       */
    UART_BDL_REG(uartPtr) = (INT8U)(usBaudRate & UART_BDL_SBR_MASK);
    UART_BDH_REG(uartPtr) &= ~UART_BDH_SBNS_MASK;                       /* Í£Ö¹Î»                       */
    UART_BDH_REG(uartPtr) |= (ucStopBit - 1) << UART_BDH_SBNS_SHIFT;
    UART_C2_REG(uartPtr) &= ~(UART_C2_TIE_MASK | UART_C2_TCIE_MASK|     /* Çå³ýÖÐ¶ÏÉèÖÃ                 */
                              UART_C2_RIE_MASK | UART_C2_ILIE_MASK);  

    while ((UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK) &&
           (UART_D_REG(uartPtr)));                                      /* Çå½ÓÊÕ»º³åÇø                 */
   
                                              
    #if UART2_IRQ_ENABLE       
        #if UART2_SEND_IRQ
        UART_C2_REG(uartPtr) |= UART_C2_TCIE_MASK;
        #endif
        #if UART2_RECEIVE_IRQ
        UART_C2_REG(uartPtr) |= UART_C2_RIE_MASK;
        #endif             
    NVIC_EnableIRQ(UART2_IRQn);
    NVIC_SetPriority(UART2_IRQn,3);                                     /* ÓÃ»§×Ô¼º¶¨Òå                 */        
    #endif            

}

/*********************************************************************************************************
** Function name:           uart0TranControl
** Descriptions:            UARTµÄ´«Êä¿ØÖÆ
** input parameters:        ucTxEnable:·¢ËÍÊ¹ÄÜ¿ØÖÆ£»ucRxEnable:½ÓÊÕÊ¹ÄÜ¿ØÖÆ
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart0TranControl (INT8U  ucTxEnable, 
                        INT8U  ucRxEnable)
{
    UART0_MemMapPtr uartPtr = UART0_BASE_PTR;
    
#if UART_PARAM_DEBUG
    UART_CHECK_PARAM(UART_PARAM_LOGIC(ucTxEnable));
    UART_CHECK_PARAM(UART_PARAM_LOGIC(ucRxEnable));
#endif   

    UART0_C2_REG(uartPtr) &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
    UART0_C2_REG(uartPtr) |= (ucTxEnable << UART0_C2_TE_SHIFT)|
                             (ucRxEnable << UART0_C2_RE_SHIFT);
}  

/*********************************************************************************************************
** Function name:           uart1TranControl
** Descriptions:            UARTµÄ´«Êä¿ØÖÆ
** input parameters:        ucTxEnable:·¢ËÍÊ¹ÄÜ¿ØÖÆ£»ucRxEnable:½ÓÊÕÊ¹ÄÜ¿ØÖÆ
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:           
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart1TranControl (INT8U  ucTxEnable, 
                        INT8U  ucRxEnable)
{
    UART_MemMapPtr uartPtr = UART1_BASE_PTR;
    
#if UART_PARAM_DEBUG
    UART_CHECK_PARAM(UART_PARAM_LOGIC(ucTxEnable));
    UART_CHECK_PARAM(UART_PARAM_LOGIC(ucRxEnable));
#endif   

    UART_C2_REG(uartPtr) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
    UART_C2_REG(uartPtr) |= (ucTxEnable << UART_C2_TE_SHIFT)|
                            (ucRxEnable << UART_C2_RE_SHIFT);
}

/*********************************************************************************************************
** Function name:           uart2TranControl
** Descriptions:            UARTµÄ´«Êä¿ØÖÆ
** input parameters:        ucTxEnable:·¢ËÍÊ¹ÄÜ¿ØÖÆ£»ucRxEnable:½ÓÊÕÊ¹ÄÜ¿ØÖÆ
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart2TranControl (INT8U  ucTxEnable, 
                        INT8U  ucRxEnable)
{
    UART_MemMapPtr uartPtr = UART2_BASE_PTR;
    
#if UART_PARAM_DEBUG
    UART_CHECK_PARAM(UART_PARAM_LOGIC(ucTxEnable));
    UART_CHECK_PARAM(UART_PARAM_LOGIC(ucRxEnable));
#endif   

    UART_C2_REG(uartPtr) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
    UART_C2_REG(uartPtr) |= (ucTxEnable << UART_C2_TE_SHIFT)|
                            (ucRxEnable << UART_C2_RE_SHIFT);
}

/*********************************************************************************************************
** Function name:           uart0GetChar
** Descriptions:            UART»ñÈ¡Ò»¸ö×Ö½Ú
** input parameters:        none
** output parameters:       none
** Returned value:          »ñÈ¡×Ö½ÚÖµ
** Created by:           
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
INT8U  uart0GetChar (void)
{
    UART0_MemMapPtr uartPtr = UART0_BASE_PTR;

    while (!(UART0_S1_REG(uartPtr) & UART0_S1_RDRF_MASK));              /* µÈ´ý½ÓÊÕ»º³åÇø¿ÉÓÃ           */
    return UART0_D_REG(uartPtr);                                        /* ·µ»Ø½ÓÊÕ×Ö½Ú                 */
}

/*********************************************************************************************************
** Function name:           uart1GetChar
** Descriptions:            UART»ñÈ¡Ò»¸ö×Ö½Ú
** input parameters:        none
** output parameters:       none
** Returned value:          »ñÈ¡×Ö½ÚÖµ
** Created by:             
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
INT8U  uart1GetChar (void)
{
    UART_MemMapPtr uartPtr = UART1_BASE_PTR;

    while (!(UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK));                /* µÈ´ý½ÓÊÕ»º³åÇø¿ÉÓÃ           */
    return UART_D_REG(uartPtr);                                         /* ·µ»Ø½ÓÊÕ×Ö½Ú                 */
}

/*********************************************************************************************************
** Function name:           uart2GetChar
** Descriptions:            UART»ñÈ¡Ò»¸ö×Ö½Ú
** input parameters:        none
** output parameters:       none
** Returned value:          »ñÈ¡×Ö½ÚÖµ
** Created by:             
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
INT8U  uart2GetChar (void)
{
    UART_MemMapPtr uartPtr = UART1_BASE_PTR;

    while (!(UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK));                /* µÈ´ý½ÓÊÕ»º³åÇø¿ÉÓÃ           */
    return UART_D_REG(uartPtr);                                         /* ·µ»Ø½ÓÊÕ×Ö½Ú                 */
}

/*********************************************************************************************************
** Function name:           uart0SendChar
** Descriptions:            UART·¢ËÍÒ»¸ö×Ö½Ú
** input parameters:        ucData:´ý·¢ËÍ×Ö½Ú
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart0SendChar (INT8U  ucData)
{
    UART0_MemMapPtr uartPtr = UART0_BASE_PTR;

    while (!((UART0_S1_REG(uartPtr) & UART0_S1_TDRE_MASK)));            /* µÈ´ýFIFO¿ÉÓÃ                 */
    UART0_D_REG(uartPtr) = ucData;                                      /* Ìî³äÊý¾Ý¼Ä´æÆ÷               */
}

/*********************************************************************************************************
** Function name:           uart1SendChar
** Descriptions:            UART·¢ËÍÒ»¸ö×Ö½Ú
** input parameters:        ucData:´ý·¢ËÍ×Ö½Ú
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart1SendChar (INT8U  ucData)
{
    UART_MemMapPtr uartPtr = UART1_BASE_PTR;

    while (!((UART_S1_REG(uartPtr) & UART_S1_TDRE_MASK)));              /* µÈ´ýFIFO¿ÉÓÃ                 */
    UART_D_REG(uartPtr) = ucData;                                       /* Ìî³äÊý¾Ý¼Ä´æÆ÷               */
}

/*********************************************************************************************************
** Function name:           uart2SendChar
** Descriptions:            UART·¢ËÍÒ»¸ö×Ö½Ú
** input parameters:        ucData:´ý·¢ËÍ×Ö½Ú
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart2SendChar (INT8U  ucData)
{
    UART_MemMapPtr uartPtr = UART2_BASE_PTR;

    while (!((UART_S1_REG(uartPtr) & UART_S1_TDRE_MASK)));              /* µÈ´ýFIFO¿ÉÓÃ                 */
    UART_D_REG(uartPtr) = ucData;                                       /* Ìî³äÊý¾Ý¼Ä´æÆ÷               */
}

/*********************************************************************************************************
** Function name:           uart0SendString
** Descriptions:            UART·¢ËÍÒ»¸ö×Ö·û´®
** input parameters:        pucBuf:´ý·¢ËÍ×Ö·û´®Ö¸Õë
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart0SendString (INT8U  *pucBuf)
{
    while (*pucBuf != '\0') { 
        uart0SendChar(*pucBuf++);
    }    
}

/*********************************************************************************************************
** Function name:           uart1SendString
** Descriptions:            UART·¢ËÍÒ»¸ö×Ö·û´®
** input parameters:        pucBuf:´ý·¢ËÍ×Ö·û´®Ö¸Õë
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart1SendString (INT8U  *pucBuf)
{
    while (*pucBuf != '\0') { 
        uart1SendChar(*pucBuf++);
    }    
}

/*********************************************************************************************************
** Function name:           uart2SendString
** Descriptions:            UART·¢ËÍÒ»¸ö×Ö·û´®
** input parameters:        pucBuf:´ý·¢ËÍ×Ö·û´®Ö¸Õë
** output parameters:       none
** Returned value:          none
** Created by:             
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  uart2SendString (INT8U  *pucBuf)
{
    while (*pucBuf != '\0') { 
        uart1SendChar(*pucBuf++);
    }    
}

/*********************************************************************************************************
** Function name:           uartGetStatus
** Descriptions:            UARTµ±Ç°×´Ì¬
** input parameters:        none
** output parameters:       none
** Returned value:          ×´Ì¬²ÎÊý
** Created by:              
** Created date:           
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
//INT32U uartGetStatus(INT8U ucPortNum)
//{
//    return (UART0_S1_REG(uartPtr) & UART0_S1_RDRF_MASK);   
//}  
/*********************************************************************************************************
** Function name:           UART0_IRQHandler
** Descriptions:            UART0ÖÐ¶Ï·þÎñº¯Êý
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:             
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  UART0_IRQHandler (void)
{     
   UART0_MemMapPtr uartPtr = UART0_BASE_PTR;                            /* ·¢ËÍÖÐ¶Ï´¦Àí³ÌÐò             */
   #if UART0_SEND_IRQ                                                   /* ÓÃ»§¶¨Òå                     */ 
   #endif
    
   #if UART0_RECEIVE_IRQ
    
   while (UART0_S1_REG(uartPtr) & UART0_S1_RDRF_MASK) {                 /* Çå³ýÖÐ¶Ï±êÖ¾                 */
       uart0SendChar(UART0_D_REG(uartPtr));                             /* ·µ»Ø½ÓÊÕÊý¾Ý                 */
//     while(!UART0_D_REG(uartPtr));                                    /* Çå½ÓÊÕ»º³åÇø                 */
   }   
   #endif
}

/*********************************************************************************************************
** Function name:           UART1_IRQHandler
** Descriptions:            UART1ÖÐ¶Ï·þÎñº¯Êý
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  UART1_IRQHandler (void)
{
   UART_MemMapPtr uartPtr = UART1_BASE_PTR;                             /* ·¢ËÍÖÐ¶Ï´¦Àí³ÌÐò             */
   #if UART1_SEND_IRQ                                                   /* ÓÃ»§¶¨Òå                     */ 
   #endif
    
   #if UART1_RECEIVE_IRQ
   while (UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK){                    /* Çå³ýÖÐ¶Ï±êÖ¾                 */
       uart1SendChar(UART_D_REG(uartPtr));                              /* ·µ»Ø½ÓÊÕÊý¾Ý                 */       
//       while (!UART0_D_REG(uartPtr));                                 /* Çå½ÓÊÕ»º³åÇø                 */
   }   
   #endif    
}

/*********************************************************************************************************
** Function name:           UART2_IRQHandler
** Descriptions:            UART2ÖÐ¶Ï·þÎñº¯Êý
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:           
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  UART2_IRQHandler (void)
{
   UART_MemMapPtr uartPtr = UART2_BASE_PTR;                             /* ·¢ËÍÖÐ¶Ï´¦Àí³ÌÐò             */
   #if UART2_SEND_IRQ                                                   /* ÓÃ»§¶¨Òå                     */ 
   #endif
    
   #if UART2_RECEIVE_IRQ
   while (UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK){                    /* Çå³ýÖÐ¶Ï±êÖ¾                 */
       uart2SendChar(UART_D_REG(uartPtr));                              /* ·µ»Ø½ÓÊÕÊý¾Ý                 */              
       while (!UART_D_REG(uartPtr));                                    /* Çå½ÓÊÕ»º³åÇø                 */
   }   
   #endif    
}
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
