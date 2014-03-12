#include <windows.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include "d3dUtil.h"
#include "World.h"
#include "Camera.h"







#ifndef D3DAPP_H
#define D3DAPP_H

class D3DApp
{
public:
	//Constructor
	D3DApp(HINSTANCE hInstance);

	//Destructor
	virtual ~D3DApp();

	//Main Loop
	int Run();

	//Framework methods
	virtual bool Init();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	void ShutDown();
	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


	//--------------GLOBAL VARIABLES------------------

	int abcX = 1001231;
	
	World world;
	Camera cam;
	IDirect3DDevice9*		m_pDevice3D;



protected:
	//Attributes
	HWND		 m_hAppWindow;
	HINSTANCE	 m_hAppInstance;
	unsigned int m_uiClientWidth;
	unsigned int m_uiClientHeight;
	std::string  m_sAppTitle;
	DWORD		 m_WindowStyle;
	float		 m_FPS;
	bool		 m_bHandleDeviceLost;
	bool		 m_bDeviceLost;







	//DirectX Attributes
	IDirect3D9*				m_pDirect3D;
	
	D3DPRESENT_PARAMETERS	m_d3dpp;




protected:
	//Methodes

	//Init app Window
	bool InitWindow();

	//Init Direct3D
	bool InitDirect3D();

	//Calculate FPS
	void CalculateFPS(float dt);






};

#endif