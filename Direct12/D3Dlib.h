#pragma once
#include "stdafx.h"


class D3DLib
{
public:
	static D3DLib* getInstance();
	
	~D3DLib();
	static const int frameBufferCount = 3; // ������Ҫ�Ļ�����������2������˫���壬3���������ػ��� 
	HANDLE fenceEvent;// a handle to an event when our fence is unlocked by the gpu
private:
	static D3DLib* Instance;
	D3DLib();
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

	UINT64 fenceValue[frameBufferCount]; // ÿ֡���Ӵ�ֵ�� ÿ�� fence �����Լ��� ֵ

	int frameIndex; // current rtv we are on

	int rtvDescriptorSize; // �豸��rtv�������Ĵ�С������ǰ�󻺳�����С��ͬ


public:
	
	bool InitD3D(); // initializes direct3d 12
	void Update(); // update the game logic
	void UpdatePipeline(); // update the direct3d pipeline (update command lists)
	void Render(); // execute the command list
	void Cleanup(); // release com objects and clean up memory
	void WaitForPreviousFrame(); // wait until gpu is finished with command list
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);
	void LogAdapterOutputs(IDXGIAdapter* adapter);
};



