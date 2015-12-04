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
  PORT配置
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
 * 寄存器访问宏定义
 */
#define PCR(PTO,BIT)  PORT##PTO##_PCR##BIT
/*
 * 时钟配置
 */ 
#define V_PORT_ENABLE_CLK(V_PTO)    SIM_SCGC5 |=  SIM_SCGC5_PORT##V_PTO##_MASK  /* 二次连接，防止出错   */
#define V_PORT_DISABLE_CLK(V_PTO)   SIM_SCGC5 &= ~SIM_SCGC5_PORT##V_PTO##_MASK

#define PORT_ENABLE_CLK(PTO)        V_PORT_ENABLE_CLK(PTO)
#define PORT_DISABLE_CLK(PTO)       V_PORT_DISABLE_CLK(PTO)
/*
 * 引脚功能配置 PTO 端口号 BIT 引脚位序 FUN 第几项功能
 */
#define  IO_FUN_SEL(PTO, BIT, FUN)      \
    PCR(PTO,BIT) = (PCR(PTO,BIT) & (~PORT_PCR_MUX_MASK))|PORT_PCR_MUX(FUN)   
        
/*
 * 引脚中断配置 PTO 端口号 BIT 引脚位序 IRQC 中断配置选择
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
  GPIO配置
********************************************************************************************************/
#define PDDR(PTO)     GPIO##PTO##_PDDR
#define PSOR(PORT)    GPIO##PORT##_PSOR
#define PCOR(PORT)    GPIO##PORT##_PCOR
#define PTOR(PORT)    GPIO##PORT##_PTOR
#define PDOR(PORT)    GPIO##PORT##_PDOR
#define PDIR(PORT)    GPIO##PORT##_PDIR
/*
 * GPIO按位输入输出控制
 */
#define GPIO_DDR_OUTPUT(POT,BIT)        PDDR(POT) |= (1 << BIT)
#define GPIO_DDR_INPUT(POT,BIT)         PDDR(POT) &= ~(1 << BIT)
/*
 * GPIO按PORT输入输出控制
 */
#define PORT_DDR_OUTPUT(POT,BITS)       PDDR(POT) |= BITS 
#define PORT_DDR_INPUT(POT,BITS)        PDDR(POT) &= ~BITS
/*
 * GPIO按位置位清零翻转控制
 */
#define GPIO_SET(POT,BIT)               PSOR(POT) = (1 << BIT)     
#define GPIO_CLR(POT,BIT)               PCOR(POT) = (1 << BIT)     
#define GPIO_TOGGLE(POT,BIT)            PTOR(POT) = (1 << BIT)     

/*
 * GPIO按PORT置位清零控制
 */
#define PORT_SET(POT,BITS)              PSOR(POT) = BITS   
#define PORT_CLR(POT,BITS)              PCOR(POT) = BITS   
#define PORT_TOGGLE(POT,BITS)           PTOR(POT) = BITS 
/*
 * GPIO输入值读取
 */
#define GPIO_GET_VALUE(POT,BIT)         ~(~(PDIR(POT) & (1 << BIT)))
#define PORT_GET_VALUE(POT)             PDIR(POT)

#define GPIO_PARAM_DEBUG        0                                               /* 是否进行参数检查     */
  
#define GPIO_PARAM_PORTNUM(x)   ((x >= 'A')&&(x <= 'D')? 1 : 0)                 /* 端口号检查           */
#define GPIO_CHECK_PARAM(x)     (x? (while (1)):)                               /* 错误处理             */

/*********************************************************************************************************
  函数声明 
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



