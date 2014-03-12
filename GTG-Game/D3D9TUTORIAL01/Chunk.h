#include "d3dUtil.h"
#include "Block.h"
#include <Windows.h>
#include "Output.h"
#include <vector>
#include "Input.h"



void Init22(IDirect3DDevice9* device);
void Update22(float dt);
void Render22(IDirect3DDevice9* device);
void Release22();





#ifndef CHUNK_H
#define CHUNK_H


class Chunk
{
public:
	
	Chunk(float _x, float _y, float _z);
	~Chunk();
	void Init(IDirect3DDevice9* Device);
	void Update(float dt);
	void Render();
	void Release();
	void addTexBlock(int _x, int _y, int _z);
	void addTexBlock(D3DXVECTOR3 pos);
	void deleteTexBlock(D3DXVECTOR3 pos);
	void deleteTexBlock(int, int y, int z);

	TexBlock getTexBlock(D3DXVECTOR3 At);
	TexBlock getTexBlock(int x, int y, int z);
	int getTexBlockIndex(int x, int y, int z);

	void addToX(float amt);
	void addToY(float amt);
	void addToZ(float amt);


	vector<TexBlock> wos;


private:
	float x, y, z;

	IDirect3DDevice9* Device;
	
	bool blockAt[10][10][10];

	



};








#endif
