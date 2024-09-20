#include "EnginePch.h"
#include "Graphics.h"

void Graphics::Init(HWND hWnd)
{
	_hWnd = hWnd;
	CreateDeviceAndSwapChain();
	CreateRTV();
	CreateDSV();
	_viewPort = Viewport(GAME.GetDesc().width, GAME.GetDesc().height);
}

void Graphics::RenderBegin()
{
	_deviceContext->OMSetRenderTargets(1, _rtv.GetAddressOf(), _dsv.Get());
	_deviceContext->ClearRenderTargetView(_rtv.Get(), (float*)(&GAME.GetDesc().clearColor));
	_deviceContext->ClearDepthStencilView(_dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	_viewPort.SetViewport();
}

void Graphics::RenderEnd()
{
	HRESULT hr = _swapChain->Present(1, 0);
	HR_ASSERT(hr);
}

void Graphics::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	memset(&desc, 0, sizeof(desc));
	{
		desc.BufferDesc.Width = GAME.GetDesc().width;
		desc.BufferDesc.Height = GAME.GetDesc().height;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = _hWnd;
		desc.Windowed = TRUE;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	HR_ASSERT(hr);
}

void Graphics::CreateRTV()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	HR_ASSERT(hr);

	hr = _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _rtv.GetAddressOf());
	HR_ASSERT(hr);
}

void Graphics::CreateDSV()
{
	{
		D3D11_TEXTURE2D_DESC desc;
		memset(&desc, 0, sizeof(desc));

		desc.Width = GAME.GetDesc().width;
		desc.Height = GAME.GetDesc().height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		HRESULT hr = _device->CreateTexture2D(
			&desc, 
			nullptr, 
			_dsTexture.GetAddressOf()
		);
		HR_ASSERT(hr);
	}

	{
		D3D11_DEPTH_STENCIL_VIEW_DESC desc;
		memset(&desc, 0, sizeof(desc));

		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;

		HRESULT hr = _device->CreateDepthStencilView(
			_dsTexture.Get(),
			&desc,
			_dsv.GetAddressOf()
		);
		HR_ASSERT(hr);
	}

}
