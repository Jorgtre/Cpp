#include <iostream>
#include <windows.h>
#include <ios>

		//Hex value
#define VK_LMOUSE 0x01
#define VK_RMOUSE 0x02
#define VK_A 0x41 
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A



bool keyHeld(SHORT Key);
bool keyClicked(SHORT Key);







#ifndef INPUT_H
#define INPUT_H
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

