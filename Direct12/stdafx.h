#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN    
// Exclude rarely-used stuff from Windows headers.
#endif
#pragma warning(disable:4996)
#include <iostream>
#include <windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include <string>
using namespace std;

// this will only call release if an object exists (prevents exceptions calling release on non existent objects)
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

// Handle to the window
extern HWND hwnd ;

// name of the window (not the title)
extern  LPCTSTR WindowName ;

// title of the window
extern  LPCTSTR WindowTitle ;

// width and height of the window
extern  int Width ;
extern  int Height ;

// is window full screen?
extern  bool FullScreen ;

// we will exit the program when this becomes false
extern  bool isRuning;

extern HANDLE fenceEvent; // a handle to an event when our fence is unlocked by the gpu


