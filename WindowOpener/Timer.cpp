#include "Timer.h"
#include <Wire.h>


Timer::Timer()
{
	Wire.begin();	
}

Timer::~Timer()
{
}

void Timer::SetTime(time_t time)
{
	if (time == 0)
	{
		return;
	}
	if (get3231Temp() != -100)
	{
		tmElements_t tm;
		breakTime(time, tm);
		// sets time and date data to DS3231
		Wire.beginTransmission(DS3231_I2C_ADDRESS);
		Wire.write(0); // set next input to start at the seconds register
		Wire.write(decToBcd(tm.Second)); // set seconds
		Wire.write(decToBcd(tm.Minute)); // set minutes
		Wire.write(decToBcd(tm.Hour)); // set hours
		Wire.write(decToBcd(tm.Wday)); // set day of week (1=Sunday, 7=Saturday)
		Wire.write(decToBcd(tm.Day)); // set date (1 to 31)
		Wire.write(decToBcd(tm.Month)); // set month
		Wire.write(decToBcd(tmYearToY2k(tm.Year))); // set year (0 to 99)
		Wire.endTransmission();
	}	
	setTime(time);
}

String Timer::GetTimeStr(bool showSeconds)
{		
	String result = String(hour()) + ":" + ((minute() < 10) ? String("0") + minute() : String(minute()));
	if (showSeconds)
	{
		result +=":" + ((second() < 10) ? String("0") + second() : String(second()));
	}
	return result;
}

String Timer::GetDateStr()
{	
	return String(day()) + "/" + month() + "/" + year();	
}

String Timer::GetTempStr(bool isFahrenheit)
{
	float fTemp = get3231Temp();
	if (fTemp == -100)
	{
		return String("");
	}	
	if (isFahrenheit)
	{
		fTemp = fTemp * 9 / 5 + 32;
		return String(fTemp, 1) + "F";
	}
	else
	{
		return String(fTemp, 1) + "C";
	}
}

float Timer::get3231Temp()
{
	//temp registers (11h-12h) get updated automatically every 64s
	Wire.beginTransmission(DS3231_I2C_ADDRESS);
	Wire.write(0x11);
	Wire.endTransmission();
	Wire.requestFrom(DS3231_I2C_ADDRESS, 2);

	if (Wire.available()) {
		tMSB = Wire.read(); //2's complement int portion
		tLSB = Wire.read(); //fraction portion

		temp3231 = (tMSB & B01111111); //do 2's math on Tmsb
		temp3231 += ((tLSB >> 6) * 0.25); //only care about bits 7 & 8
	}
	else {
		temp3231 = -100;
	}

	return temp3231;
}

byte Timer::decToBcd(byte val)
{
	return((val / 10 * 16) + (val % 10));
}
