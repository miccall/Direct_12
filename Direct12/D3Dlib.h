#pragma once
#include "stdafx.h"

bool InitD3D(); // initializes direct3d 12

void Update(); // update the game logic

void UpdatePipeline(); // update the direct3d pipeline (update command lists)

void Render(); // execute the command list

void Cleanup(); // release com objects and clean up memory

void WaitForPreviousFrame(); // wait until gpu is finished with command list