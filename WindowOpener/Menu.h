// Menu.h

#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"	
#else
	#include "WProgram.h"
#endif

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#include <LiquidCrystal.h>
#include "Timer.h"
#include "TimeEditor.h"
#include "VentilationEditor.h"


enum MenuScreens
{
	Main,
	Settings,
	Ventilation
};

class MenuClass
{
	LiquidCrystal lcd;
	MenuScreens currentScreen;
	MenuScreens prevScreen;	
	Timer timer;	
	TimeEditor editor;
	VentilationEditor ventilationEditor;
 protected:	 

 public:
	MenuClass(LiquidCrystal lcd);
	void print();
	void nextScreen();
	void previousScreen(); 
	void onKeyPress(int key);
};

extern MenuClass Menu;

#endif

