#include "EnginePch.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState()
{
}

RasterizerState::~RasterizerState()
{
}

void RasterizerState::Create()
{
    D3D11_RASTERIZER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    {
        desc.FillMode = D3D11_FILL_SOLID;
        desc.CullMode = D3D11_CULL_BACK;
        desc.FrontCounterClockwise = false;
    }

    HRESULT hr = DEVICE->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
    HR_ASSERT(hr);
}
