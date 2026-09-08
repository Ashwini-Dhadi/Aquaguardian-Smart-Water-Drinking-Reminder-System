#include<lpc21xx.h>
#include"types.h"
#include"lcd_defines.h"
#ifndef PCLK
#define PCLK 15000000
#endif

#define PREINT_VAL  ((int)(PCLK/32768)-1)

#define PREFRAC_VAL (PCLK-((PREINT_VAL+1)*32768))

#define RTC_ENABLE (1<<0)
// Bit 1 ? Clock Reset --> 1 = Reset RTC counters    0 = Normal operation

#define RTC_RESET (1<<1)

#define RTC_CLKSRC (1<<4)

void RTC_Init(void) 
{
	CCR|=(RTC_ENABLE|RTC_CLKSRC);
  // Disable and reset the RTC
	//CCR = RTC_RESET;
//  #ifndef CPU_LPC2148
  // Set prescaler integer and fractional parts
	//PREINT = PREINT_VAL;
	//PREFRAC = PREFRAC_VAL;
  // Enable the RTC
	//CCR = RTC_ENABLE;  
//	#else
	// Enable the RTC with external clock source
	//CCR = RTC_ENABLE;/* | RTC_CLKSRC; */ 
//	#endif

}

void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)

{

	*hour = HOUR;

	*minute = MIN;

	*second = SEC;
}
void DisplayRTCTime(u32 hour, u32 minute, u32 second)

{

	CmdLCD(GOTO_LINE1_POS0);

	CharLCD(hour/10+48);

	CharLCD(hour%10+48);

	CharLCD(':');

	CharLCD(minute/10+48);

	CharLCD(minute%10+48);

	CharLCD(':');

	CharLCD(second/10+48);

	CharLCD(second%10+48);
}
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{

	HOUR = hour;

	MIN = minute;

	SEC = second;

}