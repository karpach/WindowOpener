#ifndef _TIMEEDITOR_h
#define _TIMEEDITOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"	
#else
#include "WProgram.h"
#endif


#include <Time.h>

class TimeEditor
{
	time_t time;
	byte digit;
	long lastblink;
	bool hide;
	bool isEditing;
	bool isChanged;		
public:
	void Init(time_t t);
	String Print();
	bool IsEditing();
	void Next();
	void Previous();
	void Up();
	void Down();
	time_t Done();
	void Edit();
	TimeEditor();
	~TimeEditor();
private:
	byte Truncate(int v, byte min, byte max);
};

#endif