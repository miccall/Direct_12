#pragma once
#include "stdafx.h"


class D3DLib
{
public:
	// 获取单例 ，不允许外部构造 
	static D3DLib* getInstance();
	
	
	static const int frameBufferCount = 3; // 我们想要的缓冲区数量，2个用于双缓冲，3个用于三重缓冲 
	HANDLE fenceEvent;// a handle to an event when our fence is unlocked by the gpu
	
	bool InitD3D(); // initializes direct3d 12
	void Update(); // update the game logic
	void UpdatePipeline(); // update the direct3d pipeline (update command lists)
	void Render(); // execute the command list
	void Cleanup(); // release com objects and clean up memory
	void WaitForPreviousFrame(); // wait until gpu is finished with command list
	
	// debug log 方法 

	// 显卡信息 
	void LogAdapters();
	// 显示器信息 
	void LogAdapterOutputs();
	// 显示器分辨率和刷新率 ，由 LogAdapterOutputs 调用 
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);


private:
	// 单例  
	static D3DLib* Instance;

	UINT64 fenceValue[frameBufferCount]; // 每帧增加此值。 每个 fence 都有自己的 值
	int frameIndex; // current rtv we are on
	int rtvDescriptorSize; // 设备上rtv描述符的大小（所有前后缓冲区大小相同
	IDXGIAdapter1* adapter; // adapters are the graphics card (this includes the embedded graphics on the motherboard)
	int adapterIndex = 0; // we'll start looking for direct x 12  compatible graphics devices starting at index 0
	bool adapterFound = false; // set this to true when a good one was found
							   // find first hardware gpu that supports d3d 12
	HRESULT hr;
	// -- Create the Device -- //
	IDXGIFactory4* dxgiFactory;

	D3DLib();
	~D3DLib();

	// 拷贝构造 
	D3DLib(const D3DLib&);
	
	ID3D12Device* device; // direct3d device
	IDXGISwapChain3* swapChain; // 用于在渲染目标之间切换的交换链
	ID3D12CommandQueue* commandQueue; // command lists 
	ID3D12DescriptorHeap* rtvDescriptorHeap; // 描述符堆，用于保存渲染目标等资源 
	ID3D12Resource* renderTargets[frameBufferCount]; // number of render targets equal to buffer count
	ID3D12CommandAllocator* commandAllocator[frameBufferCount]; // 我们想为每个缓冲区提供足够的分配器*线程数（我们只有一个线程）
	ID3D12GraphicsCommandList* commandList; // 一个命令列表，我们可以记录命令，然后执行它们来渲染帧
	ID3D12Fence* fence[frameBufferCount];
	// 在我们的命令列表由gpu执行时被锁定的对象。 我们需要尽可能多的分配器（如果我们想知道gpu何时完成资产，则需要更多）
};



