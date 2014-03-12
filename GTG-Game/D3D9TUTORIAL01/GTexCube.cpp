#include "GTexCube.h"

GTexCube::GTexCube(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scal, const char* FileName)
{
	position = pos;
	rotation = rot;
	scale = scal;
	texName = FileName;

}

GTexCube::~GTexCube()
{

}

void GTexCube::Initialize(IDirect3DDevice9* device)
{
	//Create Vertex Buffer
	d3dVertex::VertexPositionTexture verts[NUM_VERTS] =
	{
		//Front face
		d3dVertex::VertexPositionTexture(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPositionTexture(1.0f, 1.0f, -1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPositionTexture(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPositionTexture(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

		//Back face
		d3dVertex::VertexPositionTexture(1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPositionTexture(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPositionTexture(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPositionTexture(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),

		//Left face
		d3dVertex::VertexPositionTexture(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPositionTexture(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPositionTexture(-1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPositionTexture(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

		//Right face
		d3dVertex::VertexPositionTexture(1.0f, 1.0f, -1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPositionTexture(1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPositionTexture(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPositionTexture(1.0f, -1.0f, 1.0f, 1.0f, 1.0f),

		//Top face
		d3dVertex::VertexPositionTexture(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPositionTexture(1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPositionTexture(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPositionTexture(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),

		//Bottom face
		d3dVertex::VertexPositionTexture(1.0f, -1.0f, 1.0f, 0.0f, 0.0f),
		d3dVertex::VertexPositionTexture(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f),
		d3dVertex::VertexPositionTexture(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		d3dVertex::VertexPositionTexture(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

	};

	//Create VertexBuffer
	device->CreateVertexBuffer(NUM_VERTS * sizeof(d3dVertex::VertexPositionTexture), NULL, d3dVertex::VertexPositionTexture::FVF, D3DPOOL_MANAGED, &vBuffer, NULL);

	

	//Copy it to Memory
	VOID* pVerts;
	vBuffer->Lock(0, sizeof(verts), (void**)&pVerts, 0);
	memcpy_s(pVerts, sizeof(verts), verts, sizeof(verts));
	vBuffer->Unlock();


	//Create indexBuffer

	WORD indices[NUM_INDICES] =
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

	device->CreateIndexBuffer(NUM_INDICES * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &iBuffer, NULL);

	VOID* pIndices;
	iBuffer->Lock(0, sizeof(indices), (void**)&pIndices, 0);
	memcpy_s(pIndices, sizeof(indices), indices, sizeof(indices));
	iBuffer->Unlock();

	//Load texture

	D3DXCreateTextureFromFile(device, texName.c_str(), &texture);

	if (!texture)
	{
		MessageBox(NULL, "Failed to create texture", NULL, NULL);
		return;
	}



}

void GTexCube::Update(float dt)
{
	
	rotation.y += dt;
	rotation.x += dt;
	rotation.z += dt;
}

void GTexCube::Draw(IDirect3DDevice9* device)
{
	device->SetTexture(0, texture);
	device->SetTransform(D3DTS_WORLD, &GetWorld());
	device->SetStreamSource(0, vBuffer, 0, sizeof(d3dVertex::VertexPositionTexture));
	device->SetIndices(iBuffer);
	device->SetFVF(d3dVertex::VertexPositionTexture::FVF);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_INDICES, 0, NUM_INDICES / 3);



}

void GTexCube::Release()
{
	d3d::Release(texture);
	d3d::Release(iBuffer);
	d3d::Release(vBuffer);
}

D3DXMATRIX GTexCube::GetWorld()
{

	D3DXMATRIX Scale, Rx, Ry, Rz, Translate;
	D3DXMatrixScaling(&Scale, scale.x, scale.y, scale.z);
	D3DXMatrixRotationX(&Rx, rotation.x);
	D3DXMatrixRotationY(&Ry, rotation.y);
	D3DXMatrixRotationZ(&Rz, rotation.z);
	D3DXMatrixTranslation(&Translate, position.x, position.y, position.z);

	world = Scale * Rx * Ry * Rz * Translate;
	return world;
}