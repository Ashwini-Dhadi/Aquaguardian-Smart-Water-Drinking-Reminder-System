#include <LPC21xx.H>
#include "lcd.h"
#include "defines.h"
#include "delay.h"
#include "kpm.h"
#include "rtc.h"
#include "aquaguardian.h"
#include"lcd_defines.h"
#include"aqua_defines.h"
 extern u32 hour,min,sec,goal,consumed,remaining,configurationFlag;
int main()
{
  IODIR0&=~(1<<SW_AL);
  IODIR0|=(1<<YELLOW_LED_AL);
  IOSET0=(1<<YELLOW_LED_AL);
  IODIR0|=(1<<GREEN_LED_AL);
  IOSET0=(1<<GREEN_LED_AL);
  IODIR0|=(1<<BUZZER);
  IOCLR0=(1<<BUZZER);
   

		RTC_Init();																					     
		InitLCD();
		Init_kpm();
		eint0_Init();
		

		goal=3;
		consumed=0;
		remaining=goal-consumed;

//		SetRTCTimeInfo(23,58,0);

	//	SetRTCDateInfo(11,4,2026);

//		BuildCGRAM(cgramLUT,8);

		CmdLCD(CLR_LCD);
        
    while (1) 

    {    
	    if(configurationFlag==1)
		{
			configurationFlag=0;
			menu_configuration();
		}
		display_status();
		drink_reminder();
		reminder_screen();
		midnight_reset();
		GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
    }
}