#include "Chunk.h"









const SHORT  NoB = 10;
const SHORT  nob2 = NoB * NoB;

TexBlock BList[1600];






void Init22(IDirect3DDevice9* device)
{

	int i = 0;
	for (int x = -NoB / 2; x < NoB / 2; x++){
		for (int z = -NoB / 2; z < NoB / 2; z++){

			BList[i] = TexBlock::TexBlock(x, -5, z, 0.5f, "Metal_3.png");
			BList[i].Init(device);
			
			
			i++;
		}
	}

	
	



}
void Update22(float dt)
{
	
	
	
	
}
void Render22(IDirect3DDevice9* device)
{
	
	for (int x = 0; x < nob2; x++)
	{
		BList[x].Render(device);
	}

}
void Release22()
{
	

	for (int x = 0; x < NoB * NoB; x++){
		BList[x].Release();
	}


}




Chunk::Chunk(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;

}
Chunk::~Chunk()
{

}


void Chunk::Init(IDirect3DDevice9* _Device)
{
	Device = _Device;

	int i = 10;


	for (int x = 0; x < i ; x++)
	{
		for (int z = 0; z < i; z++)
		{
			
			addTexBlock(x , 0, z );
			
			
		}
	}


	

	

}
void Chunk::Update(float dt)
{

}
void Chunk::Render()
{
	
		for (int x = 0; x < wos.size(); x++)
		{
			wos[x].Render(Device);
		}
		
	

}
void Chunk::Release()
{
	
	for (int x = 0; x < wos.size(); x++)
	{
		wos[x].Release();
	}
}
void Chunk::addTexBlock(int _x, int _y, int _z)
{
	
		wos.push_back(TexBlock(_x + x, _y + y, _z + z, 0.5f, "Metal_3.png"));
		wos[wos.size() - 1].Init(Device);
		blockAt[_x][_y][_z] = true;


}
void Chunk::addTexBlock(D3DXVECTOR3 pos)
{
	addTexBlock(pos.x, pos.y, pos.z);
}
void Chunk::deleteTexBlock(int x, int y, int z)
{
		
	//if (blockAt[x][y][z])
	{
		int index = getTexBlockIndex(x, y, z);

		wos.at(index).Release();
		wos.erase(wos.begin() + index);

		blockAt[x][y][z] = false;
	}
	
}
void Chunk::deleteTexBlock(D3DXVECTOR3 At)
{
	deleteTexBlock(At.x, At.y, At.z);
}
TexBlock Chunk::getTexBlock(D3DXVECTOR3 At)
{


		for (unsigned int i = 0; i < wos.size(); i++)
		{
			if (wos[i].position() == At) { return wos[i]; }
		}

	

}
TexBlock Chunk::getTexBlock(int x, int y, int z)
{
	return getTexBlock(D3DXVECTOR3(x, y, z));
}
int Chunk::getTexBlockIndex(int x, int y, int z)
{
	
	for (int i = 0; i < wos.size(); i++)
	{

		

		int x2 = wos.at(i).X();
		int y2 = wos.at(i).Y();
		int z2 = wos.at(i).Z();

		if (x+this->x == x2 && y+this->y == y2 && z+this->z == z2) { return i; }
	}


	return NULL;
}
void Chunk::addToX(float amt)
{
	x += amt;
}
void Chunk::addToY(float amt)
{
	y += amt;
}
void Chunk::addToZ(float amt)
{
	z += amt;
}



