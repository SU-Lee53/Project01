#include "EnginePch.h"
#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::Create(const wstring& path)
{
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;

	HRESULT hr = LoadFromWICFile(
		path.c_str(),
		WIC_FLAGS_NONE,
		&md,
		img
	);

	HR_ASSERT(hr);

	hr = CreateShaderResourceView(
		DEVICE.Get(),
		img.GetImages(),
		img.GetImageCount(),
		md,
		_srv.GetAddressOf()
	);

	HR_ASSERT(hr);

	_size.x = md.width;
	_size.y = md.height;

}

void Texture::CreateErrorTexture()
{
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;

	wstring errPath = L"../Resources/Texture/error.jpg";

	HRESULT hr = LoadFromWICFile(
		errPath.c_str(),
		WIC_FLAGS_NONE,
		&md,
		img
	);

	HR_ASSERT(hr);

	hr = CreateShaderResourceView(
		DEVICE.Get(),
		img.GetImages(),
		img.GetImageCount(),
		md,
		_srv.GetAddressOf()
	);

	HR_ASSERT(hr);

	_size.x = md.width;
	_size.y = md.height;
}
