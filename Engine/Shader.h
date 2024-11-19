#pragma once

class InputLayout;

class Shader
{
public:
	Shader();
	~Shader();

public:
	void CreateDefault();

	// fileName : actual file name / shaderName : ENTRY NAME
	void CreateVertexShader(const string& fileName, const string& shaderName);
	void CreatePixelShader(const string& filename, const string& shaderName);
	
	// explicitly used when override inputlayout
	void CreateInputLayout(vector<D3D11_INPUT_ELEMENT_DESC> desc);

public:
	void SetVertexShader(shared_ptr<VertexShader> shader,
		vector<D3D11_INPUT_ELEMENT_DESC> desc = VertexType::descs) 
	{
		_vs = shader; CreateInputLayout(desc);
	}
	void SetPixelShader(shared_ptr<PixelShader> shader) { _ps = shader; }

	shared_ptr<InputLayout> GetInputLayout() const { return _inputLayout; }
	shared_ptr<VertexShader> GetVertexShader() const { return _vs; }
	shared_ptr<PixelShader> GetPixelShader() const { return _ps; }


private:
	shared_ptr<InputLayout> _inputLayout;
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
};
