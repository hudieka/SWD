/****************************************Copyright (c)****************************************************
**               Copyright © 2003~2009 Shenzhen uCdragon Technology Co.,Ltd. All Rights Reserved 
**
**                                 http://www.ucdragon.com
**
**      ÉîÛÚÊĞÓÅÁú¿Æ¼¼ÓĞÏŞ¹«Ë¾ËùÌá¹©µÄËùÓĞ·şÎñÄÚÈİÖ¼ÔÚĞ­Öú¿Í»§¼ÓËÙ²úÆ·µÄÑĞ·¢½ø¶È£¬ÔÚ·şÎñ¹ı³ÌÖĞËùÌá¹©
**  µÄÈÎºÎ³ÌĞò¡¢ÎÄµµ¡¢²âÊÔ½á¹û¡¢·½°¸¡¢Ö§³ÖµÈ×ÊÁÏºÍĞÅÏ¢£¬¶¼½ö¹©²Î¿¼£¬¿Í»§ÓĞÈ¨²»Ê¹ÓÃ»ò×ÔĞĞ²Î¿¼ĞŞ¸Ä£¬±¾¹«Ë¾²»
**  Ìá¹©ÈÎºÎµÄÍêÕûĞÔ¡¢¿É¿¿ĞÔµÈ±£Ö¤£¬ÈôÔÚ¿Í»§Ê¹ÓÃ¹ı³ÌÖĞÒòÈÎºÎÔ­ÒòÔì³ÉµÄÌØ±ğµÄ¡¢Å¼È»µÄ»ò¼ä½ÓµÄËğÊ§£¬±¾¹«Ë¾²»
**  ³Ğµ£ÈÎºÎÔğÈÎ¡£
**                                                                        ¡ªÉîÛÚÊĞÓÅÁú¿Æ¼¼ÓĞÏŞ¹«Ë¾
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               Main.c
** Last modified date:      2012-11-07
** Last version:            V1.0
** Description:             Ö÷º¯ÊıÎÄ¼ş
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Wu Fan
** Created date:            2012-11-07
** Version:                 V1.0
** Descriptions:            lptmr²Ù×÷ÊµÑé,ÀûÓÃµÍ¹¦ºÄ¶¨Ê±Æ÷£¬Éè¼ÆÑÓÊ±³ÌĞò£¬µÍµçÆ½µãÁÁLED£¬ÁÁ1ÃëÃğ1Ãë
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/
#include "includes.h"
#include "DAP_config.h"
#include "swd_host.h"
#include "debug_cm.h"

extern uint8_t swd_switch(uint16_t val);
extern uint8_t swd_read_idcode(uint32_t *id);
/*********************************************************************************************************
** Function name:           myDelay
** Descriptions:            Çı¶¯GPIO ·­×ªDemo
** input parameters:        ulTime:ÑÓÊ±Ê±¼ä
** output parameters:       none
** Returned value:          none
** Created by:              Li Xiang
** Created Date:            2012-12-14
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
void myDelay (INT32U ulTime)
{
    INT32U i;

    i = 0;
    while (ulTime--) {
        for (i = 0; i < 5000; i++);
    }
}
/*********************************************************************************************************
** Function name:           main
** Descriptions:            Çı¶¯GPIO ·­×ªDemo
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              Li Xiang
** Created Date:            2012-12-14
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
int  main (void)
{
    SystemCoreClockUpdate();
    SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
                  | SIM_SCGC5_PORTB_MASK
                  | SIM_SCGC5_PORTC_MASK
                  | SIM_SCGC5_PORTD_MASK
                  | SIM_SCGC5_PORTE_MASK );    
    
    uart0Init(9600,0,0,8,1);
    swd_init();
    printf("YL-KL25Z128 GPIO_Blinky Test start\r\n");


    
    while(1)
    {                                                          
        //command_exec();
      uint32_t tmp = 0;
		
      if (!swd_reset()) 
      {

      }

      if (!swd_switch(0xE79E)) 
      {

      }
		

      if (!swd_reset()) 
      {

      }

      if (!swd_read_idcode(&tmp)) 
      {

      }
    }    
}


void gpio_set_cdc_led(uint8_t state)
{
    if (state)
    {
        LED_CONNECTED_GPIO->PCOR = 1UL << LED_CONNECTED_BIT; // LED on
    }
    else
    {
        LED_CONNECTED_GPIO->PSOR = 1UL << LED_CONNECTED_BIT; // LED off
    }
}


uint8_t gpio_get_pin_loader_state(void) 
{
    //time_delay_ms(2); //delay 2ms for pull-up enable
    return (PTB->PDIR & (1UL << 1));
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
