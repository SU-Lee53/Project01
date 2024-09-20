#pragma once

class Shader
{
public:
	Shader(wstring filename);
	~Shader();

public:
	void Create();

private:
	void LoadFromFile(const string& name, const string& version);
	void CreateVertexShader();
	void CreatePixelShader();

public:
	auto GetVertexShader() { return _vs; }
	auto GetPixelShader() { return _ps; }

private:
	wstring _filePath;
	ComPtr<ID3DBlob> _blob;
	ComPtr<ID3D11VertexShader> _vs;
	ComPtr<ID3D11PixelShader> _ps;

};

