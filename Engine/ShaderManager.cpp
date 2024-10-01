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
