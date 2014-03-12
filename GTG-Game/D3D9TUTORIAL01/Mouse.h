#include <windows.h>



#ifndef MOUSE_H
#define MOUSE_H
class mouse
{
public:
	mouse();
	~mouse();

	void update();
	float getDX();
	float getDY();
	int getX();
	int getY();
	bool grabbed();
	void grabbed(bool x);
	void toggleGrabb();

private:
	float prevMouseY;
	float prevMouseX;
	float DX, DY;
	bool isgrabbed = false;
	POINT p;
	POINT LockAt;
	CURSORINFO I;

};
#endif