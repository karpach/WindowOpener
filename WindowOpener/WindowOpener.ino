// include the library code:
#include <TimeLib.h>
#include <Time.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "Menu.h"

int lcd_key = 0;
int adc_key_in = 0;
int last_adc_key_in = 0;
long lastDebounceTime;

void setup() {		
	Serial.begin(9600);		
	setTime(9, 12, 0, 0, 1, 16);
	setSyncProvider(getDS3231Time);
	setSyncInterval(60);
}

void loop() {		
	lcd_key = read_LCD_buttons();  // read the buttons

	if (lcd_key != last_adc_key_in) {
		// reset the debouncing timer
		lastDebounceTime = millis();
	}

	if ((millis() - lastDebounceTime) > 100) {
		Menu.onKeyPress(lcd_key);
		lastDebounceTime = millis();
	}

	last_adc_key_in = lcd_key;
	Menu.print();	
}

int read_LCD_buttons()
{
	adc_key_in = analogRead(0);      // read the value from the sensor 
									 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
									 // we add approx 50 to those values and check to see if we are close
	if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
										   // For V1.1 us this threshold
	if (adc_key_in < 50)   return btnRIGHT;
	if (adc_key_in < 250)  return btnUP;
	if (adc_key_in < 450)  return btnDOWN;
	if (adc_key_in < 650)  return btnLEFT;
	if (adc_key_in < 850)  return btnSELECT;

	return btnNONE;  // when all others fail, return this...
}

byte bcdToDec(byte val)
{
	return((val / 16 * 10) + (val % 16));
}

time_t getDS3231Time()
{
	Wire.beginTransmission(DS3231_I2C_ADDRESS);
	Wire.write(0x00);
	Wire.endTransmission();

	// request the 7 data fields (secs, min, hr, dow, date, mth, yr)
	Wire.requestFrom(DS3231_I2C_ADDRESS, tmNbrFields);
	if (!Wire.available())
	{
		return 0;
	}

	tmElements_t tm;
	tm.Second = bcdToDec(Wire.read() & 0x7f);
	tm.Minute = bcdToDec(Wire.read());
	tm.Hour = bcdToDec(Wire.read() & 0x3f); // mask assumes 24hr clock
	tm.Wday = bcdToDec(Wire.read());
	tm.Day = bcdToDec(Wire.read());
	tm.Month = bcdToDec(Wire.read());
	tm.Year = y2kYearToTm((bcdToDec(Wire.read())));
	return(makeTime(tm));
}
