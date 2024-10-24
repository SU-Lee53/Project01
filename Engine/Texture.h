#pragma once
#include "Resource_Base.h"

class Texture : public Resource_Base
{
public:
	Texture();
	virtual ~Texture();

public:
	void Create(const wstring& path);

	void CreateErrorTexture();

	ComPtr<ID3D11ShaderResourceView> GetComPtr() const { return _srv; }
	Vec2 GetSize() const { return _size; }

	bool IsErrorTexture() const { return _isErrorTexture; }

private:
	ComPtr<ID3D11ShaderResourceView> _srv;
	Vec2 _size;
	bool _isErrorTexture = false;

public:
	using Ty = Texture;
};

