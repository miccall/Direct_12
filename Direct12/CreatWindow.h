#pragma once
#include "D3Dlib.h"


// create a window
bool InitializeWindow(HINSTANCE hInstance,int ShowWnd,bool fullscreen);
// main application loop
void mainloop();
// callback function for windows messages
LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);