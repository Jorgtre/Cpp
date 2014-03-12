#include <windows.h>
#include "Block.h"
#include "Output.h"



TexBlock::TexBlock()
{

}
TexBlock::TexBlock(float _x, float _y, float _z, float _size, const char* FileName)
{
	pos.x = _x;
	pos.y = _y;
	pos.z = _z;
	size.x = _size;
	size.y = _size;
	size.z = _size;
	texName = FileName;
	
}

void TexBlock::Init(IDirect3DDevice9* device)
{

	
	
	d3dVertex::VertexPosTex3D verts[NUM_OF_VERTS] =
	{
		d3dVertex::VertexPosTex3D(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPosTex3D(1.0f, 1.0f, -1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPosTex3D(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPosTex3D(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

		//Back face
		d3dVertex::VertexPosTex3D(1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPosTex3D(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPosTex3D(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPosTex3D(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),

		//Left face
		d3dVertex::VertexPosTex3D(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPosTex3D(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPosTex3D(-1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPosTex3D(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

		//Right face
		d3dVertex::VertexPosTex3D(1.0f, 1.0f, -1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPosTex3D(1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPosTex3D(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPosTex3D(1.0f, -1.0f, 1.0f, 1.0f, 1.0f),

		//Top face
		d3dVertex::VertexPosTex3D(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPosTex3D(1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPosTex3D(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPosTex3D(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),

		//Bottom face
		d3dVertex::VertexPosTex3D(1.0f, -1.0f, 1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPosTex3D(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPosTex3D(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPosTex3D(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
	};





	//Create Vertex Buffer
	device->CreateVertexBuffer(NUM_OF_VERTS * sizeof(d3dVertex::VertexPosTex3D), NULL, d3dVertex::VertexPosTex3D::FVF,
								D3DPOOL_MANAGED, &vertexBuffer, NULL);

	//Copy it to Memory
	VOID* pVerts; // pointer to verts
	vertexBuffer->Lock(0, sizeof(verts), (void**) &pVerts, 0);
	memcpy_s(pVerts, sizeof(verts), verts, sizeof(verts));
	vertexBuffer->Unlock();

	WORD  indices[NUM_OF_INDICES] =
	{
		//Front face
		0, 1, 2,
		2, 1, 3,

		//Back face
		4, 5, 6,
		6, 5, 7,

		//Left face
		8, 9, 10,
		10, 9, 11,


		//Right face
		12, 13, 14,
		14, 13, 15,

		//Top face
		16, 17, 18,
		18, 17, 19,

		//Bottom face
		20, 21, 22,
		22, 21, 23

	};
	
	//Create index buffer?
	device->CreateIndexBuffer(NUM_OF_INDICES * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED,
								&indexBuffer, NULL);

	VOID* pIndices;
	indexBuffer->Lock(0, sizeof(indices), (void**)&pIndices, 0);
	memcpy_s(pIndices, sizeof(indices), indices, sizeof(indices));
	indexBuffer->Unlock();

	//Load texture

	D3DXCreateTextureFromFile(device, texName.c_str(), &textureBuffer);
	if (!textureBuffer)
	{
		MessageBox(NULL, "Failed to Create/Load texture", NULL, NULL);
		return;
	}

	


}
void TexBlock::Update(float dt)
{
	delta = dt;

	//rot.x += dt;
	//rot.y += dt;
	//rot.z += dt;

}
void TexBlock::Render(IDirect3DDevice9* device)
{

	

	
	device->SetTexture(0, textureBuffer);
	device->SetTransform(D3DTS_WORLD, &getMatrix());
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(d3dVertex::VertexPosTex3D));
	device->SetIndices(indexBuffer);
	device->SetFVF(d3dVertex::VertexPosTex3D::FVF);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_OF_INDICES, 0, NUM_OF_INDICES / 3);

	
	

}
void TexBlock::Release()
{
	d3d::Release(textureBuffer);
	d3d::Release(indexBuffer);
	d3d::Release(vertexBuffer);
}
TexBlock::~TexBlock()
{

}


D3DXMATRIX TexBlock::getMatrix()
{
	D3DXMATRIX scale, Translate, rx, ry, rz;
	D3DXMatrixScaling(&scale, size.x, size.y, size.z);
	D3DXMatrixRotationX(&rx, rot.x);
	D3DXMatrixRotationY(&ry, rot.y);
	D3DXMatrixRotationZ(&rz, rot.z);
	D3DXMatrixTranslation(&Translate, pos.x, pos.y, pos.z);
	
	

	//Matrix = scale * rx * ry * rz * Translate;
	Matrix = scale * Translate;
	return Matrix;
	
}

float TexBlock::X()
{
	return pos.x;
}
float TexBlock::Y()
{
	return pos.y;
}
float TexBlock::Z()
{
	return pos.z;
}
void TexBlock::moveY(float amt)
{
	pos.y += amt * delta;
}
void TexBlock::moveX(float amt)
{
	pos.x += amt * delta;
}
void TexBlock::moveZ(float amt)
{
	pos.z += amt * delta;
}
void TexBlock::rotX(float amt)
{
	rot.x += amt * delta;
}
void TexBlock::rotY(float amt)
{
	rot.y += amt * delta;
}
void TexBlock::rotZ(float amt)
{
	rot.z += amt * delta;
}
D3DXVECTOR3 TexBlock::position()
{
	return pos;
}







//===================================ColorBlock=============================================
ColorBlock::ColorBlock(float _x, float _y, float _z, float _size, D3DCOLOR _color)
{
	pos.x = _x;
	pos.y = _y;
	pos.z = _z;
	size.x = _size;
	size.y = _size;
	size.z = _size;
	color = _color;

}

void ColorBlock::Init(IDirect3DDevice9* device)
{



	d3dVertex::VertexPositionColor verts[NUM_OF_VERTS] =
	{
		d3dVertex::VertexPositionColor(-1.0f, 1.0f, -1.0f, color),
		d3dVertex::VertexPositionColor(1.0f, 1.0f, -1.0f, color),
		d3dVertex::VertexPositionColor(-1.0f, -1.0f, -1.0f, color),
		d3dVertex::VertexPositionColor(1.0f, -1.0f, -1.0f, color),

		//Back face
		d3dVertex::VertexPositionColor(1.0f, 1.0f, 1.0f, color),
		d3dVertex::VertexPositionColor(-1.0f, 1.0f, 1.0f, color),
		d3dVertex::VertexPositionColor(1.0f, -1.0f, 1.0f, color),
		d3dVertex::VertexPositionColor(-1.0f, -1.0f, 1.0f, color),

		//Left face
		d3dVertex::VertexPositionColor(-1.0f, 1.0f, 1.0f, color),
		d3dVertex::VertexPositionColor(-1.0f, 1.0f, -1.0f, color),
		d3dVertex::VertexPositionColor(-1.0f, -1.0f, 1.0f, color),
		d3dVertex::VertexPositionColor(-1.0f, -1.0f, -1.0f, color),

		//Right face
		d3dVertex::VertexPositionColor(1.0f, 1.0f, -1.0f, color),
		d3dVertex::VertexPositionColor(1.0f, 1.0f, 1.0f, color),
		d3dVertex::VertexPositionColor(1.0f, -1.0f, -1.0f, color),
		d3dVertex::VertexPositionColor(1.0f, -1.0f, 1.0f, color),

		//Top face
		d3dVertex::VertexPositionColor(-1.0f, 1.0f, 1.0f, color),
		d3dVertex::VertexPositionColor(1.0f, 1.0f, 1.0f, color),
		d3dVertex::VertexPositionColor(-1.0f, 1.0f, -1.0f, color),
		d3dVertex::VertexPositionColor(1.0f, 1.0f, -1.0f, color),

		//Bottom face
		d3dVertex::VertexPositionColor(1.0f, -1.0f, 1.0f, color),
		d3dVertex::VertexPositionColor(-1.0f, -1.0f, 1.0f, color),
		d3dVertex::VertexPositionColor(1.0f, -1.0f, -1.0f, color),
		d3dVertex::VertexPositionColor(-1.0f, -1.0f, -1.0f, color),
	};





	//Create Vertex Buffer
	device->CreateVertexBuffer(NUM_OF_VERTS * sizeof(d3dVertex::VertexPositionColor), NULL,
								d3dVertex::VertexPositionColor::FVF,
								D3DPOOL_MANAGED, &vertexBuffer, NULL);

	//Copy it to Memory
	VOID* pVerts; // pointer to verts
	vertexBuffer->Lock(0, sizeof(verts), (void**) &pVerts, 0);
	memcpy_s(pVerts, sizeof(verts), verts, sizeof(verts));
	vertexBuffer->Unlock();

	WORD  indices[NUM_OF_INDICES] =
	{
		//Front face
		0, 1, 2,
		2, 1, 3,

		//Back face
		4, 5, 6,
		6, 5, 7,

		//Left face
		8, 9, 10,
		10, 9, 11,


		//Right face
		12, 13, 14,
		14, 13, 15,

		//Top face
		16, 17, 18,
		18, 17, 19,

		//Bottom face
		20, 21, 22,
		22, 21, 23

	};

	//Create index buffer?
	device->CreateIndexBuffer(NUM_OF_INDICES * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED,
		&indexBuffer, NULL);

	VOID* pIndices;
	indexBuffer->Lock(0, sizeof(indices), (void**) &pIndices, 0);
	memcpy_s(pIndices, sizeof(indices), indices, sizeof(indices));
	indexBuffer->Unlock();

	//Load texture

	




}
void ColorBlock::Update(float dt)
{
	delta = dt;

	//rot.x += dt;
	//rot.y += dt;
	//rot.z += dt;

}
void ColorBlock::Render(IDirect3DDevice9* device)
{




	//device->SetTexture(0, );
	device->SetTransform(D3DTS_WORLD, &getMatrix());
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(d3dVertex::VertexPositionColor));
	device->SetIndices(indexBuffer);
	device->SetFVF(d3dVertex::VertexPositionColor::FVF);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_OF_INDICES, 0, NUM_OF_INDICES / 3);




}
void ColorBlock::Release()
{
	d3d::Release(indexBuffer);
	d3d::Release(vertexBuffer);
}
ColorBlock::~ColorBlock()
{

}

D3DXMATRIX ColorBlock::getMatrix()
{
	D3DXMATRIX scale, Translate, rx, ry, rz;
	D3DXMatrixScaling(&scale, size.x, size.y, size.z);
	D3DXMatrixRotationX(&rx, rot.x);
	D3DXMatrixRotationY(&ry, rot.y);
	D3DXMatrixRotationZ(&rz, rot.z);
	D3DXMatrixTranslation(&Translate, pos.x, pos.y, pos.z);



	//Matrix = scale * rx * ry * rz * Translate;
	Matrix = scale * Translate;
	return Matrix;

}

void ColorBlock::moveY(float amt)
{
	pos.y += amt * delta;
}
void ColorBlock::moveX(float amt)
{
	pos.x += amt * delta;
}
void ColorBlock::moveZ(float amt)
{
	pos.z += amt * delta;
}
void ColorBlock::rotX(float amt)
{
	rot.x += amt * delta;
}
void ColorBlock::rotY(float amt)
{
	rot.y += amt * delta;
}
void ColorBlock::rotZ(float amt)
{
	rot.z += amt * delta;
}
D3DXVECTOR3 ColorBlock::position()
{
	return position();
}



