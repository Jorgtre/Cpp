#include <windows.h>
#include "D3DApp.h"
#include "GTexCube.h"
#include "Chunk.h"
#include "Output.h"
#include "Input.h"

#include "Test.h"
#include "World.h"




const DWORD d3dVertex::VertexPositionColor::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
const DWORD d3dVertex::VertexPositionTexture::FVF = D3DFVF_XYZ | D3DFVF_TEX1;
const DWORD d3dVertex::VertexPosTex3D::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

mouse Mouse;
mouse& pMouse = Mouse;




class TestApp : public D3DApp
{
public:
	//Constructor
	TestApp(HINSTANCE hInstance);
	//Destructor
	~TestApp();

	//Methodes
	bool Init() override;
	void Update(float dt) override;
	void Render() override;
	void Shutdown();

	void InvalidateDeviceObjects();

	


};

TestApp::TestApp(HINSTANCE hInstance) : D3DApp(hInstance)
{
	
	
}

TestApp::~TestApp()
{

}

bool TestApp::Init()
{
	if (!D3DApp::Init())
	{
		return false;
	}
	
	Init22(m_pDevice3D);

	world.Init(m_pDevice3D);
	

	return true;
}

void TestApp::InvalidateDeviceObjects()
{
	
}

void TestApp::Update(float dt)
{
	

	world.Update(dt);
	Mouse.update();

	if (keyClicked(VK_L)) { Mouse.toggleGrabb(); }

	cam.Update(m_pDevice3D, m_uiClientWidth, m_uiClientHeight, dt, pMouse);
	
	
	
}

void TestApp::Render()
{
	/*
	HRESULT hr;

	if (m_bHandleDeviceLost)
	{
		if (m_bDeviceLost)
		{
			//sleep the thread
			Sleep(100); // Free up CPU

			if (FAILED(hr = m_pDevice3D->TestCooperativeLevel()))
			{
				if (hr == D3DERR_DEVICELOST) { return; }
				
				if (hr == D3DERR_DEVICENOTRESET)
				{
					//Invalidate device objects
					InvalidateDeviceObjects();

					//Reset device
					hr = m_pDevice3D->Reset(&m_d3dpp);

					if (FAILED(hr))
					{
						MessageBox(NULL, "Failed to reset device", NULL, NULL);
						return;
					}


					//Restore device objects
					RestoreDeviceObjects();
				}
				
				return;
			}
		}
	}
	*/



	m_bDeviceLost = false;
	
	m_pDevice3D->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, d3dColors::CornflowerBlue, 1.0f, 0); //Clearing the screen

	m_pDevice3D->BeginScene();
	{
		Render22(m_pDevice3D);


		world.Render();


	}
	m_pDevice3D->EndScene();

	m_pDevice3D->Present(0, 0, 0, 0);

}

void TestApp::Shutdown()
{
	Release22();
	world.Release();
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	TestApp* tApp = new TestApp(hInstance);

	if (!tApp->Init())
		return 1;
	
	return tApp->Run();
}