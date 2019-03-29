#include "CreatWindow.h"
using namespace DirectX; //math library

constexpr auto Debug = false ;
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	// ���п����Դ���
	if (Debug)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
	}
	// create the window
	if (!InitializeWindow(hInstance, nShowCmd, FullScreen))
	{
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return 1;
	}

	D3DLib * d3dapp = D3DLib::getInstance();
	// initialize direct3d
	if (!d3dapp->InitD3D())
	{
		MessageBox(0, L"Failed to initialize direct3d 12",
			L"Error", MB_OK);
		d3dapp->Cleanup();
		return 1;
	}

	// start the main loop
	mainloop();

	// we want to wait for the gpu to finish executing the command list before we start releasing everything
	// �������ڿ�ʼ  �ͷ���������  ֮ǰ  �ȴ�gpu ִ���������б�  
	d3dapp->WaitForPreviousFrame();

	// close the fence event
	CloseHandle(d3dapp->fenceEvent);

	// clean up everything
	d3dapp->Cleanup();

	return 0;
}

