#ifndef _VENTILATIONEDITOR_h
#define _VENTILATIONEDITOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"	
#else
#include "WProgram.h"
#endif

#include "TimeEditor.h"

enum VentilationSettings
{
	VentilationSettingsView,
	VentilationSettingsTimeEdit,
	VentilationSettingsStatusEdit
};

struct VentilationAction
{
	long Time;
	byte Duration;
};

class VentilationEditor
{
public:
	VentilationEditor();
	~VentilationEditor();
	String Print();
	bool Next();
	bool Previous();
	void Reset();
	void Up();
	void Down();
	void Select();
private:
	VentilationAction ventilations[10];
	TimeEditor editor;
	byte counter;
	VentilationSettings status;
	long lastblink;
	bool hide;
};

#endif

