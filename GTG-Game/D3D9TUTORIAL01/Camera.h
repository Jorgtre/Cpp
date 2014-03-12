#ifndef CAMERA_H
#define CAMERA_H

#include <d3d9.h>
#include <d3dx9.h>
#include "Output.h"
#include "Input.h"
#include "Mouse.h"



class Camera
{
public:

	Camera();
	~Camera();



	void Update(IDirect3DDevice9* device, int winWidth, int winHeight, float dt, mouse& Mouse);
	D3DXVECTOR3 Position();
	D3DXVECTOR3 LookingAt();
	D3DXVECTOR3 vUp();
	void Position(float x, float y, float z);
	void LookAt(float x, float y, float z);
	void vUp(float x, float y, float z);
	mouse ref_Mouse;
	



private:
	D3DXVECTOR3 m_vEyeAtPt;
	D3DXVECTOR3	m_vLookAtPt;
	D3DXVECTOR3 m_vUp;
	
	D3DXMATRIX  m_matView;
	void Move();
	void Rotate();



protected:







};
#endif // ! CAMERA_H
