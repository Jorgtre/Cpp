#include "D3DApp.h"
#include <sstream>
#include "Input.h"
#include "Chunk.h"

namespace
{
	//Create a global pointer to D3DApp
	D3DApp* g_pd3dApp;
	

}

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//Forward the messages
	return g_pd3dApp->MsgProc(hwnd, msg, wParam, lParam);



}

D3DApp::D3DApp(HINSTANCE hInstance)
{
	m_hAppInstance = hInstance;
	m_hAppWindow = NULL;
	m_uiClientWidth = 1900;
	m_uiClientHeight = 1000;
	m_sAppTitle = "DIRECTX9 APPLICATION";
	m_WindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
	m_bDeviceLost = false;
	m_bHandleDeviceLost = false;
	g_pd3dApp = this;


}

D3DApp::~D3DApp()
{
	//Realease object from memory
}

int D3DApp::Run()
{

	
	//Store counts per secound
	__int64 countsPersec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*) &countsPersec);
	float secPerCount = 1.0f / countsPersec; // Store seconds per count

	//Initial previous time
	__int64 prevTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*) &prevTime);

	//Main message loop
	MSG msg = {0};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else
		{
			//Capture current count
			__int64 curTime = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			//Calculate deltaTime
			float deltaTime = (curTime - prevTime) * secPerCount;


			//Calculate FPS
			CalculateFPS(deltaTime);
			//Update
			Update(deltaTime);
			//Render
			Render();

			//set previous time to current time
			prevTime = curTime;

		}
	}

	//Shutdown
	ShutDown();

	

	return static_cast<int>(msg.wParam);
}

bool D3DApp::Init()
{
	//Check window creation
	if (!InitWindow())
	{
		return false;
	}
	
	//Check Direct3D init

	if (!InitDirect3D())
	{
		return false;
	}
	return true;
}

bool D3DApp::InitWindow()
{

	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = m_hAppInstance;
	wcex.lpfnWndProc = MainWindowProc;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH) GetStockObject(NULL_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "D3DAPPWNDCLASS";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	

	
	

	//Register that class

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Failed to register window class", NULL, NULL);
		return false;
	}
	//Cache requested width, height
	RECT r = { 0, 0, m_uiClientWidth, m_uiClientHeight };
	AdjustWindowRect(&r, m_WindowStyle, false);
	int width = r.right - r.left;
	int height = r.bottom - r.top;
	
	//Create window
	m_hAppWindow = CreateWindow("D3DAPPWNDCLASS", m_sAppTitle.c_str(), m_WindowStyle,
								GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2,
								GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2,
								width, height, NULL, NULL, m_hAppInstance, NULL);

	

	//Check if window was created
	if (!m_hAppInstance)
	{
		MessageBox(NULL, "Failed to create window", NULL, NULL);
		return false;
	}

	//Show window
	ShowWindow(m_hAppWindow, SW_SHOW);

	return true;



}

void D3DApp::ShutDown()
{
	//Release direct3D from memory
	d3d::Release(m_pDevice3D);
	d3d::Release(m_pDirect3D);

}

bool D3DApp::InitDirect3D()
{
	//Get interface to Direct3D
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_pDirect3D)
	{
		MessageBox(NULL, "Failed to create direct3D com object", NULL, NULL);
		return false;
	}

	//Check device capabilities
	D3DCAPS9 m_d3dDevCaps;
	m_pDirect3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_d3dDevCaps);

	int vp;
	if (m_d3dDevCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	//Fill out the present parameters
	ZeroMemory(&m_d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	m_d3dpp.BackBufferWidth = m_uiClientWidth;
	m_d3dpp.BackBufferHeight = m_uiClientHeight;
	m_d3dpp.Windowed = true;
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_d3dpp.MultiSampleQuality = 0;
	m_d3dpp.hDeviceWindow = m_hAppWindow;
	m_d3dpp.Flags = 0;
	m_d3dpp.EnableAutoDepthStencil = true;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;


	//Create the device
	m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, m_hAppWindow, vp, &m_d3dpp, &m_pDevice3D);
	if (!m_pDevice3D)
	{
		MessageBox(NULL, "Failed device creation", NULL, NULL);
		return false;
	}

	D3DVIEWPORT9 viewport;
	ZeroMemory(&viewport, sizeof(D3DVIEWPORT9));
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = m_uiClientWidth;
	viewport.Height = m_uiClientHeight;
	viewport.MinZ = 0;
	viewport.MaxZ = 1;

	m_pDevice3D->SetViewport(&viewport);


	return true;
}

void D3DApp::CalculateFPS(float dt){

	static int frameCnt;
	static float elapsedTime;

	//Incroment frameCnt
	frameCnt++;
	//Incroment elapsed time
	elapsedTime += dt;

	if (elapsedTime >= 1.0f)
	{
		m_FPS = (float)frameCnt;

		//Output FPS to Window title
		std::stringstream ss;

		ss << m_sAppTitle.c_str() << " FPS:  " << m_FPS;
		SetWindowText(m_hAppWindow, ss.str().c_str());


		//Reset elapsed time and frameCount
		frameCnt = 0;
		elapsedTime = 0;


	}


}

LRESULT D3DApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (keyHeld(VK_ESCAPE)) 
	{
		PostQuitMessage(0);
		return 0; 
	}
	
	switch (msg)
	{
	

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;



	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_F1:
			m_bHandleDeviceLost = !m_bHandleDeviceLost;
			return 0;
		}
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);


}





