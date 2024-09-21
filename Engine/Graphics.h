#pragma once
#include "Viewport.h";

class Pipeline;

class Graphics
{
	DECLARE_SINGLE(Graphics);

public:
	void Init(HWND hWnd);
	
public:
	void RenderBegin();
	void RenderEnd();

private:
	void CreateDeviceAndSwapChain();
	void CreateRTV();
	void CreateDSV();

public:
	auto GetDevice() const { return _device; }
	auto GetDeviceContext() const { return _deviceContext; }

public:
	shared_ptr<Pipeline> GetPipeline() const { return _pipeLine; }

private:
	HWND _hWnd;

	// Device, DeviceContext
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	ComPtr<IDXGISwapChain> _swapChain = nullptr;

	// RTV
	ComPtr<ID3D11RenderTargetView> _rtv;

	// DSV
	ComPtr<ID3D11Texture2D> _dsTexture;
	ComPtr<ID3D11DepthStencilView> _dsv;

	Viewport _viewPort;

	// Pipelines
	shared_ptr<Pipeline> _pipeLine;
};

