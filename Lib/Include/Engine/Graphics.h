#pragma once
#include "Viewport.h";

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
	auto GetDevice() { return _device; }
	auto GetDeviceContext() { return _deviceContext; }

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
};

