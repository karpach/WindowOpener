// 
// 
// 

#include "Menu.h"

MenuClass::MenuClass(LiquidCrystal l):lcd(l)
{	
	currentScreen = Main;
	prevScreen = Main;
	lcd.begin(16, 2);	
}


void MenuClass::print()
{		
	lcd.setCursor(0, 0);
	if (currentScreen != prevScreen)
	{
		lcd.clear();
		prevScreen = currentScreen;
	}
	switch (currentScreen)
	{
		case Main:
			lcd.print(timer.GetTimeStr(true));
			lcd.print(" ");
			lcd.print(timer.GetTempStr(true));
			break;
		case Settings:
			lcd.print("Set Time");
			lcd.setCursor(0, 1);
			lcd.print(editor.Print());
			break;
		case Ventilation:
			lcd.print("Ventilation ");
			lcd.setCursor(0, 1);			
			lcd.print(ventilationEditor.Print());
			break;

	}	
}

void MenuClass::nextScreen()
{
	switch (currentScreen)
	{
		case Main:
			currentScreen = Settings;
			editor.Init(now());
			break;
		case Settings:
			currentScreen = Ventilation;
			editor.Init(now());			
			break;
		case Ventilation:
			currentScreen = Main;
			ventilationEditor.Reset();
			break;
	}	
}

void MenuClass::previousScreen()
{
	switch (currentScreen)
	{
		case Ventilation:
			currentScreen = Settings;
			editor.Init(now());
			break;
		case Main:
			currentScreen = Ventilation;
			editor.Init(now());
			break;
		case Settings:
			currentScreen = Main;
			break;
	}
}

void MenuClass::onKeyPress(int key)
{
	switch (key)
	{
		case btnRIGHT:
			if (currentScreen == Settings && editor.IsEditing())
			{
				editor.Next();
				return;
			}
			if (currentScreen == Ventilation)
			{
				if (!ventilationEditor.Next()) 
				{
					nextScreen();
				}
				return;
			}
			nextScreen();
			break;
		case btnLEFT:
			if (currentScreen == Settings && editor.IsEditing())
			{
				editor.Previous();
				return;
			}
			if (currentScreen == Ventilation)
			{
				if (!ventilationEditor.Previous())
				{
					previousScreen();
				}
				return;
			}
			previousScreen();
			break;
		case btnUP:
			switch (currentScreen)
			{
			case Settings:
				editor.Up();
				break;
			case Ventilation:
				ventilationEditor.Up();
				break;
			default:
				break;
			}
			break;
		case btnDOWN:			
			switch (currentScreen)
			{
			case Settings:
				editor.Down();
				break;
			case Ventilation:
				ventilationEditor.Down();
				break;
			default:
				break;
			}
			break;
		case btnSELECT:
			switch (currentScreen)
			{
			case Settings:
				if (editor.IsEditing())
				{
					timer.SetTime(editor.Done());
				}
				else
				{
					editor.Edit();
				}				
				break;
			case Ventilation:
				ventilationEditor.Select();
				break;
			default:
				break;
			}			
			break;
	}
}

MenuClass Menu(LiquidCrystal(8, 13, 9, 4, 5, 6, 7));