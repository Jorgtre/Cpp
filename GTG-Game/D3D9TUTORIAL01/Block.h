#ifndef BLOCK_H
#define BLOCK_H

#include <windows.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include "d3dUtil.h"
#include <debugapi.h>
#include <stdio.h>




const int NUM_OF_VERTS = 24;
const int NUM_OF_INDICES = 36;

class TexBlock
{
public:

	TexBlock();
	TexBlock(float _x, float _y, float _z, float _size, const char* FileName);

	~TexBlock();


	void Init(IDirect3DDevice9* device);
	void Update(float dt);
	void Render(IDirect3DDevice9* device);
	void Release();




	float X();
	float Y();
	float Z();
	void moveY(float amt);
	void moveX(float amt);
	void moveZ(float amt);
	void rotX(float amt);
	void rotY(float amt);
	void rotZ(float amt);
	D3DXVECTOR3 position();



	D3DXMATRIX getMatrix();


private:
	float delta;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
	D3DXVECTOR3 rot;
	D3DXMATRIX Matrix;
	std::string texName;

	IDirect3DVertexBuffer9* vertexBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	IDirect3DTexture9* textureBuffer;
	
	
	

};



class ColorBlock
{
public:

	ColorBlock(float _x, float _y, float _z, float _size, D3DCOLOR _color);

	~ColorBlock();


	void Init(IDirect3DDevice9* device);
	void Update(float dt);
	void Render(IDirect3DDevice9* device);
	void Release();


	void moveY(float amt);
	void moveX(float amt);
	void moveZ(float amt);
	void rotX(float amt);
	void rotY(float amt);
	void rotZ(float amt);
	D3DXVECTOR3 position();

	D3DXMATRIX getMatrix();


private:
	float delta;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
	D3DXVECTOR3 rot;
	D3DXMATRIX Matrix;
	D3DCOLOR color;

	IDirect3DVertexBuffer9* vertexBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	




};




#endif
