#pragma once
#include "stdafx.h"


class D3DLib
{
public:
	// ��ȡ���� ���������ⲿ���� 
	static D3DLib* getInstance();
	
	
	static const int frameBufferCount = 3; // ������Ҫ�Ļ�����������2������˫���壬3���������ػ��� 
	HANDLE fenceEvent;// a handle to an event when our fence is unlocked by the gpu
	
	bool InitD3D(); // initializes direct3d 12
	void Update(); // update the game logic
	void UpdatePipeline(); // update the direct3d pipeline (update command lists)
	void Render(); // execute the command list
	void Cleanup(); // release com objects and clean up memory
	void WaitForPreviousFrame(); // wait until gpu is finished with command list
	
	// debug log ���� 

	// �Կ���Ϣ 
	void LogAdapters();
	// ��ʾ����Ϣ 
	void LogAdapterOutputs();
	// ��ʾ���ֱ��ʺ�ˢ���� ���� LogAdapterOutputs ���� 
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);


private:
	// ����  
	static D3DLib* Instance;

	UINT64 fenceValue[frameBufferCount]; // ÿ֡���Ӵ�ֵ�� ÿ�� fence �����Լ��� ֵ
	int frameIndex; // current rtv we are on
	int rtvDescriptorSize; // �豸��rtv�������Ĵ�С������ǰ�󻺳�����С��ͬ
	IDXGIAdapter1* adapter; // adapters are the graphics card (this includes the embedded graphics on the motherboard)
	int adapterIndex = 0; // we'll start looking for direct x 12  compatible graphics devices starting at index 0
	bool adapterFound = false; // set this to true when a good one was found
							   // find first hardware gpu that supports d3d 12
	HRESULT hr;
	// -- Create the Device -- //
	IDXGIFactory4* dxgiFactory;

	D3DLib();
	~D3DLib();

	// �������� 
	D3DLib(const D3DLib&);
	
	ID3D12Device* device; // direct3d device
	IDXGISwapChain3* swapChain; // ��������ȾĿ��֮���л��Ľ�����
	ID3D12CommandQueue* commandQueue; // command lists 
	ID3D12DescriptorHeap* rtvDescriptorHeap; // �������ѣ����ڱ�����ȾĿ�����Դ 
	ID3D12Resource* renderTargets[frameBufferCount]; // number of render targets equal to buffer count
	ID3D12CommandAllocator* commandAllocator[frameBufferCount]; // ������Ϊÿ���������ṩ�㹻�ķ�����*�߳���������ֻ��һ���̣߳�
	ID3D12GraphicsCommandList* commandList; // һ�������б����ǿ��Լ�¼���Ȼ��ִ����������Ⱦ֡
	ID3D12Fence* fence[frameBufferCount];
	// �����ǵ������б���gpuִ��ʱ�������Ķ��� ������Ҫ�����ܶ�ķ����������������֪��gpu��ʱ����ʲ�������Ҫ���ࣩ
};



