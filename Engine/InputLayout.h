#pragma once

class InputLayout
{
public:
	InputLayout();
	~InputLayout();

public:
	void Create(const vector<D3D11_INPUT_ELEMENT_DESC>& descs, ComPtr<ID3DBlob> blob);

public:
	auto GetComPtr() const { return _inputLayout; }

private:
	ComPtr<ID3D11InputLayout> _inputLayout;
};

