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
#include <vector>
using namespace std;

// this will only call release if an object exists (prevents exceptions calling release on non existent objects)
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

// 一些基础的全局变量 
extern HWND hwnd ;
extern LPCTSTR WindowName ;
extern LPCTSTR WindowTitle ;
extern int Width ;
extern int Height ;
extern bool FullScreen ;
extern bool isRuning;




