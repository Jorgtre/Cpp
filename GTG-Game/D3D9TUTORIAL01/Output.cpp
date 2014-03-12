#include "Output.h"

void print(string text, float num)
{
	string numstr = static_cast<ostringstream*>(&(ostringstream() << num))->str();
	std::string result = text + numstr + "\n";
	OutputDebugString(result.c_str());

}
void printXY(float X, float Y)
{
	string stringX = static_cast<ostringstream*>(&(ostringstream() << X))->str();
	string stringY = static_cast<ostringstream*>(&(ostringstream() << Y))->str();
	string output = "X : " + stringX + "| Y : " + stringY + "\n";
	OutputDebugString(output.c_str());
}
void printStr(string text)
{
	OutputDebugString(text.c_str());
}
void printXMATRIX(D3DXMATRIX matrix)
{
	string mstr[16];
	string output;
	string space = " | ";
	
	mstr[0] = toString(matrix._11);
	mstr[1] = toString(matrix._12);
	mstr[2] = toString(matrix._13);
	mstr[3] = toString(matrix._14);
	mstr[4] = toString(matrix._21);
	mstr[5] = toString(matrix._22);
	mstr[6] = toString(matrix._23);
	mstr[7] = toString(matrix._24);
	mstr[8] = toString(matrix._31);
	mstr[9] = toString(matrix._32);
	mstr[10] = toString(matrix._33);
	mstr[11] = toString(matrix._34);
	mstr[12] = toString(matrix._41);
	mstr[13] = toString(matrix._42);
	mstr[14] = toString(matrix._43);
	mstr[15] = toString(matrix._44);

	
	for (int x = 0; x < 16; x++){
		output = output + space + mstr[x];
	}



	OutputDebugString((output + "\n").c_str());




	
}
void printVector3(D3DXVECTOR3 vector)
{
	string output;
	string v1, v2, v3;
	string space = " | ";

	v1 = toString(vector.x);
	v2 = toString(vector.y);
	v3 = toString(vector.z);

	output = space + v1 + space + v2 + space + v3 + "\n";
	OutputDebugString(output.c_str());
}



string toString(float num)
{
	return static_cast<ostringstream*>(&(ostringstream() << num))->str();
}


