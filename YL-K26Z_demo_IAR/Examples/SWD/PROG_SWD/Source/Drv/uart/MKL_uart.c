/****************************************Copyright (c)****************************************************
**               Copyright � 2003~2009 Shenzhen uCdragon Technology Co.,Ltd. All Rights Reserved 
**
**                                 http://www.ucdragon.com
**
**      �����������Ƽ����޹�˾���ṩ�����з�������ּ��Э���ͻ����ٲ�Ʒ���з����ȣ��ڷ�����������ṩ
**  ���κγ����ĵ������Խ����������֧�ֵ����Ϻ���Ϣ���������ο����ͻ���Ȩ��ʹ�û����вο��޸ģ�����˾��
**  �ṩ�κε������ԡ��ɿ��Եȱ�֤�����ڿͻ�ʹ�ù��������κ�ԭ����ɵ��ر�ġ�żȻ�Ļ��ӵ���ʧ������˾��
**  �е��κ����Ρ�
**                                                                        �������������Ƽ����޹�˾
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               MKL_uart.c
** Last modified date:      
** Last version:            V1.0
** Descriptions:            uart��������
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
** Descriptions:            UART0�ĳ�ʼ��
** input parameters:        ucBaudRate:�����ʣ�ucParityEnable:У��λѡ��
**                          ucParityType:У�����ͣ�ucDataLength:���ݳ��ȣ�ucStopBit:ֹͣλ��
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
    SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);                                 /* ѡ��PLLʱ��                  */  
    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;                                  /* ��������ʱ��                 */

    uart0TranControl(UART_TX_DISABLE, UART_RX_DISABLE);                 /* ���Ƚ�ֹͨ��                 */

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
    
    UART0_C1_REG(uartPtr) &= ~(UART0_C1_M_MASK |                        /* ���ݳ���                     */
                              UART0_C1_PT_MASK |                        /* У��λ����                   */
                              UART0_C1_PE_MASK);                        /* У��λ                       */
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
    UART0_BDH_REG(uartPtr)  = (usBaudRate & 0x1F00) >> 8;               /* ������                       */
    UART0_BDL_REG(uartPtr)  = (INT8U)(usBaudRate & UART0_BDL_SBR_MASK);
    UART0_BDH_REG(uartPtr) &= ~UART0_BDH_SBNS_MASK;                     /* ֹͣλ                       */
    UART0_BDH_REG(uartPtr) |= (ucStopBit - 1) << UART0_BDH_SBNS_SHIFT;
    UART0_C2_REG(uartPtr)  &= ~(UART0_C2_TIE_MASK | UART0_C2_TCIE_MASK |       
                              UART0_C2_RIE_MASK | UART0_C2_ILIE_MASK);  /* ����ж�����                 */

    while ((UART0_S1_REG(uartPtr) & UART0_S1_RDRF_MASK) &&
           (UART0_D_REG(uartPtr)));                                     /* ����ջ�����                 */
    #if UART0_DEFAULT_OPEN   
    uart0TranControl(UART_TX_ENABLE, UART_RX_ENABLE);                   /* �����������ͨ��             */
    #endif
    
    #if UART0_IRQ_ENABLE    
        #if UART0_SEND_IRQ
        UART0_C2_REG(uartPtr) |= UART0_C2_TCIE_MASK;
        #endif
        #if UART0_RECEIVE_IRQ
        UART0_C2_REG(uartPtr) |= UART0_C2_RIE_MASK;
        #endif                
    NVIC_EnableIRQ(UART0_IRQn);
    NVIC_SetPriority(UART0_IRQn,3);                                     /* �û��Լ�����                 */                    
    #endif            
      
}

/*********************************************************************************************************
** Function name:           uart1Init
** Descriptions:            UART1�ĳ�ʼ��
** input parameters:        ucBaudRate:�����ʣ�ucParityEnable:У��λѡ��
**                          ucParityType:У�����ͣ�ucDataLength:���ݳ��ȣ�ucStopBit:ֹͣλ��
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
    
    SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;                                  /* ��������ʱ��                 */       
    uart1TranControl(UART_TX_DISABLE, UART_RX_DISABLE);                 /* ���Ƚ�ֹͨ��                 */
 
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
     

    UART_C1_REG(uartPtr) &= ~(UART_C1_M_MASK |                           /* ���ݳ���                    */
                              UART_C1_PT_MASK |                          /* У��λ����                  */
                              UART_C1_PE_MASK);                          /* У��λ                      */
    
    UART_C1_REG(uartPtr) |= ((ucDataLength - 8UL) << UART_C1_M_SHIFT)|
                            (ucParityEnable << UART_C1_PE_SHIFT)|
                            (ucParityType << UART_C1_PT_SHIFT);                

    
    usBaudRate = SystemBusClock/(ulBaudRate * 16);    
    UART_BDH_REG(uartPtr) = (usBaudRate & 0x1F00) >> 8;                 /* ������                       */
    UART_BDL_REG(uartPtr) = (INT8U)(usBaudRate & UART_BDL_SBR_MASK);
    UART_BDH_REG(uartPtr) &= ~UART_BDH_SBNS_MASK;                       /* ֹͣλ                       */
    UART_BDH_REG(uartPtr) |= (ucStopBit - 1) << UART_BDH_SBNS_SHIFT;
    UART_C2_REG(uartPtr) &= ~(UART_C2_TIE_MASK | UART_C2_TCIE_MASK|     /* ����ж�����                 */
                              UART_C2_RIE_MASK | UART_C2_ILIE_MASK);  

    while ((UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK) && 
           (UART_D_REG(uartPtr)));                                      /* ����ջ�����                 */
   
    #if UART0_DEFAULT_OPEN   
    uart1TranControl(UART_TX_ENABLE, UART_RX_ENABLE);                   /* �����������ͨ��             */
    #endif

    #if UART1_IRQ_ENABLE        
        #if UART1_SEND_IRQ
        UART_C2_REG(uartPtr) |= UART_C2_TCIE_MASK;
        #endif
        #if UART1_RECEIVE_IRQ
        UART_C2_REG(uartPtr) |= UART_C2_RIE_MASK;
        #endif                   
    NVIC_EnableIRQ(UART1_IRQn);
    NVIC_SetPriority(UART1_IRQn,3);                                     /* �û��Լ�����                 */                 
    #endif            
            
}

/*********************************************************************************************************
** Function name:           uart2Init
** Descriptions:            UART2�ĳ�ʼ��
** input parameters:        ucBaudRate:�����ʣ�ucParityEnable:У��λѡ��
**                          ucParityType:У�����ͣ�ucDataLength:���ݳ��ȣ�ucStopBit:ֹͣλ��
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
    
    SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;                                  /* ��������ʱ��                 */       
    uart2TranControl(UART_TX_DISABLE, UART_RX_DISABLE);                 /* ���Ƚ�ֹͨ��                 */


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
    
     

    UART_C1_REG(uartPtr) &= ~(UART_C1_M_MASK |                          /* ���ݳ���                     */
                              UART_C1_PT_MASK |                         /* У��λ����                   */
                              UART_C1_PE_MASK);                         /* У��λ                       */
    
    UART_C1_REG(uartPtr) |= ((ucDataLength - 8UL) << UART_C1_M_SHIFT)|
                            (ucParityEnable << UART_C1_PE_SHIFT)|
                            (ucParityType << UART_C1_PT_SHIFT);                

    
    usBaudRate = SystemBusClock/(ulBaudRate * 16);    
    UART_BDH_REG(uartPtr) = (usBaudRate & 0x1F00) >> 8;                 /* ������                       */
    UART_BDL_REG(uartPtr) = (INT8U)(usBaudRate & UART_BDL_SBR_MASK);
    UART_BDH_REG(uartPtr) &= ~UART_BDH_SBNS_MASK;                       /* ֹͣλ                       */
    UART_BDH_REG(uartPtr) |= (ucStopBit - 1) << UART_BDH_SBNS_SHIFT;
    UART_C2_REG(uartPtr) &= ~(UART_C2_TIE_MASK | UART_C2_TCIE_MASK|     /* ����ж�����                 */
                              UART_C2_RIE_MASK | UART_C2_ILIE_MASK);  

    while ((UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK) &&
           (UART_D_REG(uartPtr)));                                      /* ����ջ�����                 */
   
                                              
    #if UART2_IRQ_ENABLE       
        #if UART2_SEND_IRQ
        UART_C2_REG(uartPtr) |= UART_C2_TCIE_MASK;
        #endif
        #if UART2_RECEIVE_IRQ
        UART_C2_REG(uartPtr) |= UART_C2_RIE_MASK;
        #endif             
    NVIC_EnableIRQ(UART2_IRQn);
    NVIC_SetPriority(UART2_IRQn,3);                                     /* �û��Լ�����                 */        
    #endif            

}

/*********************************************************************************************************
** Function name:           uart0TranControl
** Descriptions:            UART�Ĵ������
** input parameters:        ucTxEnable:����ʹ�ܿ��ƣ�ucRxEnable:����ʹ�ܿ���
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
** Descriptions:            UART�Ĵ������
** input parameters:        ucTxEnable:����ʹ�ܿ��ƣ�ucRxEnable:����ʹ�ܿ���
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
** Descriptions:            UART�Ĵ������
** input parameters:        ucTxEnable:����ʹ�ܿ��ƣ�ucRxEnable:����ʹ�ܿ���
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
** Descriptions:            UART��ȡһ���ֽ�
** input parameters:        none
** output parameters:       none
** Returned value:          ��ȡ�ֽ�ֵ
** Created by:           
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
INT8U  uart0GetChar (void)
{
    UART0_MemMapPtr uartPtr = UART0_BASE_PTR;

    while (!(UART0_S1_REG(uartPtr) & UART0_S1_RDRF_MASK));              /* �ȴ����ջ���������           */
    return UART0_D_REG(uartPtr);                                        /* ���ؽ����ֽ�                 */
}

/*********************************************************************************************************
** Function name:           uart1GetChar
** Descriptions:            UART��ȡһ���ֽ�
** input parameters:        none
** output parameters:       none
** Returned value:          ��ȡ�ֽ�ֵ
** Created by:             
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
INT8U  uart1GetChar (void)
{
    UART_MemMapPtr uartPtr = UART1_BASE_PTR;

    while (!(UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK));                /* �ȴ����ջ���������           */
    return UART_D_REG(uartPtr);                                         /* ���ؽ����ֽ�                 */
}

/*********************************************************************************************************
** Function name:           uart2GetChar
** Descriptions:            UART��ȡһ���ֽ�
** input parameters:        none
** output parameters:       none
** Returned value:          ��ȡ�ֽ�ֵ
** Created by:             
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
INT8U  uart2GetChar (void)
{
    UART_MemMapPtr uartPtr = UART1_BASE_PTR;

    while (!(UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK));                /* �ȴ����ջ���������           */
    return UART_D_REG(uartPtr);                                         /* ���ؽ����ֽ�                 */
}

/*********************************************************************************************************
** Function name:           uart0SendChar
** Descriptions:            UART����һ���ֽ�
** input parameters:        ucData:�������ֽ�
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

    while (!((UART0_S1_REG(uartPtr) & UART0_S1_TDRE_MASK)));            /* �ȴ�FIFO����                 */
    UART0_D_REG(uartPtr) = ucData;                                      /* ������ݼĴ���               */
}

/*********************************************************************************************************
** Function name:           uart1SendChar
** Descriptions:            UART����һ���ֽ�
** input parameters:        ucData:�������ֽ�
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

    while (!((UART_S1_REG(uartPtr) & UART_S1_TDRE_MASK)));              /* �ȴ�FIFO����                 */
    UART_D_REG(uartPtr) = ucData;                                       /* ������ݼĴ���               */
}

/*********************************************************************************************************
** Function name:           uart2SendChar
** Descriptions:            UART����һ���ֽ�
** input parameters:        ucData:�������ֽ�
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

    while (!((UART_S1_REG(uartPtr) & UART_S1_TDRE_MASK)));              /* �ȴ�FIFO����                 */
    UART_D_REG(uartPtr) = ucData;                                       /* ������ݼĴ���               */
}

/*********************************************************************************************************
** Function name:           uart0SendString
** Descriptions:            UART����һ���ַ���
** input parameters:        pucBuf:�������ַ���ָ��
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
** Descriptions:            UART����һ���ַ���
** input parameters:        pucBuf:�������ַ���ָ��
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
** Descriptions:            UART����һ���ַ���
** input parameters:        pucBuf:�������ַ���ָ��
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
** Descriptions:            UART��ǰ״̬
** input parameters:        none
** output parameters:       none
** Returned value:          ״̬����
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
** Descriptions:            UART0�жϷ�����
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
   UART0_MemMapPtr uartPtr = UART0_BASE_PTR;                            /* �����жϴ������             */
   #if UART0_SEND_IRQ                                                   /* �û�����                     */ 
   #endif
    
   #if UART0_RECEIVE_IRQ
    
   while (UART0_S1_REG(uartPtr) & UART0_S1_RDRF_MASK) {                 /* ����жϱ�־                 */
       uart0SendChar(UART0_D_REG(uartPtr));                             /* ���ؽ�������                 */
//     while(!UART0_D_REG(uartPtr));                                    /* ����ջ�����                 */
   }   
   #endif
}

/*********************************************************************************************************
** Function name:           UART1_IRQHandler
** Descriptions:            UART1�жϷ�����
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
   UART_MemMapPtr uartPtr = UART1_BASE_PTR;                             /* �����жϴ������             */
   #if UART1_SEND_IRQ                                                   /* �û�����                     */ 
   #endif
    
   #if UART1_RECEIVE_IRQ
   while (UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK){                    /* ����жϱ�־                 */
       uart1SendChar(UART_D_REG(uartPtr));                              /* ���ؽ�������                 */       
//       while (!UART0_D_REG(uartPtr));                                 /* ����ջ�����                 */
   }   
   #endif    
}

/*********************************************************************************************************
** Function name:           UART2_IRQHandler
** Descriptions:            UART2�жϷ�����
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
   UART_MemMapPtr uartPtr = UART2_BASE_PTR;                             /* �����жϴ������             */
   #if UART2_SEND_IRQ                                                   /* �û�����                     */ 
   #endif
    
   #if UART2_RECEIVE_IRQ
   while (UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK){                    /* ����жϱ�־                 */
       uart2SendChar(UART_D_REG(uartPtr));                              /* ���ؽ�������                 */              
       while (!UART_D_REG(uartPtr));                                    /* ����ջ�����                 */
   }   
   #endif    
}
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
