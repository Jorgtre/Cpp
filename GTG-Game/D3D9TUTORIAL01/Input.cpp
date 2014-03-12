#include "Input.h"



bool KP[500];


bool keyHeld(SHORT Key)
{
	return (GetAsyncKeyState(Key));
}
bool keyClicked(SHORT Key)
{
	
	if (GetAsyncKeyState(Key)) 	
	{ 
		if (KP[Key] == false)	
		{
			KP[Key] = true;
			return true; 
		} 
	}
	else 
	{
		
		KP[Key] = false;
	}
	
	
	
	return false;
}




