/*********************************************Copyright (c)***********************************************
**                                Guangzhou ZLG MCU Technology Co., Ltd.
**
**                                        http://www.zlgmcu.com
**
**      ������������Ƭ���Ƽ����޹�˾���ṩ�����з�������ּ��Э���ͻ����ٲ�Ʒ���з����ȣ��ڷ�����������ṩ
**  ���κγ����ĵ������Խ����������֧�ֵ����Ϻ���Ϣ���������ο����ͻ���Ȩ��ʹ�û����вο��޸ģ�����˾��
**  �ṩ�κε������ԡ��ɿ��Եȱ�֤�����ڿͻ�ʹ�ù��������κ�ԭ����ɵ��ر�ġ�żȻ�Ļ��ӵ���ʧ������˾��
**  �е��κ����Ρ�
**                                                                        ����������������Ƭ���Ƽ����޹�˾
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               MKL_gpio.h
** Last modified date:      2012-12-14
** Last version:            V1.0
** Descriptions:            gpio��������
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Li Xiang
** Created date:            2012-12-14
** Version:                 V0.9
** Descriptions:            The original version ��ʼ�汾
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
** Descriptions:            IO����ѡ��
** input parameters:        ucPort��PORT�� ucBit��λ�� ucFun������
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
** Descriptions:            IO�ж�ѡ��
** input parameters:        ucPort��PORT�� ucBit��λ�� ucIrq���ж�����
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
** Descriptions:            IO PE ����
** input parameters:        ucPort��PORT�� ucBit��λ�� ucPe��PE
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
** Descriptions:            IO SRE ����
** input parameters:        ucPort��PORT�� ucBit��λ�� ucSre:SRE
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
** Descriptions:            IO PFE ����
** input parameters:        ucPort��PORT�� ucBit��λ�� ucPfe:PFE
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
** Descriptions:            IO DSE ����
** input parameters:        ucPort��PORT�� ucBit��λ�� ucDse:DSE
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
** Descriptions:            PORTʱ��ʹ��
** input parameters:        PORT��
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
** Descriptions:            PORTʱ�ӽ���
** input parameters:        PORT��
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

