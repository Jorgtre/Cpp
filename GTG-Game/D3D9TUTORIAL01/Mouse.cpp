#include "Mouse.h"


mouse::mouse()
{

}
mouse::~mouse()
{

}
void mouse::update()
{

	GetCursorPos(&p);
	if (isgrabbed)
	{

		SHORT x = p.x;
		SHORT y = p.y;
		SetCursorPos(LockAt.x, LockAt.y);
		GetCursorPos(&p);
		SHORT jumpX = p.x - x;
		SHORT jumpY = p.y - y;

		DY = (y - prevMouseY) - jumpY;
		DX = (x - prevMouseX) - jumpX;


		ShowCursor(false);

		SHORT Limit = 100;

		if (DX > Limit) { DX = Limit; }
		if (DX < -Limit) { DX = -Limit; }


		if (DY > Limit) { DY = Limit; }
		if (DY < -Limit) { DY = -Limit; }

	}
	else
	{
		ShowCursor(true);
		DX = 0;
		DY = 0;
	}
	prevMouseX = p.x;
	prevMouseY = p.y;
}
bool mouse::grabbed()
{
	return isgrabbed;
}
void mouse::grabbed(bool x)
{
	isgrabbed = x;
}
void mouse::toggleGrabb()
{
	isgrabbed = !isgrabbed;
	GetCursorPos(&p);
	LockAt = p;

}
float mouse::getDX()
{
	return DX;
}
float mouse::getDY()
{
	return DY;
}