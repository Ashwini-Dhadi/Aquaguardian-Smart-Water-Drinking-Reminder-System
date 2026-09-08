#include<lpc21xx.h>
#include"types.h"
#define EINT0_VIC_CHN0  14
#define EINT0_STATUS_LED  16
#define EINT0_PIN_FUNC    0x0000000C

extern u8 configurationFlag;

void eint0_isr(void)__irq;

void eint0_Init()
{
     PINSEL0&=~(3<<(1*2));
     PINSEL0|=EINT0_PIN_FUNC;
     VICIntEnable=1<<EINT0_VIC_CHN0;
     VICVectCntl0=(1<<5)|EINT0_VIC_CHN0;
     VICVectAddr0=(u32)eint0_isr;
     EXTMODE=1<<0;
	// EXTPOLAR&=~(1<<0);
	 //EXTINT=1<<0;
}


void eint0_isr(void)__irq
{
    configurationFlag=1;   
    VICVectAddr=0;
    EXTINT=1<<0;
}
