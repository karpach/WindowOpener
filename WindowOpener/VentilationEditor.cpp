#include "VentilationEditor.h"

VentilationEditor::VentilationEditor()
{
	counter = 0;		
	status = VentilationSettingsView;
	editor.Init(ventilations[counter].Time);
}


VentilationEditor::~VentilationEditor()
{
}

void VentilationEditor::Reset()
{
	counter = 0;
	editor.Init(ventilations[counter].Time);
}

bool VentilationEditor::Next()
{		
	if (editor.IsEditing())
	{
		editor.Next();
	}
	else 
	{
		if (counter < 9)
		{
			counter++;
			editor.Init(ventilations[counter].Time);
		}
		else {
			return false;
		}
	}
	return true;
}

bool VentilationEditor::Previous()
{
	if (editor.IsEditing())
	{
		editor.Previous();
	}
	else 
	{
		if (counter > 0)
		{
			counter--;
			editor.Init(ventilations[counter].Time);
		}
		else
		{
			return false;
		}
	}
	return true;
}

void VentilationEditor::Up()
{
	switch (status)
	{
	case VentilationSettingsView:
		break;
	case VentilationSettingsTimeEdit:
		editor.Up();
		break;
	case VentilationSettingsStatusEdit:
		ventilations[counter].Duration++;
		break;
	default:
		break;
	}	
}

void VentilationEditor::Down()
{
	switch (status)
	{
	case VentilationSettingsView:
		break;
	case VentilationSettingsTimeEdit:
		editor.Down();
		break;
	case VentilationSettingsStatusEdit:
		if (ventilations[counter].Duration > 0)
		{
			ventilations[counter].Duration--;
		}		
		break;
	default:
		break;
	}	
}

void VentilationEditor::Select()
{	
	switch (status)
	{
	case VentilationSettingsView:
		status = VentilationSettingsTimeEdit;
		editor.Edit();
		break;
	case VentilationSettingsTimeEdit:
		status = VentilationSettingsStatusEdit;
		ventilations[counter].Time = editor.Done();
		break;
	case VentilationSettingsStatusEdit:
		status = VentilationSettingsView;
		break;
	default:
		break;
	}
}

String VentilationEditor::VentilationEditor::Print()
{	
	String result = String(counter+1) + ">" + editor.Print();	
	if (hide && status == VentilationSettingsStatusEdit)
	{
		result += "         ";
	}	
	else
	{
		result += ventilations[counter].Duration > 0 ? " " + String(ventilations[counter].Duration) + " min   " : " Disabled";
	}	
	if (millis() - lastblink > 500)
	{
		hide = !hide;
		lastblink = millis();
	}
	return result;
}
