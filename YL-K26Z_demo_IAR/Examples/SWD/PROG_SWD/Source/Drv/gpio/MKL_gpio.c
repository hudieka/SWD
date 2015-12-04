/*********************************************Copyright (c)***********************************************
**                                Guangzhou ZLG MCU Technology Co., Ltd.
**
**                                        http://www.zlgmcu.com
**
**      广州周立功单片机科技有限公司所提供的所有服务内容旨在协助客户加速产品的研发进度，在服务过程中所提供
**  的任何程序、文档、测试结果、方案、支持等资料和信息，都仅供参考，客户有权不使用或自行参考修改，本公司不
**  提供任何的完整性、可靠性等保证，若在客户使用过程中因任何原因造成的特别的、偶然的或间接的损失，本公司不
**  承担任何责任。
**                                                                        ——广州周立功单片机科技有限公司
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               MKL_gpio.h
** Last modified date:      2012-12-14
** Last version:            V1.0
** Descriptions:            gpio驱动程序
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Li Xiang
** Created date:            2012-12-14
** Version:                 V0.9
** Descriptions:            The original version 初始版本
**--------------------------------------------------------------------------------------------------------
** Modified by:        
** Modified date:      
** Version:            
** Descriptions:       
**
*********************************************************************************************************/
#include "includes.h"
/*********************************************************************************************************
** Function name:           IO_FUN_SEL
** Descriptions:            IO功能选择
** input parameters:        ucPort：PORT号 ucBit：位数 ucFun：功能
** output parameters:       none
** Returned value:          none
** Created by:              Li Xiang
** Created date:            2012-05-14
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
// inline void IO_FUN_SEL(INT8U ucPort, INT8U ucBit, INT8U ucFun)
// {
//     PCR(ucPort,ucBit) = (PCR(ucPort,ucBit) & (~PORT_PCR_MUX_MASK))|PORT_PCR_MUX(ucFun) ;   
// }
/*********************************************************************************************************
** Function name:           IO_IRQ_CONFIG
** Descriptions:            IO中断选择
** input parameters:        ucPort：PORT号 ucBit：位数 ucIrq：中断类型
** output parameters:       none
** Returned value:          none
** Created by:              Li Xiang
** Created date:            2012-05-14
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
// inline void IO_IRQ_CONFIG(INT8U ucPort, INT8U ucBit, INT8U ucIrq)
// {
//     PCR(ucPort,ucBit) = (PCR(ucPort,ucBit) & (~PORT_PCR_IRQC_MASK))|PORT_PCR_IRQC(ucIrq);   
// }
/*********************************************************************************************************
** Function name:           IO_PE_CONFIG
** Descriptions:            IO PE 设置
** input parameters:        ucPort：PORT号 ucBit：位数 ucPe：PE
** output parameters:       none
** Returned value:          none
** Created by:              Li Xiang
** Created date:            2012-05-14
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
// inline void IO_PE_CONFIG(INT8U ucPort, INT8U ucBit, INT8U ucPe)
// {
//     PCR(ucPort,ucBit) = (PCR(ucPort,ucBit) & (~PORT_PCR_PE_MASK))|(ucPe << PORT_PCR_PE_SHIFT);    
// }
/*********************************************************************************************************
** Function name:           IO_SRE_CONFIG
** Descriptions:            IO SRE 设置
** input parameters:        ucPort：PORT号 ucBit：位数 ucSre:SRE
** output parameters:       none
** Returned value:          none
** Created by:              Li Xiang
** Created date:            2012-05-14
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
// inline void IO_SRE_CONFIG(INT8U ucPort, INT8U ucBit, INT8U ucSre)
// {
//     PCR(ucPort,ucBit) = (PCR(ucPort,ucBit) & (~PORT_PCR_PE_MASK))|(ucSre << PORT_PCR_SRE_SHIFT);    
// }
/*********************************************************************************************************
** Function name:           IO_PFE_CONFIG
** Descriptions:            IO PFE 设置
** input parameters:        ucPort：PORT号 ucBit：位数 ucPfe:PFE
** output parameters:       none
** Returned value:          none
** Created by:              Li Xiang
** Created date:            2012-05-14
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
// inline void IO_PFE_CONFIG(INT8U ucPort, INT8U ucBit, INT8U ucPfe)
// {
//     PCR(ucPort,ucBit) = (PCR(ucPort,ucBit) & (~PORT_PCR_PE_MASK))|(ucPfe << PORT_PCR_PFE_SHIFT);    
// }
/*********************************************************************************************************
** Function name:           IO_DSE_CONFIG
** Descriptions:            IO DSE 设置
** input parameters:        ucPort：PORT号 ucBit：位数 ucDse:DSE
** output parameters:       none
** Returned value:          none
** Created by:              Li Xiang
** Created date:            2012-05-14
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
// inline void IO_DSE_CONFIG(INT8U ucPort, INT8U ucBit, INT8U ucDse)
// {
//     PCR(ucPort,ucBit) = (PCR(ucPort,ucBit) & (~PORT_PCR_PE_MASK))|(ucDse << PORT_PCR_DSE_SHIFT);    
// }
//  
/*********************************************************************************************************
** Function name:           PORTnClkEnable
** Descriptions:            PORT时钟使能
** input parameters:        PORT号
** output parameters:       none
** Returned value:          none
** Created by:              Li Xiang
** Created date:            2012-05-14
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void PORTnClkEnable(INT8U ucPort)
{
    INT32U ucTemp = 0;
#if GPIO_PARAM_DEBUG
    GPIO_CHECK_PARAM(GPIO_PARAM_PORTNUM(ucPort));  
#endif     
    switch (ucPort) {
        case 'A':
            SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
            break;    
        case 'B':
            SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;            
            break;
        case 'C': 
            SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;            
            break;
        case 'D':
            SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;                  
            break;
        case 'E':
            SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;                    
            break;
        default:
            break;
    }    
}    
/*********************************************************************************************************
** Function name:           PORTnClkDisable
** Descriptions:            PORT时钟禁能
** input parameters:        PORT号
** output parameters:       none
** Returned value:          none
** Created by:              Li Xiang
** Created date:            2012-05-14
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void PORTnClkDisable(INT8U ucPort)
{
    INT32U ucTemp = 0;
#if GPIO_PARAM_DEBUG
    GPIO_CHECK_PARAM(GPIO_PARAM_PORTNUM(ucPort));  
#endif     
    switch (ucPort) {
        case 'A':
            SIM_SCGC5 &= ~SIM_SCGC5_PORTA_MASK;
            break;    
        case 'B':
            SIM_SCGC5 &= ~SIM_SCGC5_PORTB_MASK;            
            break;
        case 'C': 
            SIM_SCGC5 &= ~SIM_SCGC5_PORTC_MASK;            
            break;
        case 'D':
            SIM_SCGC5 &= ~SIM_SCGC5_PORTD_MASK;                  
            break;
        case 'E':
            SIM_SCGC5 &= ~SIM_SCGC5_PORTE_MASK;                    
            break;
        default:
            break;
    }    
}    

/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/  

