#include "EnginePch.h"
#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::Init()
{
    for (const auto& desc : descs)
    {
        if (desc.type == SHADER_TYPE::Vertex)
        {
            shared_ptr<VertexShader> vs = make_shared<VertexShader>();
            vs->Create(desc.fileName, desc.entryName, "vs_5_0");
            AddVertexShader(vs);
        }
        else if (desc.type == SHADER_TYPE::Pixel)
        {
            shared_ptr<PixelShader> ps = make_shared<PixelShader>();
            ps->Create(desc.fileName, desc.entryName, "ps_5_0");
            AddPixelShader(ps);
        }
    }
}

void ShaderManager::LoadFromFile(const wstring& path, const string& name, const string& version, OUT ComPtr<ID3DBlob>& blob)
{
    ComPtr<ID3DBlob> error;

    const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    HRESULT hr = ::D3DCompileFromFile(
        path.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        name.c_str(),
        version.c_str(),
        compileFlag,
        0,
        blob.GetAddressOf(),
        error.GetAddressOf()
    );

    if (FAILED(hr))
    {
        if (error != NULL)
        {
            string str = (const char*)error->GetBufferPointer();
            MessageBoxA(NULL, str.c_str(), "Shader Error", MB_OK);
        }

        assert(false);
    }
}

void ShaderManager::AddVertexShader(shared_ptr<VertexShader> shader)
{
    _vsSet.insert(shader);
}

shared_ptr<VertexShader> ShaderManager::GetVertexShader(const string& name)
{
    auto it = find_if(_vsSet.begin(), _vsSet.end(),
        [name](shared_ptr<VertexShader> vs)->bool
        {
            if (vs->GetName() == name) return true;
            return false;
        }
    );

    if (it == _vsSet.end())
    {
        assert(false, "Failed to find shader");
        return nullptr;
    }

    return *it;
}

void ShaderManager::AddPixelShader(shared_ptr<PixelShader> shader)
{
    _psSet.insert(shader);
}

shared_ptr<PixelShader> ShaderManager::GetPixelShader(const string& name)
{
    auto it = find_if(_psSet.begin(), _psSet.end(),
        [name](shared_ptr<PixelShader> ps)->bool
        {
            if (ps->GetName() == name) return true;
            return false;
        }
    );

    if (it == _psSet.end())
    {
        assert(false, "Failed to find shader");
        return nullptr;
    }

    return *it;
}

vector<SHADER_DESC> ShaderManager::descs =
{
    {SHADER_TYPE::Vertex, "Vertex.hlsl", "VS"},
    {SHADER_TYPE::Pixel, "Pixel.hlsl", "PS"},
    {SHADER_TYPE::Pixel, "TestPixel.hlsl", "TestPS"}
    // Add when need more!!
};