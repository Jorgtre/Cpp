#include <Windows.h>
#include <iostream>
#include <sstream>

#define DBOUT( s )            \
{                             \
	std::ostringstream os_;    \
	os_ << s;                   \
	OutputDebugString(os_.str().c_str());  \
}




void outputTest()
{
	//DBOUT("TEST");

	OutputDebugString("asdsad" + 1231231);
}