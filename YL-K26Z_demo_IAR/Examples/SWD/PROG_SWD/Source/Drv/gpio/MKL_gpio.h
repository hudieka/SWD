/*********************************************************************************************************/
#ifndef __ZMD_GPIO_MKL_H
#define __ZMD_GPIO_MKL_H

//
//-------- <<< Use Configuration Wizard in Context Menu >>> ----------------------------------------------
//
#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************
  PORT����
********************************************************************************************************/
#define MKL_PORTA               A
#define MKL_PORTB               B
#define MKL_PORTC               C
#define MKL_PORTD               D
#define MKL_PORTE               E
    
#define IO_DIS_IRQ            0x0
#define IO_DMA_RISE_IRQ       0x1
#define IO_DMA_FALL_IRQ       0x2
#define IO_DMA_EITHER_IRQ     0x3
#define IO_LOW_LEVEL_IRQ      0x8
#define IO_HIGH_LEVEL_IRQ     0xc
#define IO_RISE_EDGE_IRQ      0x9
#define IO_FALL_EDGE_IRQ      0xa
#define IO_EITHER_EDGE_IRQ    0xb   
/*
 * �Ĵ������ʺ궨��
 */
#define PCR(PTO,BIT)  PORT##PTO##_PCR##BIT
/*
 * ʱ������
 */ 
#define V_PORT_ENABLE_CLK(V_PTO)    SIM_SCGC5 |=  SIM_SCGC5_PORT##V_PTO##_MASK  /* �������ӣ���ֹ����   */
#define V_PORT_DISABLE_CLK(V_PTO)   SIM_SCGC5 &= ~SIM_SCGC5_PORT##V_PTO##_MASK

#define PORT_ENABLE_CLK(PTO)        V_PORT_ENABLE_CLK(PTO)
#define PORT_DISABLE_CLK(PTO)       V_PORT_DISABLE_CLK(PTO)
/*
 * ���Ź������� PTO �˿ں� BIT ����λ�� FUN �ڼ����
 */
#define  IO_FUN_SEL(PTO, BIT, FUN)      \
    PCR(PTO,BIT) = (PCR(PTO,BIT) & (~PORT_PCR_MUX_MASK))|PORT_PCR_MUX(FUN)   
        
/*
 * �����ж����� PTO �˿ں� BIT ����λ�� IRQC �ж�����ѡ��
 */    
#define  IO_IRQ_CONFIG(PTO, BIT, IRQ)   \
    PCR(PTO,BIT) = (PCR(PTO,BIT) & (~PORT_PCR_IRQC_MASK))|PORT_PCR_IRQC(IRQ);   

#define  IO_PE_CONFIG(PTO, BIT, PE)    \
    PCR(PTO,BIT)) = (PCR(PTO,BIT) & (~PORT_PCR_PE_MASK))|(PE << PORT_PCR_PE_SHIFT);  
    
#define  IO_SRE_CONFIG(PTO, BIT, SRE)    \
    PCR(PTO,BIT)) = (PCR(PTO,BIT) & (~PORT_PCR_SRE_MASK))|(SRE << PORT_PCR_SRE_SHIFT); 
    
#define  IO_PFE_CONFIG(PTO, BIT, PFE)    \
    PCR(PTO,BIT)) = (PCR(PTO,BIT) & (~PORT_PCR_PFE_MASK))|(PFE << PORT_PCR_PFE_SHIFT);  

#define  IO_DSE_CONFIG(PTO, BIT, PFE)    \
    PCR(PTO,BIT)) = (PCR(PTO,BIT) & (~PORT_PCR_DSE_MASK))|(DSE << PORT_PCR_DSE_SHIFT);  


/********************************************************************************************************
  GPIO����
********************************************************************************************************/
#define PDDR(PTO)     GPIO##PTO##_PDDR
#define PSOR(PORT)    GPIO##PORT##_PSOR
#define PCOR(PORT)    GPIO##PORT##_PCOR
#define PTOR(PORT)    GPIO##PORT##_PTOR
#define PDOR(PORT)    GPIO##PORT##_PDOR
#define PDIR(PORT)    GPIO##PORT##_PDIR
/*
 * GPIO��λ�����������
 */
#define GPIO_DDR_OUTPUT(POT,BIT)        PDDR(POT) |= (1 << BIT)
#define GPIO_DDR_INPUT(POT,BIT)         PDDR(POT) &= ~(1 << BIT)
/*
 * GPIO��PORT�����������
 */
#define PORT_DDR_OUTPUT(POT,BITS)       PDDR(POT) |= BITS 
#define PORT_DDR_INPUT(POT,BITS)        PDDR(POT) &= ~BITS
/*
 * GPIO��λ��λ���㷭ת����
 */
#define GPIO_SET(POT,BIT)               PSOR(POT) = (1 << BIT)     
#define GPIO_CLR(POT,BIT)               PCOR(POT) = (1 << BIT)     
#define GPIO_TOGGLE(POT,BIT)            PTOR(POT) = (1 << BIT)     

/*
 * GPIO��PORT��λ�������
 */
#define PORT_SET(POT,BITS)              PSOR(POT) = BITS   
#define PORT_CLR(POT,BITS)              PCOR(POT) = BITS   
#define PORT_TOGGLE(POT,BITS)           PTOR(POT) = BITS 
/*
 * GPIO����ֵ��ȡ
 */
#define GPIO_GET_VALUE(POT,BIT)         ~(~(PDIR(POT) & (1 << BIT)))
#define PORT_GET_VALUE(POT)             PDIR(POT)

#define GPIO_PARAM_DEBUG        0                                               /* �Ƿ���в������     */
  
#define GPIO_PARAM_PORTNUM(x)   ((x >= 'A')&&(x <= 'D')? 1 : 0)                 /* �˿ںż��           */
#define GPIO_CHECK_PARAM(x)     (x? (while (1)):)                               /* ������             */

/*********************************************************************************************************
  �������� 
*********************************************************************************************************/  
extern void PORTnClkEnable(INT8U ucPort); 
extern void PORTnClkDisable(INT8U ucPort);


#ifdef __cplusplus
}
#endif


#endif


/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/ 



