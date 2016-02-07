// Timer.h

#ifndef _TIMER_h
#define _TIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"	
#else
#include "WProgram.h"
#endif

#include <LiquidCrystal.h>
#include <Time.h>
#define DS3231_I2C_ADDRESS 0x68

class Timer
{	
	byte tMSB, tLSB;
	float temp3231;
public:
	Timer();
	~Timer();	
	String GetTimeStr(bool showSeconds);
	String GetDateStr();
	String GetTempStr(bool isFahrenheit);	
	void SetTime(time_t time);
private:
	float get3231Temp();	
	byte decToBcd(byte val);	
};

#endif
