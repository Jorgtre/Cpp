#include "Camera.h"
#include "Block.h"
#include "World.h"





Camera::Camera()
{
	m_vEyeAtPt.z = -1;
}
Camera::~Camera()
{

}
void Camera::Update(IDirect3DDevice9* m_pDevice3D, int winWidth, int winHeight, float dt, mouse& Mouse)
{
	ref_Mouse = Mouse;
	
	
	

	m_vUp.y = 1;

	Rotate();
	Move();
	

	if (keyClicked(VK_P)) { printXMATRIX(m_matView); }


	m_pDevice3D->SetTransform(D3DTS_VIEW, &m_matView);

	//setting projection
	D3DXMatrixPerspectiveFovLH(&m_matView, D3DX_PI / 4, static_cast<float>(winWidth) / winHeight, 1.0f, 1000.0f);

	m_pDevice3D->SetTransform(D3DTS_PROJECTION, &m_matView);
	m_pDevice3D->SetRenderState(D3DRS_LIGHTING, false);


}
void Camera::Rotate()
{
	

	D3DXVECTOR3 vDirection, vRotAxis;
	D3DXMATRIX matRotAxis, matRotY, matRotZ;


	

	D3DXVec3Normalize(&vDirection, &(m_vLookAtPt - m_vEyeAtPt)); //create direction vector



	D3DXVec3Cross(&vRotAxis, &vDirection, &m_vUp); //strafe vector
	D3DXVec3Normalize(&vRotAxis, &vRotAxis);

	//create rotation matrices

	D3DXMatrixRotationAxis(&matRotAxis, &vRotAxis, ref_Mouse.getDY() / -800);


	D3DXMatrixRotationY(&matRotY, ref_Mouse.getDX() / 800);

	//D3DXMatrixRotationYawPitchRoll(&matRotZ, Mouse.getDX() / 800,  Mouse.getDY() / 800, Z);

	

	//rotate direction
	D3DXVec3TransformCoord(&vDirection, &vDirection, &(matRotAxis * matRotY));
	//rotate up vector
	D3DXVec3TransformCoord(&m_vUp, &m_vUp, &(matRotAxis * matRotY));
	//translate up vector



	m_vLookAtPt = vDirection + m_vEyeAtPt;

	D3DXMatrixLookAtLH(&m_matView, &m_vEyeAtPt, &m_vLookAtPt, &m_vUp);

	

}
void Camera::Move()
{


	D3DXVECTOR3 vDirection;

	D3DXVec3Normalize(&vDirection, &(m_vLookAtPt - m_vEyeAtPt)); //create direction vector

	float m_fSpeed = 0.01f;

	if (keyHeld(VK_T))
	{

		printVector3(vDirection);

	}
	else
	{
		vDirection.y = 0; //Make sure the the camera does NOT move on the value of Y
	}
		
	

	if (keyHeld(VK_W))
	{
		if (keyHeld(VK_LSHIFT)) //fast movement
		{
			m_vEyeAtPt += vDirection * (m_fSpeed * 6);
			m_vLookAtPt += vDirection * (m_fSpeed * 6);
		}
		else
		{
			m_vEyeAtPt += vDirection * m_fSpeed;
			m_vLookAtPt += vDirection * m_fSpeed;
		}
	}

	if (keyHeld(VK_S))
	{
		if (keyHeld(VK_LSHIFT)) //fast movement
		{
			m_vEyeAtPt -= vDirection * (m_fSpeed * 6);
			m_vLookAtPt -= vDirection * (m_fSpeed * 6);
		}
		else
		{
			m_vEyeAtPt -= vDirection * m_fSpeed;
			m_vLookAtPt -= vDirection * m_fSpeed;
		}
	}
	if (keyHeld(VK_A))
	{
		D3DXVec3Cross(&vDirection, &vDirection, &m_vUp); //create strafe vector
		D3DXVec3Normalize(&vDirection, &vDirection);

		if (keyHeld(VK_LSHIFT)) //fast movement
		{
			m_vEyeAtPt += vDirection * (m_fSpeed * 6);
			m_vLookAtPt += vDirection * (m_fSpeed * 6);
		}
		else
		{
			m_vEyeAtPt += vDirection * m_fSpeed;
			m_vLookAtPt += vDirection * m_fSpeed;
		}
	}

	if (keyHeld(VK_D))
	{
		D3DXVec3Cross(&vDirection, &vDirection, &m_vUp); //create strafe vector
		D3DXVec3Normalize(&vDirection, &vDirection);

		if (keyHeld(VK_LSHIFT)) //fast movement
		{
			m_vEyeAtPt -= vDirection * (m_fSpeed * 6);
			m_vLookAtPt -= vDirection * (m_fSpeed * 6);
		}
		else
		{
			m_vEyeAtPt -= vDirection * m_fSpeed;
			m_vLookAtPt -= vDirection * m_fSpeed;
		}
	}
	
}
D3DXVECTOR3 Camera::Position()
{
	return m_vEyeAtPt;
}
D3DXVECTOR3 Camera::LookingAt()
{
	return m_vLookAtPt;
}
D3DXVECTOR3 Camera::vUp()
{
	return m_vUp;
}
void Camera::Position(float x, float y, float z)
{
	m_vEyeAtPt = D3DXVECTOR3(x, y, z);
}
void Camera::LookAt(float x, float y, float z)
{
	m_vLookAtPt = D3DXVECTOR3(x, y, z);
}
void Camera::vUp(float x, float y, float z)
{
	m_vUp = D3DXVECTOR3(x, y, z);
}






