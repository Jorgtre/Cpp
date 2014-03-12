#include <windows.h>
#include "Input.h"
#include "Output.h"
#include "Chunk.h"



	
#ifndef WORLD_H
#define WORLD_H
class World
{
public:

	void Init(IDirect3DDevice9* device);
	void Update(float dt);
	void Render();
	void Release();
	void AddChunk(float x, float y, float z);

private:

	IDirect3DDevice9* m_pDevice;
	float dt;
	vector<Chunk> chunk;


};
	
#endif