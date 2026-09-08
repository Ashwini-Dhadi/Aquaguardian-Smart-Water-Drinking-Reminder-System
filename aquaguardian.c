#include<lpc21xx.h>
#include"types.h"
#include"lcd_defines.h"
#include"rtc.h"
#include"kpm.h"
#include"lcd.h"
#include"defines.h"	
#include"delay.h"
#include"aqua_defines.h"
u32 goal;
 u32 consumed;
 u32 remaining;
 u32 reminderHour=0;
 u32 reminderMin=1;
 u32 reminderSec=0;
 u8 reminderFlag=0;
 u8 goalFlag=0;
 u8 resetFlag=0;
 u8 configurationFlag=0;
 u8 key;
 u32 duration;
 u32 hour;
 u32 min;
 u32 sec;




void yellow_led_on(void)
{
 IOCLR0=(1<<YELLOW_LED_AL);
}

void yellow_led_off(void)
{
 IOSET0=(1<<YELLOW_LED_AL);
}

void green_led_on(void)
{
 IOCLR0=(1<<GREEN_LED_AL);
}
 
void green_led_off(void)
{
 IOSET0=(1<<GREEN_LED_AL);
}

	
u32 getnumber(u32 pos,u8 *flag)
{
	u8 key;
	u32 num=0;
	*flag=0;
	CmdLCD(DSP_ON_CUR_BLK);
        CmdLCD(pos);
	while(1)
	{
		key =keyscan();
		if((key>='0')&&(key<='9'))
		{
			num=(num*10)+(key-'0');
			*flag=1;
			CmdLCD(pos);
			U32LCD(num);
		}
		else if(key=='*')
		{
			if(*flag==1)
			{
				num=num/10;
				CmdLCD(pos);
				StrLCD("                ");
				CmdLCD(pos);
				if(num!=0)
				{
					U32LCD(num);
				}
				if(num==0)
				{
					*flag=0;
				}
			}
		}
		else if(key=='C')
		{
			num=0;
			*flag=0;
			CmdLCD(pos);
			StrLCD("                ");
			CmdLCD(pos);
		}
		else if(key=='D')
                {
			CmdLCD(DSP_ON_CUR_OFF);
			return num;
		}
	}
}
void set_duration(void)
{ 
	u8 durationFlag;
	u32 duration_entered;
	{
INPUT:		CmdLCD(CLR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("set duration");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("MIN:");
		duration_entered=getnumber(GOTO_LINE2_POS0+4,&durationFlag);
		if(durationFlag==0)
		{
			CmdLCD(CLR_LCD);
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("enter duration");
			delay_ms(1000);
			goto INPUT;
		}
		if((duration_entered>=1)&&(duration_entered<=59))
		{
			  duration=duration_entered;
			  return;
		}
		 CmdLCD(CLR_LCD);
         CmdLCD(GOTO_LINE1_POS0);
         StrLCD("Invalid duration");
		 delay_ms(1000);
		 goto INPUT;
		}
}
u32 goal_setting(void)
{
 	u8 setgoalFlag;
	u32 goal_entered;

goal_INPUT:	CmdLCD(CLR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("set your goal");
		CmdLCD(GOTO_LINE2_POS0);
		goal_entered=getnumber(GOTO_LINE2_POS0,&setgoalFlag);
		if(setgoalFlag==0)
		{
			CmdLCD(CLR_LCD);
                	CmdLCD(GOTO_LINE1_POS0);
                	StrLCD("Plz Enter Goal");
			delay_ms(2000);
			goto goal_INPUT;
		}
		if(goal_entered==0)
		{
			CmdLCD(CLR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Goal is too Low!");
			delay_ms(1000);
			goto goal_INPUT;
		}
		return goal_entered;
}

void change_goal(void)
		 {
		 	CmdLCD(CLR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Change Your Goal");
			delay_ms(2000);
			goal=goal_setting();
			remaining=goal-consumed;
			goalFlag=0;
		 }

void change_remindertime(void)
{
	u32 hour_entered;
	u32 min_entered;
	u8 hourFlag;
	u8 minFlag;

hour_INPUT:	CmdLCD(CLR_LCD);
	        CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Set Reminder");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("HOUR:");
		hour_entered=getnumber(GOTO_LINE2_POS0+5,&hourFlag);
                if(hourFlag==0)
		{
			CmdLCD(CLR_LCD);
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("Plz enter Hour");
			delay_ms(1000);
			goto hour_INPUT;
		}
		if(hour_entered>23)
		{
                  	CmdLCD(CLR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD("Invalid Hour");
			delay_ms(1000);
			goto hour_INPUT;
		}

		  //minutes
min_INPUT: 	CmdLCD(CLR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Set Reminder");
		CmdLCD(GOTO_LINE2_POS0);	   
		StrLCD("MIN:");
                min_entered=getnumber(GOTO_LINE2_POS0+4,&minFlag);
		if(minFlag==0)
		{
			CmdLCD(CLR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD("Please enter Min");
                        delay_ms(1000);
                        goto min_INPUT;
		}
		if(min_entered>59)
                {
                        CmdLCD(CLR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD("Invalid Min");
                        delay_ms(1000);
                        goto min_INPUT;
                }
		reminderHour=hour_entered;
        	reminderMin=min_entered;
        	reminderSec=0;
			CmdLCD(CLR_LCD);
}
void set_time(void)
{
	u32 hour_entered;
	u32 min_entered;
	u8 hourFlag;
	u8 minFlag;
	hour_INPUT:	CmdLCD(CLR_LCD);
	        CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Set Time");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("HOUR:");
		hour_entered=getnumber(GOTO_LINE2_POS0+5,&hourFlag);
                if(hourFlag==0)
		{
			CmdLCD(CLR_LCD);
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("Plz enter Hour");
			delay_ms(1000);
			goto hour_INPUT;
		}
		if(hour_entered>23)
		{
                  	CmdLCD(CLR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD("Invalid Hour");
			delay_ms(1000);
			goto hour_INPUT;
		}

		  //minutes
min_INPUT: 	CmdLCD(CLR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Set Time");
		CmdLCD(GOTO_LINE2_POS0);	   
		StrLCD("MIN:");
                min_entered=getnumber(GOTO_LINE2_POS0+4,&minFlag);
		if(minFlag==0)
		{
			CmdLCD(CLR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD("Please enter Min");
                        delay_ms(1000);
                        goto min_INPUT;
		}
		if(min_entered>59)
                {
                        CmdLCD(CLR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD("Invalid Min");
                        delay_ms(1000);
                        goto min_INPUT;
                }
				 SetRTCTimeInfo(hour_entered,min_entered,0);
}
void display_status(void)
		 {
			CmdLCD(GOTO_LINE1_POS0);
			GetRTCTimeInfo(&hour,&min,&sec);
			DisplayRTCTime(hour,min,sec);
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("C:");
			U32LCD(consumed);
			StrLCD("  ");
			StrLCD("R:");
			U32LCD(remaining);
			StrLCD("  ");
			StrLCD("G:");	 
			U32LCD(goal);

		 }
         
void drink_reminder(void)
		 {
		   if((HOUR==reminderHour)&&(MIN==reminderMin)&&(SEC==reminderSec)&&(reminderFlag==0)&&(goalFlag==0))
			    {
			      reminderFlag=1;
				  yellow_led_on();
				  IOSET0=(1<<BUZZER); //buzz on
			    }
		 }
void intake_update(void)
		 {
			if(consumed<goal)
			   {
				 consumed++;
				 remaining--;
				 CmdLCD(CLR_LCD);
			     CmdLCD(GOTO_LINE1_POS0);
			     StrLCD("Intake updated");
			     delay_ms(2000);
				 if(consumed==goal)
						   {
						     goalFlag=1;
							 reminderFlag=0;
							 green_led_on();
							 CmdLCD(CLR_LCD);
			                 CmdLCD(GOTO_LINE1_POS0);
			                 StrLCD("GOAL ACHIEVED!!");
							 delay_ms(2000);
						    }
						   	if(consumed<goal)
							{  
						     reminderHour=HOUR;
						     reminderMin=MIN+1;
							 reminderSec=SEC;
						     if(reminderMin==60)
						     {
						     reminderMin=0;
							 reminderHour++;
							 if(reminderHour==24)
							 {
							   reminderHour=0;
							 }
							}
						}
					}
			}		

 			
void switch_press(void)
			{
			  while(reminderFlag==1)
			  {
			    if(READBIT(IOPIN0,SW_AL)==0)
			            {
			        	while(READBIT(IOPIN0,SW_AL)==0);
						yellow_led_off();
						IOCLR0=(1<<BUZZER);
				         intake_update();
						 reminderFlag=0;
						 CmdLCD(CLR_LCD);
						 }
					}
			}
  		
					
void drink_water(void)
			{
			  CmdLCD(CLR_LCD);
			  CmdLCD(GOTO_LINE1_POS0);
			  StrLCD("DRINK WATER");
			}
void reminder_screen(void)
{
		   if(reminderFlag==1)
			    	{  
			         drink_water();
					 switch_press();
					}
}

				 
void midnight_reset(void)
{
   if((HOUR==0)&&(MIN==0)&&(resetFlag==0))
    {
			consumed=0;
			remaining=goal;
			goalFlag=0;
			reminderFlag=0;
			green_led_off();
			resetFlag=1;
			CmdLCD(CLR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("NEW DAY..");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("HYDRATE YOURSELF");
			delay_ms(3000);
     }
	 if((HOUR!=0)&&(MIN!=0)&&(SEC!=0))
	 {
	   resetFlag=0;
	   }
}





void menu_configuration(void)
{
	u8 key;
	CmdLCD(CLR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("A:GOAL  B:REMIND");
	CmdLCD(GOTO_LINE2_POS0);
    StrLCD("C:DUR D:T #:EXIT");
	while(1)
	{
		key=keyscan();
		switch(key)
		{
			case 'A':change_goal();
				 	return;
			case 'B':change_remindertime();
				 	return;
			case 'C':set_duration();
			 		return;
			case 'D':set_time();
					return;
			case '#':{	  CmdLCD(CLR_LCD);
				 return; }
		}
	}
}
