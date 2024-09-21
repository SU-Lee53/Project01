#include "EnginePch.h"
#include "BlendState.h"

BlendState::BlendState()
{
}

BlendState::~BlendState()
{
}

void BlendState::Create(D3D11_RENDER_TARGET_BLEND_DESC blendDesc, float factor)
{
    _blendFactor = factor;

    D3D11_BLEND_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    {
        desc.AlphaToCoverageEnable = false;
        desc.IndependentBlendEnable = false;
        desc.RenderTarget[0] = blendDesc;
    }


    HRESULT hr = DEVICE->CreateBlendState(&desc, _blendState.GetAddressOf());
    HR_ASSERT(hr);
}
